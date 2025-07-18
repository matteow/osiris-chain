cmake_minimum_required(VERSION 3.18)
project(osiris-core VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(/usr/include)

enable_testing()

include(FetchContent)


FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2 # Use a specific tag for stability
)
FetchContent_MakeAvailable(json)
set(JSON_Build_Tests OFF CACHE BOOL "" FORCE) # Disable tests
set(JSON_Build_Examples OFF CACHE BOOL "" FORCE) # Disable examples

# FetchContent for httplib

set(CPPHTTPLIB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Disable examples
set(CPPHTTPLIB_BUILD_TESTS OFF CACHE BOOL "" FORCE) # Disable examples

# FetchContent for prometheus-cpp
FetchContent_Declare(
    prometheus-cpp
    GIT_REPOSITORY https://github.com/jupp0r/prometheus-cpp.git
    GIT_TAG v1.0.0 # Use a specific tag for stability
)
FetchContent_MakeAvailable(prometheus-cpp)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) # Build static
set(BUILD_TESTING OFF CACHE BOOL "" FORCE) # Disable tests
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Disable examples

# Find dependencies (these will now use FetchContent targets if available)
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(yaml-cpp REQUIRED)
find_package(ZLIB REQUIRED)
find_package(CURL REQUIRED)

add_subdirectory(src)
add_subdirectory(tests) # Added
# Dodany przez run_debug.sh - Weryfikuje konfigurację YAML przed buildem
add_custom_target(check_config ALL
  COMMAND ${CMAKE_COMMAND} -E echo "Validating YAML config..."
add_custom_target(check_config ALL)
  COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=$ENV{PYTHONPATH} python3 ${CMAKE_SOURCE_DIR}/cmake/check_yaml.py
  COMMENT "Checking YAML configuration syntax"
)

