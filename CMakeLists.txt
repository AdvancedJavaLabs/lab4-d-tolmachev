cmake_minimum_required (VERSION 3.15)

project(lab4)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(HADOOP_INCLUDE_DIR ${HADOOP_INSTALL_DIR}/include)
set(HADOOP_LIBRARY_DIR ${HADOOP_INSTALL_DIR}/lib/native)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(NTIRPC REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

include_directories(${HADOOP_INCLUDE_DIR})
link_directories(${HADOOP_LIBRARY_DIR})

add_executable(aggregate
    src/aggregate.cpp
    src/mapper.cpp
    src/mapper.hpp
    src/reducer.cpp
    src/reducer.hpp
)
add_executable(sort
    src/mapper.cpp
    src/mapper.hpp
    src/partitioner.cpp
    src/partitioner.hpp
    src/reducer.cpp
    src/reducer.hpp
    src/sort.cpp
)

target_link_libraries(aggregate PRIVATE hadoop hadooppipes hadooputils ${NTIRPC_LIBRARY} OpenSSL::Crypto OpenSSL::SSL Threads::Threads)
target_link_libraries(sort PRIVATE hadoop hadooppipes hadooputils ${NTIRPC_LIBRARY} OpenSSL::Crypto OpenSSL::SSL Threads::Threads)
