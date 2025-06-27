# configuration-manager
D-Bus Configuration Manager
Описание

Проект реализует D-Bus сервис com.system.configurationManager для управления конфигурацией приложений через D-Bus. Сервис читает конфигурационные файлы из каталога ~/com.system.configurationManager/ и создаёт для каждого файла D-Bus объект с интерфейсом для изменения и получения конфигурации.

В качестве примера клиентского приложения реализовано confManagerApplication1, которое подписывается на сигнал изменения конфигурации и выводит в stdout фразу через заданный интервал.
Структура проекта
```
 conf_manager_project/
│
├── configManager/
│   ├── src/
│   │   ├── main.cpp
│   │   ├── ConfigurationManager.cpp
│   │   ├── ConfigurationManager.hpp
│   │   ├── ApplicationObject.cpp
│   │   ├── ApplicationObject.hpp
│   ├── CMakeLists.txt
│
├── confManagerApplication1/
│   ├── src/
│   │   ├── main.cpp
│   │   ├── ConfApp.cpp
│   │   ├── ConfApp.hpp
│   ├── CMakeLists.txt
│
├── .clang-format
```



Сборка

Требования(в моем случае):

    C++17
    CMake >= 3.25
    библиотека sdbus-c++
    clang-format (рекомендуется)

Шаги сборки

# Сборка и запуск configManager (DBus сервис)
```
cd configManager
mkdir build && cd build
cmake ..
make
./configManager
```

# Сборка и запуск confManagerApplication1 (клиент)
```
cd ../../confManagerApplication1
mkdir build && cd build
cmake ..
make
./confManagerApplication1
```
