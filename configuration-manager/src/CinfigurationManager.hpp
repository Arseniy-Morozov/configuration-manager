#pragma once

#include "ApplicationObject.hpp"
#include <memory>
#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <vector>

class ConfigurationManager {
  public:
    ConfigurationManager();
    void run();

  private:
    void loadApplications();

    std::vector< std::unique_ptr< ApplicationObject > > applications_;

    std::unique_ptr< sdbus::IConnection > connection_; // Добавлен член для подключения к D-Bus
};
