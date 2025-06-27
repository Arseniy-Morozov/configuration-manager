# D-Bus Configuration Manager

## Описание

Проект реализует D-Bus сервис `com.system.configurationManager` для управления конфигурацией приложений через D-Bus.
Сервис читает конфигурационные файлы из каталога `~/com.system.configurationManager/` и создаёт для каждого файла D-Bus объект с интерфейсом для изменения и получения конфигурации.

В качестве примера клиентского приложения реализовано `confManagerApplication1`, которое подписывается на сигнал изменения конфигурации и выводит в stdout фразу через заданный интервал.

---

## Структура проекта

- `configManager/` — сервис управления конфигурациями (DBus сервис)
- `confManagerApplication1/` — пример клиентского приложения
- `.clang-format` — правила форматирования кода
- `README.md` — инструкция

---

## Сборка

Требования:
- C++17
- CMake >= 3.25
- библиотека [sdbus-c++](https://github.com/Kistler-Group/sdbus-cpp)
- clang-format (рекомендуется)

### Шаги сборки

```bash
# Сборка configManager (DBus сервис)
cd configManager
mkdir build && cd build
cmake ..
make

# Сборка confManagerApplication1 (клиент)
cd ../../confManagerApplication1
mkdir build && cd build
cmake ..
make
