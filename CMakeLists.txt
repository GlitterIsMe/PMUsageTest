#cmake_minimum_required(VERSION 3.13)
#project(pmemtest)

#set(CMAKE_CXX_STANDARD 14)

#add_executable(pmemtest main.cpp)

cmake_minimum_required(VERSION 3.3)
project(pmemtest)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

include(FindThreads)

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(LIBPMEM REQUIRED libpmem)
else()
    find_package(LIBPMEM REQUIRED)
endif()

link_directories(${LIBPMEM_LIBRARY_DIRS})

add_executable(pmemtest main.cpp)
target_include_directories(pmemtest PUBLIC ${LIBPMEM_INCLUDE_DIRS} . ..)
target_link_libraries(pmemtest ${LIBPMEM_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})