#include <gtest/gtest.h>
#include <filesystem>
#include "../src/config.hpp"
#include "../src/storage/StorageFactory.hpp"
#include "../src/storage/IStorage.hpp"
#include "../src/types.hpp"

// Define a test database path
const std::string TEST_DB_PATH = "./test_storage_db";

class StorageTest : public ::testing::Test {
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
    }

    void TearDown() override {
        // Clean up test data
        if (std::filesystem::exists(TEST_DB_PATH)) {
            std::filesystem::remove_all(TEST_DB_PATH);
        }
    }

    osiris::Config& config_ = osiris::Config::getInstance();
    std::unique_ptr<osiris::storage::IStorage> storage_;
};

TEST_F(StorageTest, BasicStateOperations) {
    // Store and retrieve a simple key-value pair
    storage_->put("test_key", "test_value");
    EXPECT_EQ(storage_->get("test_key"), "test_value");

    // Check for existence (by checking if get returns empty string or specific default)
    // Assuming get returns empty string if key does not exist
    EXPECT_FALSE(storage_->get("test_key").empty());
    EXPECT_TRUE(storage_->get("nonexistent_key").empty());

    // Delete a key
    storage_->remove("test_key");
    EXPECT_TRUE(storage_->get("test_key").empty());
}

TEST_F(StorageTest, BlockStorageOperations) {
    osiris::Block block;
    block.number = 1;
    block.hash = "0xblockhash1";
    block.prev_hash = "0xprevhash0";
    block.timestamp = 123456789;
    block.data = "some block data";
    block.nonce = 123;
    block.difficulty = 100;
    block.merkleRoot = "0xmerkle";
    // No transactions for simplicity in this test

    storage_->addBlock(block);

    // getBlock by hash is not directly available in IStorage, so we test getLatestBlock
    // This test might need to be adjusted if specific block retrieval by hash is required.
    auto retrieved_block = storage_->getLatestBlock();
    EXPECT_EQ(retrieved_block.number, block.number);
    EXPECT_EQ(retrieved_block.hash, block.hash);
    EXPECT_EQ(retrieved_block.prev_hash, block.prev_hash);
}

TEST_F(StorageTest, TransactionStorageOperations) {
    osiris::Transaction tx;
    tx.from = "0xsender";
    tx.to = "0xreceiver";
    tx.amount = 100.0;
    tx.timestamp = 987654321;
    tx.senderPublicKey = "pubkey";
    tx.signature = "signature";

    storage_->storeTransaction(tx);

    auto retrieved_tx = storage_->getTransaction(tx.computeHash());
    EXPECT_EQ(retrieved_tx.from, tx.from);
    EXPECT_EQ(retrieved_tx.to, tx.to);
    EXPECT_EQ(retrieved_tx.amount, tx.amount);
}