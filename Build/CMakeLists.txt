cmake_minimum_required(VERSION 3.12)
project(GameMYX C ASM)

set(CMAKE_C_STANDARD 99)

cmake_policy(SET CMP0076 NEW)

get_filename_component(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)
get_filename_component(GAME_NAME "${ROOT_DIR}" NAME)

########################################################################

if(TARGET_SDL2)
    if(NOT WIN32)
        find_package(SDL2 REQUIRED)
    elseif(MINGW)
        if(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set(sdl2_libpath "${ROOT_DIR}/Build/SDL2/i686-w64-mingw32/lib")
            set(sdl2_incpath "${ROOT_DIR}/Build/SDL2/i686-w64-mingw32/include/SDL2")
        else()
            set(sdl2_libpath "${ROOT_DIR}/Build/SDL2/x86_64-w64-mingw32/lib")
            set(sdl2_incpath "${ROOT_DIR}/Build/SDL2/x86_64-w64-mingw32/include/SDL2")
        endif()
    else()
        if(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set(sdl2_libpath "${ROOT_DIR}/Build/SDL2/lib/x86")
        else()
            set(sdl2_libpath "${ROOT_DIR}/Build/SDL2/lib/x64")
        endif()
    endif()
endif()

########################################################################

if(CMAKE_HOST_WIN32)
    set(EXE_SUFFIX ".exe")
else()
    set(EXE_SUFFIX "")
endif()

macro(build_for_host dir)
    file(MAKE_DIRECTORY "${ROOT_DIR}/Build/${dir}")
    if(CMAKE_HOST_WIN32)
        add_custom_target(${dir}
            COMMAND
                "${CMAKE_COMMAND}" -E
                    make_directory "${ROOT_DIR}/Build/${dir}"
            COMMAND
                "${CMAKE_COMMAND}"
                    -G "MinGW Makefiles"
                    -DCMAKE_TOOLCHAIN_FILE="${ROOT_DIR}/Build/tcc.cmake"
                    -DCMAKE_MAKE_PROGRAM="${ROOT_DIR}/Tools/make/mingw32-make"
                    -DCMAKE_BUILD_TYPE=Release
                    "${ROOT_DIR}/${dir}"
            COMMAND
                "${ROOT_DIR}/Tools/make/mingw32-make"
            WORKING_DIRECTORY
                "${ROOT_DIR}/Build/${dir}"
            )
    else()
        add_custom_target(${dir}
            COMMAND
                "${CMAKE_COMMAND}" -E
                    make_directory "${ROOT_DIR}/Build/${dir}"
            COMMAND
                "${CMAKE_COMMAND}"
                    -DCMAKE_BUILD_TYPE=Release
                    "${ROOT_DIR}/${dir}"
            COMMAND
                "${CMAKE_COMMAND}"
                    --build . --config Release
            WORKING_DIRECTORY
                "${ROOT_DIR}/Build/${dir}"
            )
    endif()
endmacro()

########################################################################
## Tools

set(importer "${ROOT_DIR}/Build/Importer/Importer${EXE_SUFFIX}")
build_for_host(Importer)

set(mmapview "${ROOT_DIR}/Build/MMapView/MMapView${EXE_SUFFIX}")
build_for_host(MMapView)

########################################################################
## Assets

macro(IMPORTER_TARGET target)

    set(inputs)
    set(outputs)

    foreach(arg ${ARGN})
        if("${arg}" MATCHES "\\.(bmp|jpg|png|psd|gif|hdr|pic|ppm|pgm|tsx|tmx)$")
            LIST(APPEND inputs "${arg}")
        elseif("${arg}" MATCHES "\\.h$")
            LIST(APPEND outputs "${arg}")
        endif()
    endforeach()

    add_custom_command(
        OUTPUT
            ${outputs}
        COMMAND
            "${ROOT_DIR}/Build/Importer/Importer" ${ARGN}
        DEPENDS
            ${inputs} "${importer}" Importer
        WORKING_DIRECTORY
            "${CMAKE_CURRENT_BINARY_DIR}"
        )

    if(NOT TARGET "${target}")
        add_custom_target("${target}")
    endif()

    target_sources("${target}" PRIVATE ${outputs})

endmacro()

macro(IMPORTER)
    IMPORTER_TARGET(Assets ${ARGN})
endmacro()

add_subdirectory("${ROOT_DIR}/Data" Data)
add_subdirectory("${ROOT_DIR}/Engine/Dialogs/_Assets" DialogAssets)

########################################################################
## Code

if(TARGET_ZXNEXT)
    add_definitions(-DTARGET_ZXNEXT)
elseif(TARGET_SDL2)
    add_definitions(-DTARGET_SDL2)
endif()

file(GLOB_RECURSE engine1_src
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    #CONFIGURE_DEPENDS
    ${ROOT_DIR}/Engine/AnimSprites/*.c
    ${ROOT_DIR}/Engine/AnimSprites/*.h
    ${ROOT_DIR}/Engine/AnimSprites/*.asm
    ${ROOT_DIR}/Engine/Asserts/*.c
    ${ROOT_DIR}/Engine/Asserts/*.h
    ${ROOT_DIR}/Engine/Asserts/*.asm
    ${ROOT_DIR}/Engine/Collisions/*.c
    ${ROOT_DIR}/Engine/Collisions/*.h
    ${ROOT_DIR}/Engine/Collisions/*.asm
    ${ROOT_DIR}/Engine/Core/*.c
    ${ROOT_DIR}/Engine/Core/*.h
    ${ROOT_DIR}/Engine/Core/*.asm
    ${ROOT_DIR}/Engine/Input/*.c
    ${ROOT_DIR}/Engine/Input/*.h
    ${ROOT_DIR}/Engine/Input/*.asm
    ${ROOT_DIR}/Engine/Quests/*.c
    ${ROOT_DIR}/Engine/Quests/*.h
    ${ROOT_DIR}/Engine/Quests/*.asm
    ${ROOT_DIR}/engine.h
    ${ROOT_DIR}/engine_p.h
    )

file(GLOB_RECURSE engine2_src
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    #CONFIGURE_DEPENDS
    ${ROOT_DIR}/Engine/Dialogs/*.c
    ${ROOT_DIR}/Engine/Dialogs/*.h
    ${ROOT_DIR}/Engine/Dialogs/*.asm
    ${ROOT_DIR}/Engine/Inventory/*.c
    ${ROOT_DIR}/Engine/Inventory/*.h
    ${ROOT_DIR}/Engine/Inventory/*.asm
    ${ROOT_DIR}/Engine/Maps/*.c
    ${ROOT_DIR}/Engine/Maps/*.h
    ${ROOT_DIR}/Engine/Maps/*.asm
    ${ROOT_DIR}/Engine/Music/*.c
    ${ROOT_DIR}/Engine/Music/*.h
    ${ROOT_DIR}/Engine/Music/*.asm
    ${ROOT_DIR}/Engine/Render/*.c
    ${ROOT_DIR}/Engine/Render/*.h
    ${ROOT_DIR}/Engine/Render/*.asm
    ${ROOT_DIR}/Engine/Text/*.c
    ${ROOT_DIR}/Engine/Text/*.h
    ${ROOT_DIR}/Engine/Text/*.asm
    )

file(GLOB_RECURSE game_src
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    #CONFIGURE_DEPENDS
    ${ROOT_DIR}/Game/*.c
    ${ROOT_DIR}/Game/*.h
    ${ROOT_DIR}/Game/*.asm
    ${ROOT_DIR}/config.h
    ${ROOT_DIR}/mmap.h
    ${ROOT_DIR}/mmap.inc
    )

foreach(file ${engine1_src} ${engine2_src} ${game_src})
    if(NOT TARGET_ZXNEXT AND "${file}" MATCHES "\\/ZXNext\\/")
        set_source_files_properties("${file}"
            PROPERTIES HEADER_FILE_ONLY TRUE)
    endif()
    if(NOT TARGET_SDL2 AND "${file}" MATCHES "\\/SDL2\\/")
        set_source_files_properties("${file}"
            PROPERTIES HEADER_FILE_ONLY TRUE)
    endif()
endforeach()

add_library(Engine STATIC
    ${engine1_src}
    )

set_target_properties(Engine PROPERTIES PREFIX "" SUFFIX ".lib")

add_dependencies(Engine DialogsAssets)
target_include_directories(Engine PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(Engine PUBLIC "${ROOT_DIR}/Engine")

add_library(Engine2 STATIC
    ${engine2_src}
    )

set_target_properties(Engine2 PROPERTIES PREFIX "" SUFFIX ".lib")

target_include_directories(Engine2 PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(Engine2 Engine)

if(TARGET_SDL2)
    if(NOT WIN32)
        target_link_libraries(Engine SDL2)
    elseif(MINGW)
        target_link_libraries(Engine
            "${sdl2_libpath}/libSDL2.a" setupapi imm32 winmm version)
        target_include_directories(Engine PRIVATE "${sdl2_incpath}")
        target_include_directories(Engine2 PRIVATE "${sdl2_incpath}")
    else()
        target_link_libraries(Engine "${sdl2_libpath}/SDL2.lib")
        target_include_directories(Engine PRIVATE
            "${ROOT_DIR}/Build/SDL2/include")
        target_include_directories(Engine2 PRIVATE
            "${ROOT_DIR}/Build/SDL2/include")
    endif()
endif()

set_source_files_properties("${CMAKE_BINARY_DIR}/DialogAssets/bank6.c"
    PROPERTIES GENERATED TRUE) # FIXME
set_source_files_properties("${CMAKE_BINARY_DIR}/Data/bank7.c"
    PROPERTIES GENERATED TRUE) # FIXME
set_source_files_properties("${CMAKE_BINARY_DIR}/Data/bank8.c"
    PROPERTIES GENERATED TRUE) # FIXME
set_source_files_properties("${CMAKE_BINARY_DIR}/Data/bank9.c"
    PROPERTIES GENERATED TRUE) # FIXME
set_source_files_properties("${CMAKE_BINARY_DIR}/Data/bank14.c"
    PROPERTIES GENERATED TRUE) # FIXME
set_source_files_properties("${CMAKE_BINARY_DIR}/Data/bank15.c"
    PROPERTIES GENERATED TRUE) # FIXME
#set_source_files_properties("${CMAKE_BINARY_DIR}/Data/bank16.c"
#    PROPERTIES GENERATED TRUE) # FIXME

add_executable(Game WIN32
    ${game_src}
    "${CMAKE_BINARY_DIR}/DialogAssets/bank6.c"  # FIXME
    "${CMAKE_BINARY_DIR}/Data/bank7.c"          # FIXME
    "${CMAKE_BINARY_DIR}/Data/bank8.c"          # FIXME
    "${CMAKE_BINARY_DIR}/Data/bank9.c"          # FIXME
    "${CMAKE_BINARY_DIR}/Data/bank14.c"         # FIXME
    "${CMAKE_BINARY_DIR}/Data/bank15.c"         # FIXME
    #"${CMAKE_BINARY_DIR}/Data/bank16.c"         # FIXME
    )

add_dependencies(Game Assets)
target_include_directories(Game PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(Game Engine Engine2)

if(TARGET_SDL2)
    set_target_properties(Game PROPERTIES
        OUTPUT_NAME "${GAME_NAME}"
    )

    if(NOT WIN32)
        target_link_libraries(Game SDL2::Main)
    elseif(MINGW)
        target_link_libraries(Game mingw32 "${sdl2_libpath}/libSDL2main.a" mingw32)
    else()
        target_link_libraries(Game "${sdl2_libpath}/SDL2main.lib")

        add_custom_command(TARGET Game POST_BUILD
            COMMAND
                "${CMAKE_COMMAND}" -E copy
                    "${sdl2_libpath}/SDL2.dll"
                    "$<TARGET_FILE_DIR:Game>"
            )
    endif()
elseif(TARGET_ZXNEXT)
    add_dependencies(Game MMapView)

    set_target_properties(Game PROPERTIES
        OUTPUT_NAME "${GAME_NAME}"
        PREFIX ""
        SUFFIX ".nex"
        LINK_DEPENDS "${ROOT_DIR}/mmap.h;${ROOT_DIR}/mmap.inc;${mmapview}"
        LINK_FLAGS "-pragma-include:${ROOT_DIR}/mmap.h -Cm -I${ROOT_DIR}"
        )

    add_custom_command(TARGET Game POST_BUILD
        COMMAND
            "${CMAKE_COMMAND}" -E copy
                "$<TARGET_FILE:Game>"
                "${ROOT_DIR}/Build/Sync/Build/${GAME_NAME}.nex"
        COMMAND
            "${mmapview}"
                "${CMAKE_BINARY_DIR}/${GAME_NAME}.map"
                > "${ROOT_DIR}/Build/MemoryMap.txt"
        )
endif()
