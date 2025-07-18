#include <gtest/gtest.h>
#include <filesystem>
#include "../src/chain.hpp"
#include "../src/config.hpp"
#include "../src/storage/StorageFactory.hpp"

// Define a test database path
const std::string TEST_DB_PATH = "./test_chain_db";

class ChainTest : public ::testing::Test {
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

TEST_F(ChainTest, InitializationTest) {
    EXPECT_NO_THROW({
        osiris::Chain chain(std::move(storage_));
    });
}

TEST_F(ChainTest, GenesisBlockTest) {
    osiris::Chain chain(std::move(storage_));
    auto genesis = chain.getLatestBlock();
    EXPECT_EQ(genesis.number, 0);
}

TEST_F(ChainTest, TransactionTest) {
    osiris::Chain chain(std::move(storage_));
    osiris::Transaction tx;
    tx.from = "0x1111111111111111111111111111111111111111";
    tx.to = "0x2222222222222222222222222222222222222222";
    tx.amount = 1000;
    tx.timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                       std::chrono::system_clock::now().time_since_epoch()).count();
    tx.senderPublicKey = "dummy_public_key";
    tx.signature = "dummy_signature";

    chain.addTransactionToPool(tx);
    EXPECT_EQ(chain.getTransactionPool().size(), 1);
}

TEST_F(ChainTest, BlockMiningTest) {
    osiris::Chain chain(std::move(storage_));
    
    // Add a transaction
    osiris::Transaction tx;
    tx.from = "0x1111111111111111111111111111111111111111";
    tx.to = "0x2222222222222222222222222222222222222222";
    tx.amount = 1000;
    tx.timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                       std::chrono::system_clock::now().time_since_epoch()).count();
    tx.senderPublicKey = "dummy_public_key";
    tx.signature = "dummy_signature";
    
    chain.addTransactionToPool(tx);
    
    // Mine a block
    osiris::Block block_template;
    block_template.number = chain.getLatestBlock().number + 1;
    block_template.prev_hash = chain.getLatestBlock().hash;
    block_template.timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                                   std::chrono::system_clock::now().time_since_epoch()).count();
    block_template.data = "mined block";
    block_template.nonce = 0; // Will be updated by miner
    block_template.difficulty = config_.getConsensusConfig().pow.difficulty;
    block_template.merkleRoot = ""; // Will be updated after transactions

    osiris::Block new_block = chain.mineBlock(block_template);
    EXPECT_EQ(new_block.number, 1);
    EXPECT_FALSE(new_block.hash.empty());
    EXPECT_EQ(new_block.transactions.size(), 1);
    
    // Add the block to chain
    chain.addBlock(new_block);
    EXPECT_EQ(chain.getLatestBlock().number, 1);
    
    // Pending transactions should be empty now
    EXPECT_EQ(chain.getTransactionPool().size(), 0);
}
