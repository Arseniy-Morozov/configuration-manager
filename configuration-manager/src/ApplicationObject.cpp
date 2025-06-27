#include "ApplicationObject.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

ApplicationObject::ApplicationObject(const std::string &name, const std::string &path,
                                     std::shared_ptr< sdbus::IConnection > connection)
    : appName_(name), configPath_(path), connection_(std::move(connection)) {
    loadConfiguration();

    std::string objPath = "/com/system/configurationManager/Application/" + appName_;
    dbusObject_ = sdbus::createObject(*connection_, objPath);

    dbusObject_->registerMethod("ChangeConfiguration")
        .onInterface("com.system.configurationManager.Application.Configuration")
        .withInputParamNames("key", "value")
        .implementedAs([this](const std::string &key, const sdbus::Variant &val) {
            try {
                applyConfiguration(key, val);
                emitConfigChanged();
            } catch (...) {
                throw sdbus::Error("com.system.configurationManager.Error",
                                   "Failed to change configuration");
            }
        });

    dbusObject_->registerMethod("GetConfiguration")
        .onInterface("com.system.configurationManager.Application.Configuration")
        .withOutputParamNames("configuration")
        .implementedAs([this]() { return config_; });

    dbusObject_->registerSignal("configurationChanged")
        .onInterface("com.system.configurationManager.Application.Configuration")
        .withParameters< std::map< std::string, sdbus::Variant > >();

    dbusObject_->finishRegistration();
}

ApplicationObject::~ApplicationObject() {
    dbusObject_.reset();
}

void ApplicationObject::loadConfiguration() {
    std::ifstream file(configPath_);
    if (!file.is_open()) {
        std::cerr << "[WARN] Failed to open config file: " << configPath_ << std::endl;
        return;
    }

    json j;
    try {
        file >> j;
    } catch (...) {
        std::cerr << "[ERROR] Failed to parse JSON config file: " << configPath_ << std::endl;
        return;
    }

    for (auto &el : j.items()) {
        if (el.value().is_number_integer()) {
            config_[el.key()] = sdbus::Variant(static_cast< int32_t >(el.value().get< int >()));
        } else if (el.value().is_string()) {
            config_[el.key()] = sdbus::Variant(el.value().get< std::string >());
        }
        // Можно добавить поддержку других типов при необходимости
    }
}

void ApplicationObject::saveConfiguration() {
    json j;

    for (const auto &[key, value] : config_) {
        try {
            j[key] = value.get< std::string >();
        } catch (const sdbus::Error &) {
            try {
                j[key] = value.get< int32_t >();
            } catch (const sdbus::Error &) {
                std::cerr << "[WARN] Unsupported variant type for key: " << key << std::endl;
            }
        }
    }

    std::ofstream file(configPath_);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Cannot open config file for saving: " << configPath_ << std::endl;
        return;
    }

    file << j.dump(4);
    file.flush();
    if (file.fail()) {
        std::cerr << "[ERROR] Failed to write config to file: " << configPath_ << std::endl;
    } else {
        std::cout << "[INFO] Configuration saved successfully to " << configPath_ << std::endl;
    }
}

void ApplicationObject::applyConfiguration(const std::string &key, const sdbus::Variant &val) {
    // Здесь по ключу можно добавить кастомную логику валидации или преобразования
    // Пример простой проверки типа для ключа TimeoutPhrase:
    if (key == "TimeoutPhrase") {
        try {
            std::string strVal = val.get< std::string >();
            std::cout << "[INFO] TimeoutPhrase set to: " << strVal << std::endl;
            config_[key] = val;
        } catch (const sdbus::Error &) {
            throw std::runtime_error("Invalid type for TimeoutPhrase; expected string");
        }
    } else {
        // Для остальных ключей просто сохраняем
        config_[key] = val;
    }

    saveConfiguration();
}

void ApplicationObject::emitConfigChanged() {
    dbusObject_->emitSignal("configurationChanged")
        .onInterface("com.system.configurationManager.Application.Configuration")
        .withArguments(config_);
}
