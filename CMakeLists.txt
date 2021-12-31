cmake_minimum_required(VERSION 3.0.0)

project(DicomClassifier VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define sources
file(GLOB_RECURSE SOURCES_FILES
    "DicomClassifier/*.cpp"
    "DicomClassifier/*.cxx"
)

# Define headers
file(GLOB_RECURSE HEADERS_FILES
    "*.h"
    "*.hpp"
)

# Set sources
add_library(DicomClassifier STATIC "${SOURCES_FILES}")

# Include dirs
include_directories(DicomClassifier)


# C++ flags
set(USE_PTHREAD ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")






