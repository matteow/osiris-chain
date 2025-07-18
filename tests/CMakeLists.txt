cmake_minimum_required(VERSION 3.18)

project(osiris-tests)

set(TEST_SOURCES
    config_tests.cpp
    consensus_tests.cpp
    contract_tests.cpp
    network_tests.cpp
    storage_tests.cpp
    metrics_tests.cpp
    ChainTest.cpp
    WalletTest.cpp
    main_test.cpp
)

foreach(TEST_FILE ${TEST_SOURCES})
    string(REPLACE ".cpp" "" TEST_NAME ${TEST_FILE})
    add_executable(${TEST_NAME} ${TEST_FILE})
    set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(${TEST_NAME}
        osiris-core
        nlohmann_json
        osiris-consensus
        osiris-contract
        osiris-network
        osiris-metrics-server
        osiris-storage
        osiris-modules # This includes osiris-cli if it's enabled
        gtest_main
        gmock_main
        osiris-storage
        ${CRYPTOPP_LIBRARY}
    )
    target_include_directories(${TEST_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${prometheus-cpp_SOURCE_DIR}/3rdparty/googletest/googletest/include
        ${prometheus-cpp_SOURCE_DIR}/3rdparty/googletest/googlemock/include
        ${cryptopp_SOURCE_DIR}
        ${json_SOURCE_DIR}/include
    )

target_compile_definitions(${TEST_NAME} PRIVATE "CMAKE_SOURCE_DIR=\"${CMAKE_SOURCE_DIR}\"")
target_compile_definitions(${TEST_NAME} PRIVATE "TEST_BUILD_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"")
    add_test(NAME ${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}>)
endforeach()