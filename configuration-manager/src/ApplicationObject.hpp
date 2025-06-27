#pragma once

#include <map>
#include <memory>
#include <sdbus-c++/sdbus-c++.h>
#include <string>

class ApplicationObject {
  public:
    ApplicationObject(const std::string &name, const std::string &path,
                      std::shared_ptr< sdbus::IConnection > connection);
    ~ApplicationObject();

  private:
    void loadConfiguration();
    void saveConfiguration();
    void applyConfiguration(const std::string &key, const sdbus::Variant &value);
    void emitConfigChanged();

    std::string                             appName_;
    std::string                             configPath_;
    std::shared_ptr< sdbus::IConnection >   connection_;
    std::unique_ptr< sdbus::IObject >       dbusObject_;
    std::map< std::string, sdbus::Variant > config_;

    // runtime-применяемая конфигурация
    std::string timeoutPhrase_;
};
