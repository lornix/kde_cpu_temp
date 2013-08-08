# cmake project file
execute_process(COMMAND kde4-config --localprefix
                OUTPUT_VARIABLE prefixdir)

set(CMAKE_INSTALL_PREFIX ${prefixdir})

# Project needs a name
project(lornix_cpu_temp)

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
set(lornix_cpu_temp_SRCS lornix_cpu_temp.cpp)

# Now make sure all files get to the right place
kde4_add_plugin(plasma-applet-lornix_cpu_temp ${lornix_cpu_temp_SRCS})
target_link_libraries(plasma-applet-lornix_cpu_temp
    ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS})

install(TARGETS plasma-applet-lornix_cpu_temp
    DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES plasma-applet-lornix_cpu_temp.desktop
    DESTINATION ${SERVICES_INSTALL_DIR})
