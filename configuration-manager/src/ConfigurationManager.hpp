#pragma once

#include "ApplicationObject.hpp"
#include <memory>
#include <sdbus-c++/sdbus-c++.h> // Подключение sdbus-c++ для работы с D-Bus
#include <string>
#include <vector>

class ConfigurationManager {
  public:
    // Конструктор, принимающий соединение
    explicit ConfigurationManager(std::shared_ptr< sdbus::IConnection > connection);

    // Запуск менеджера
    void run();

  private:
    void loadApplications();

    std::shared_ptr< sdbus::IConnection >               connection_;
    std::vector< std::unique_ptr< ApplicationObject > > applications_;
};