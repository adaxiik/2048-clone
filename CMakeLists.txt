cmake_minimum_required(VERSION 3.0.0)
project(2048 LANGUAGES C VERSION 1.0)

#debug
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -fsanitize=address -g -fno-omit-frame-pointer -fno-sanitize-recover")
#set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address -fno-sanitize-recover")
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}")



#https://stackoverflow.com/questions/58107854/cmake-is-unable-to-find-sdl2-ttf-im-trying-to-link-it-the-same-way-i-would-wit
#change it if it doesn't work, but find_package(SDL2_TTF) doesn't work for me
INCLUDE(FindPkgConfig)  
#find_package(SDL2)
#find_package(SDL2_TTF)
#find_package(SDL2_IMAGE)




PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
include_directories(${SDL2_TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "src/render/*.c" "src/game/*.c")
add_executable(2048 src/main.c ${SOURCES})
target_include_directories(2048 PRIVATE /include)

target_link_libraries(2048 ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2IMAGE_LIBRARIES} m)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})