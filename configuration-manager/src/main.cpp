#include "ConfigurationManager.hpp"
#include <memory>
#include <sdbus-c++/sdbus-c++.h>

int main() {
    // Создаём unique_ptr
    std::unique_ptr< sdbus::IConnection > uniqueConn = sdbus::createSessionBusConnection();

    // Преобразуем в shared_ptr (безопасно, так как unique_ptr владеет объектом)
    std::shared_ptr< sdbus::IConnection > connection(std::move(uniqueConn));

    connection->requestName("com.system.configurationManager");

    ConfigurationManager manager(connection);
    manager.run();

    return 0;
}