cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME VoxMysticum)
project(${PROJECT_NAME})

include_directories(./src)

set(SOURCE_FILES
        src/Entities/Barrel.cpp
        src/Entities/Bat.cpp
        src/Entities/Effect.cpp
        src/Entities/Entity.cpp
        src/Entities/IBaseEntity.cpp
        src/Entities/Light.cpp
        src/Entities/Magic.cpp
        src/Entities/Player.cpp
        src/json/json-forwards.h
        src/json/json.h
        src/Logging/StandardLogger.cpp
        src/Resources/Shader.cpp
        src/Resources/Texture.cpp
        src/Resources/TMD.cpp
        src/States/GameState.cpp
        src/States/PauseState.cpp
        src/AnimPlayer.cpp
        src/Config.cpp
        src/IDFactory.cpp
        src/jsoncpp.cpp
        src/KeyBindings.cpp
        src/Logging.cpp
        src/main.cpp
        src/ResourceManager.cpp
        src/RNG.cpp
        src/SoundEngine.cpp
        src/StateManager.cpp)

# Add executable and resources
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set (RES_SOURCE "${CMAKE_SOURCE_DIR}/res/Resources")
set (RES_DEST "${CMAKE_CURRENT_BINARY_DIR}/Resources")
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${RES_SOURCE} ${RES_DEST}
        DEPENDS ${destination}
        COMMENT "symbolic link resources folder from ${RES_SOURCE} => ${RES_DEST}"
)

set (DATA_SOURCE "${CMAKE_SOURCE_DIR}/res/Data")
set (DATA_DEST "${CMAKE_CURRENT_BINARY_DIR}/Data")
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${DATA_SOURCE} ${DATA_DEST}
        DEPENDS ${destination}
        COMMENT "symbolic link resources folder from ${DATA_SOURCE} => ${DATA_DEST}"
)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()