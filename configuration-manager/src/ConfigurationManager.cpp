#include "ConfigurationManager.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

ConfigurationManager::ConfigurationManager(std::shared_ptr< sdbus::IConnection > connection)
    : connection_(connection) {}

void ConfigurationManager::loadApplications() {
    const char *homeEnv = std::getenv("HOME");
    if (!homeEnv) {
        std::cerr << "Не удалось получить переменную окружения HOME" << std::endl;
        return;
    }
    std::string configDir = std::string(homeEnv) + "/com.system.configurationManager";

    if (!fs::exists(configDir) || !fs::is_directory(configDir)) {
        std::cerr << "Директория конфигурации не найдена: " << configDir << std::endl;
        return;
    }

    for (const auto &entry : fs::directory_iterator(configDir)) {
        if (entry.path().extension() == ".json") {
            std::string appName = entry.path().stem();

            // Передача connection_ как аргумента
            auto app =
                std::make_unique< ApplicationObject >(appName, entry.path().string(), connection_);
            applications_.push_back(std::move(app));
        }
    }
}

void ConfigurationManager::run() {
    // Создаем соединение, если оно еще не создано
    if (!connection_) {
        connection_ = sdbus::createSessionBusConnection();
        connection_->requestName("com.system.configurationManager");
        std::cout << "Сервис com.system.configurationManager зарегистрирован" << std::endl;
    }

    loadApplications();

    connection_->enterEventLoop();
}
