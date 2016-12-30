# ┌──────────────────────────────────────────────────────────────────┐
# │  Basis für CMAKE                                                 │
# └──────────────────────────────────────────────────────────────────┘

cmake_minimum_required(VERSION 3.6)

# ENV ist im .bashrc definiert
#   (Am Mac auf /Volumes/Daten/DevLocal/DevCPP/cmake )
set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})

# ┌──────────────────────────────────────────────────────────────────┐
# │  Projects Settings                                               │
# └──────────────────────────────────────────────────────────────────┘

project(gpio)

# Output bin, c++11 usw
include(Config)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Google-Test (BasisProjekt: find_package(GTest)                  │
# └──────────────────────────────────────────────────────────────────┘

find_package(GTest)
add_subdirectory(tests)

# ┌──────────────────────────────────────────────────────────────────┐
# │  Libs                                                            │
# └──────────────────────────────────────────────────────────────────┘

# RealLife
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")

    find_library(RF24
            NAMES librf24-bcm.so librf24-bcm.so.1
            HINTS ${PIROOT}
            )

# Simulation
else()

    # Faket nur die LIB
    set(RF24 "")

endif()

# ┌──────────────────────────────────────────────────────────────────┐
# │  Source                                                          │
# └──────────────────────────────────────────────────────────────────┘

# Where GPIOs .h files can be found.
#target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("${PROJECT_SOURCE_DIR}/include")

# RealLife
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")

    include_directories(
            ${PIROOT}/usr/local/include
    )

    set(SOURCE_FILES
            src/raspi/GPIO.cpp
            )

# Simulation
else()

    set(SOURCE_FILES
            src/desktop/GPIO.cpp
            )

endif()

set(SOURCE_FILES ${SOURCE_FILES}
        src/GPIO.cpp
        )

# ┌──────────────────────────────────────────────────────────────────┐
# │  Library (entry points)                                          │
# └──────────────────────────────────────────────────────────────────┘

#add_library (${PROJECT_NAME} SHARED ${SOURCE_FILES})
add_library (${PROJECT_NAME} STATIC
        ${SOURCE_FILES}

        # RF24-Lib
        #${RF24}
        )

target_link_libraries (${PROJECT_NAME}
        ${RF24}
)