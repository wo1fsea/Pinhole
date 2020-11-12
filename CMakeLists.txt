cmake_minimum_required(VERSION 3.12)
project(pinehole)
 
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
 
find_package(glad REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLM REQUIRED)
 
add_executable(${PROJECT_NAME}
  src/main.cpp
)
 
target_include_directories(${PROJECT_NAME} PUBLIC
  ${GLM_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS}
)
 
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glad::glad
    ${SDL2_LIBRARIES}
) 

if (APPLE)
    target_link_libraries(
        ${PROJECT_NAME} 
        PRIVATE
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


