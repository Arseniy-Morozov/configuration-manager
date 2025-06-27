#pragma once
#include <sdbus-c++/sdbus-c++.h>
#include <string>

class ConfApp {
  public:
    ConfApp();
    void run();

  private:
    void loadConfig();
    void updateTimer();
    void onConfigChanged(const std::map< std::string, sdbus::Variant > &newConfig);

    int         timeoutMs_ = 1000;
    std::string timeoutPhrase_ = "Default phrase";
};
