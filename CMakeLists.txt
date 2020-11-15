cmake_minimum_required(VERSION 3.12)
project(pinhole)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(glad REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLM REQUIRED)

add_subdirectory(external/assimp)
list(APPEND EXTRA_LIBS assimp)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/external/assimp")

include_directories(include)

file(GLOB PROJECT_HEADERS include/*.hpp
                          include/*.h)
file(GLOB PROJECT_SOURCES src/*.cpp)

file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          README.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("include" FILES ${PROJECT_HEADERS})
source_group("src" FILES ${PROJECT_SOURCES})

add_executable(${PROJECT_NAME} ${PROJECT_HEADERS} ${PROJECT_SOURCES})
 
target_include_directories(${PROJECT_NAME} PUBLIC
    ${GLM_INCLUDE_DIRS}
    ${GLAD_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${EXTRA_INCLUDES}
)
 
target_link_libraries(${PROJECT_NAME} 
    glad::glad
    ${SDL2_LIBRARIES} 
    ${EXTRA_LIBS} 
) 

if (APPLE)
    target_link_libraries(
        ${PROJECT_NAME} 
        "-framework CoreAudio" 
        "-framework AudioToolbox"
        "-framework CoreFoundation"
        "-framework CoreGraphics"
        "-framework CoreVideo"
        "-framework ForceFeedback"
        "-framework IOKit"
        "-framework CarBon"
        "-framework AppKit"
        iconv
    )
endif()


