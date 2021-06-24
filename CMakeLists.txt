SET(PROJECTNAME example)
PROJECT(${PROJECTNAME})

CMAKE_MINIMUM_REQUIRED(VERSION 3.16.3)

INCLUDE_DIRECTORIES("./src")
INCLUDE_DIRECTORIES("./src/utils")
# add_executable(${PROJECTNAME} src/main.cpp)

AUX_SOURCE_DIRECTORY(./src DIR_MAIN_SRCS)
AUX_SOURCE_DIRECTORY(./src/utils DIR_MAIN_UTILS_SRCS)
AUX_SOURCE_DIRECTORY(./src/crypto DIR_MAIN_CRYPTO_SRCS)

ADD_EXECUTABLE(${PROJECTNAME} 
                    ${DIR_MAIN_SRCS} 
                    ${DIR_MAIN_UTILS_SRCS}
                    ${DIR_MAIN_CRYPTO_SRCS}
                    )

# Enable ExternalProject CMake module
include(ExternalProject)

# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_SOURCE_DIR}/src/rust)

# Add librustbellman as a CMake target
ExternalProject_Add(
    librustbellman
    DOWNLOAD_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND cargo build #COMMAND cargo build --release
    UPDATE_COMMAND cargo build #COMMAND cargo build --release
    BINARY_DIR "${CMAKE_SOURCE_DIR}/src/rust"
    INSTALL_COMMAND ""
    ALWAYS TRUE
    LOG_BUILD ON)

# Create dependency of Example on librustbellman
add_dependencies(${PROJECTNAME} librustbellman)

# message(${CMAKE_SOURCE_DIR})

# Specify Example's link libraries
target_link_libraries(${PROJECTNAME}
    debug "${CMAKE_SOURCE_DIR}/src/rust/target/debug/librustbellman.a"
    optimized "${CMAKE_SOURCE_DIR}/src/rust/target/release/librustbellman.a")

# set_target_properties(Example PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
TARGET_LINK_LIBRARIES(${PROJECTNAME} -lpthread)
TARGET_LINK_LIBRARIES(${PROJECTNAME} -ldl)
