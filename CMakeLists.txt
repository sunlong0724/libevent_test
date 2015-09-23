CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(libevent_test CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_FXX_FLAGS} -g -std=c++11")

#include_directories(googletest/googletest/include)
add_executable(test_timer src/test_timer.cc)
target_link_libraries(test_timer event)

add_executable(test_serv src/test_serv.cc)
target_link_libraries(test_serv event)


