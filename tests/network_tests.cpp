#include <gtest/gtest.h>
#include <filesystem>
#include <thread>
#include <chrono>

#include "../src/config.hpp"
#include "../src/chain.hpp"
#include "../src/network/P2PNode.hpp"
#include "../src/storage/StorageFactory.hpp"
#include "../src/consensus/ConsensusFactory.hpp"
#include "../src/consensus/PoW.hpp"

// Define a test database path
const std::string TEST_DB_PATH = "./test_network_db";

class NetworkTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clean up previous test data
        if (std::filesystem::exists(TEST_DB_PATH)) {
            std::filesystem::remove_all(TEST_DB_PATH);
        }

        // Load a default configuration for tests
        config_.load(std::string(TEST_BUILD_DIR) + "/../config/dev.yaml");

        // Create storage instance
        storage_ = osiris::storage::StorageFactory::create(config_.getStorageType());
        chain_ = std::make_unique<osiris::Chain>(std::move(storage_));

        // Create a dummy consensus for the P2PNode
        consensus_ = osiris::consensus::ConsensusFactory::create("PoW", *chain_, config_);
    }

    void TearDown() override {
        // Clean up test data
        if (std::filesystem::exists(TEST_DB_PATH)) {
            std::filesystem::remove_all(TEST_DB_PATH);
        }
    }

    osiris::Config& config_ = osiris::Config::getInstance();
    std::unique_ptr<osiris::storage::IStorage> storage_;
    std::unique_ptr<osiris::Chain> chain_;
    std::unique_ptr<osiris::consensus::IConsensus> consensus_;
};

TEST_F(NetworkTest, P2PNodeInitialization) {
    osiris::network::P2PNode node(config_.getNetworkConfig(), *chain_, *consensus_);
    // Node should not be running immediately after initialization
    // EXPECT_FALSE(node.isRunning()); // P2PNode does not have isRunning()
}

TEST_F(NetworkTest, P2PNodeStartStop) {
    osiris::network::P2PNode node(config_.getNetworkConfig(), *chain_, *consensus_);
    node.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Give it a moment to start
    node.stop();
    // No direct way to check if it's stopped without isRunning() method
}

// Add more tests for P2P communication, block broadcasting, etc.
// These would require setting up multiple nodes and simulating network interactions,
// which is more complex and might be better suited for integration tests.
