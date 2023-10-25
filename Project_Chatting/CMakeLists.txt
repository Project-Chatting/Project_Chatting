cmake_minimum_required(VERSION 3.1)
project(CoolSMSSMSExample)

# Find and include libcurl
find_package(CURL REQUIRED)

# Find and include jsoncpp
find_package(Jsoncpp REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE CURL::libcurl Jsoncpp::Jsoncpp)