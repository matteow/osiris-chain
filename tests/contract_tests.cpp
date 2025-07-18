#include <gtest/gtest.h>
#include <filesystem>
#include "../src/config.hpp"
#include "../src/contract/Engine.hpp"
#include "../src/contract/Parser.hpp"

// Define a test contracts directory
const std::string TEST_CONTRACTS_PATH = "./test_contracts";

class ContractTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clean up previous test data
        if (std::filesystem::exists(TEST_CONTRACTS_PATH)) {
            std::filesystem::remove_all(TEST_CONTRACTS_PATH);
        }
        std::filesystem::create_directories(TEST_CONTRACTS_PATH);

        // Load a default configuration for tests
        config_.load(std::string(TEST_BUILD_DIR) + "/../config/dev.yaml");

        // Initialize engine with contracts config
        engine_ = std::make_unique<osiris::contract::Engine>(config_.getContractsConfig());
    }

    void TearDown() override {
        // Clean up test data
        if (std::filesystem::exists(TEST_CONTRACTS_PATH)) {
            std::filesystem::remove_all(TEST_CONTRACTS_PATH);
        }
    }

    osiris::Config& config_ = osiris::Config::getInstance();
    std::unique_ptr<osiris::contract::Engine> engine_;
};

TEST_F(ContractTest, ParserBasicFunctionality) {
    // Note: This test assumes osiris::contract::Parser exists and works as expected.
    // The Parser.hpp defines Osiris::contract::Parser, which might be a namespace mismatch.
    // If compilation fails here, the Parser needs to be moved to osiris::contract namespace.
    Osiris::contract::Parser parser;
    std::string contract_code = R"(
contract MyContract {
    name: "TestContract"
    owner: "0x123"
    storage my_value: uint256 = 0;
    function getMyValue() -> uint256 { return my_value; }
}
    )";

    Osiris::contract::Contract parsed_contract = parser.parseContent(contract_code);
    EXPECT_EQ(parsed_contract.name, "TestContract");
    EXPECT_EQ(parsed_contract.owner, "0x123");
    EXPECT_EQ(parsed_contract.storage["my_value"], "0");
    EXPECT_EQ(parsed_contract.functions.size(), 1);
    EXPECT_EQ(parsed_contract.functions[0].name, "getMyValue");
}

TEST_F(ContractTest, EngineDeployAndCall) {
    // Create a dummy contract (bytecode and abi are placeholders)
    osiris::contract::Contract contract;
    contract.address = "0xcontract_address";
    contract.bytecode = "dummy_bytecode";
    contract.abi = "dummy_abi";

    // Deploy the contract
    EXPECT_TRUE(engine_->deployContract(contract, "0xdeployer"));

    // Call a function (assuming a simple function that doesn't require complex args)
    osiris::contract::ExecutionContext context;
    context.gas_limit = 100000;
    context.sender = "0xcaller";
    context.contract_address = contract.address;

    osiris::contract::ExecutionResult result = engine_->callFunction(
        contract.address, "dummy_function", {}, context);
    
    EXPECT_TRUE(result.success);
    EXPECT_EQ(result.gas_used, 0); // Assuming dummy function uses no gas
}
