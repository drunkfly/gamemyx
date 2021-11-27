cmake_minimum_required(VERSION 3.12)
project(GameMYX C ASM)

set(CMAKE_C_STANDARD 99)

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

macro(IMPORTER)

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

    if(NOT TARGET Assets)
        add_custom_target(Assets)
    endif()

    target_sources(Assets PRIVATE ${outputs})

endmacro()

add_subdirectory("${ROOT_DIR}/Data" Data)

########################################################################
## Code

if(TARGET_ZXNEXT)
    add_definitions(-DTARGET_ZXNEXT)
elseif(TARGET_SDL2)
    add_definitions(-DTARGET_SDL2)
endif()

file(GLOB_RECURSE engine_src
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    #CONFIGURE_DEPENDS
    ${ROOT_DIR}/Engine/*.c
    ${ROOT_DIR}/Engine/*.h
    ${ROOT_DIR}/Engine/*.asm
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

foreach(file ${engine_src} ${game_src})
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
    ${engine_src}
    )

set_target_properties(Engine PROPERTIES PREFIX "" SUFFIX ".lib")
target_include_directories(Engine PUBLIC "${ROOT_DIR}/Engine")

if(TARGET_SDL2)
    if(NOT WIN32)
        target_link_libraries(Engine SDL2)
    elseif(MINGW)
        target_link_libraries(Engine
            "${sdl2_libpath}/libSDL2.a" setupapi imm32 winmm version)
        target_include_directories(Engine PRIVATE "${sdl2_incpath}")
    else()
        target_link_libraries(Engine "${sdl2_libpath}/SDL2.lib")
        target_include_directories(Engine PRIVATE
            "${ROOT_DIR}/Build/SDL2/include")
    endif()
endif()

set_source_files_properties("${CMAKE_BINARY_DIR}/Data/bank6.c"
    PROPERTIES GENERATED TRUE) # FIXME

add_executable(Game WIN32
    ${game_src}
    "${CMAKE_BINARY_DIR}/Data/bank6.c" # FIXME
    )

add_dependencies(Game Assets)
target_include_directories(Game PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(Game Engine)

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
