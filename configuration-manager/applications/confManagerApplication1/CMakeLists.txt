project(confManagerApplication1)

add_executable(confManagerApplication1
    main.cpp
    ConfApp.cpp
)

target_link_libraries(confManagerApplication1 PRIVATE sdbus-c++)
