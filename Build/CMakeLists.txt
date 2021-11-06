cmake_minimum_required(VERSION 3.12)
project(GameMYX C ASM)

add_definitions(
    -DZXNEXT
    )

get_filename_component(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)
get_filename_component(GAME_NAME "${ROOT_DIR}" NAME)

file(GLOB_RECURSE engine_src
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    CONFIGURE_DEPENDS
    ${ROOT_DIR}/Engine/*.c
    ${ROOT_DIR}/Engine/*.h
    ${ROOT_DIR}/Engine/*.asm
    )

file(GLOB_RECURSE game_src
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    CONFIGURE_DEPENDS
    ${ROOT_DIR}/Game/*.c
    ${ROOT_DIR}/Game/*.h
    ${ROOT_DIR}/Game/*.asm
    )

add_library(Engine STATIC
    ${engine_src}
    )

set_target_properties(Engine PROPERTIES PREFIX "" SUFFIX ".lib")
target_include_directories(Engine PRIVATE "${ROOT_DIR}/Engine")
target_include_directories(Engine PUBLIC "${ROOT_DIR}/Engine/Include")

add_executable(Game
    ${game_src}
    )

target_link_libraries(Game Engine)
set_target_properties(Game PROPERTIES
    OUTPUT_NAME "${GAME_NAME}"
    PREFIX ""
    SUFFIX ".nex"
    LINK_FLAGS "-pragma-include:${ROOT_DIR}/mmap.h -Cm -I${ROOT_DIR}")

add_custom_command(TARGET Game
    POST_BUILD COMMAND
        "${CMAKE_COMMAND}" -E copy
            "$<TARGET_FILE:Game>"
            "${ROOT_DIR}/Build/Sync/Build/${GAME_NAME}.nex"
    )
