#include "ConfApp.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>

using json = nlohmann::json;

ConfApp::ConfApp() {
    loadConfig();

    auto connection = sdbus::createSessionBusConnection();
    auto proxy =
        sdbus::createProxy(*connection, "com.system.configurationManager",
                           "/com/system/configurationManager/Application/confManagerApplication1");

    proxy->uponSignal("configurationChanged")
        .onInterface("com.system.configurationManager.Application.Configuration")
        .call([this](const std::map< std::string, sdbus::Variant > &config) {
            onConfigChanged(config);
        });

    proxy->finishRegistration();
}

void ConfApp::loadConfig() {
    std::ifstream file(std::string(getenv("HOME")) +
                       "/com.system.configurationManager/confManagerApplication1.json");
    json          j;
    file >> j;
    timeoutMs_ = j["Timeout"];
    timeoutPhrase_ = j["TimeoutPhrase"];
}

void ConfApp::onConfigChanged(const std::map< std::string, sdbus::Variant > &config) {
    if (config.count("Timeout"))
        timeoutMs_ = config.at("Timeout").get< int32_t >();
    if (config.count("TimeoutPhrase"))
        timeoutPhrase_ = config.at("TimeoutPhrase").get< std::string >();
}

void ConfApp::run() {
    while (true) {
        std::cout << timeoutPhrase_ << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMs_));
    }
}
