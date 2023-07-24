cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

project(video)
#project(music)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(/home/china/arm-jpeg/include ./include)

#add_executable(${PROJECT_NAME} main.cc src/madplay.cc src/DCList.cc src/lcd.cc src/ts.cc)
add_executable(${PROJECT_NAME} main.cc src/mplayer.cc src/DCList.cc src/lcd.cc src/ts.cc)

find_library(jpeg_lib NAMES jpeg PATHS /home/china/arm-jpeg/lib)

target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads ${jpeg_lib})

