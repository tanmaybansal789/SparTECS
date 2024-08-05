cmake_minimum_required(VERSION 3.16)

project(SparTECS)

# enable AddressSanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files
set(SOURCES src/Entity.cpp)

# Add the header files
set(HEADERS
        include/SparTECS/Context.h
        include/SparTECS/Entity.h
        include/SparTECS/EventManager.h
        include/SparTECS/Events.h
        include/SparTECS/Group.h
        include/SparTECS/Pool.h

        src/Context.tpp
        src/EventManager.tpp
        src/Group.tpp
        src/Pool.tpp

        include/SparTECS/SparTECS.h
)

# Include directories
include_directories(include)
include_directories(include/SparTECS)
include_directories(src)

# Create the library
add_library(SparTECS STATIC ${SOURCES} ${HEADERS})

# Optionally, you can specify where to place the library
# set_target_properties(SparTECS PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
# )

# If you have a test or example main.cpp, you can create a separate executable for it
# add_executable(SparTECSExample main.cpp)
# target_link_libraries(SparTECSExample PRIVATE SparTECS)