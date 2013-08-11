# Project needs a name
project(cpu_temp)

execute_process(COMMAND kde4-config --localprefix
                OUTPUT_VARIABLE prefixdir
                OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_INSTALL_PREFIX ${prefixdir})

# Find the required Libaries
find_package(KDE4 REQUIRED)
include(KDE4Defaults)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${KDE4_INCLUDES}
    )

# We add our source code here
set(cpu_temp_SRCS cpu_temp.cpp)

# Now make sure all files get to the right place
kde4_add_plugin(plasma-applet-cpu_temp ${cpu_temp_SRCS})
target_link_libraries(plasma-applet-cpu_temp
    ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS})

install(TARGETS plasma-applet-cpu_temp
    DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES plasma-applet-cpu_temp.desktop
    DESTINATION ${SERVICES_INSTALL_DIR})

install(CODE "execute_process(COMMAND kbuildsycoca4)")
