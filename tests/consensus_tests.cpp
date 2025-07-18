#include <gtest/gtest.h>
#include <filesystem>
#include "../src/consensus/ConsensusFactory.hpp"
#include "../src/consensus/PoW.hpp"
#include "../src/consensus/PoS.hpp"
#include "../src/chain.hpp"
#include "../src/config.hpp"
#include "../src/storage/StorageFactory.hpp"

// Define a test database path
const std::string TEST_DB_PATH = "./test_consensus_db";

class ConsensusTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clean up previous test data
        if (std::filesystem::exists(TEST_DB_PATH)) {
            std::filesystem::remove_all(TEST_DB_PATH);
        }

        // Load a default configuration for tests
        config_.load(std::string(TEST_BUILD_DIR) + "/../config/dev.yaml");

        // Override some config values for testing purposes
        // Note: Direct modification of config_ members is not allowed for singleton
        // We assume dev.yaml provides reasonable defaults or we load specific test configs

        // Create storage instance
        storage_ = osiris::storage::StorageFactory::create(config_.getStorageType());
        chain_ = std::make_unique<osiris::Chain>(std::move(storage_));
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
};

TEST_F(ConsensusTest, PoWConsensusCreation) {
    // Ensure PoW can be created
    std::unique_ptr<osiris::consensus::IConsensus> pow_consensus = 
        osiris::consensus::ConsensusFactory::create("PoW", *chain_, config_);
    EXPECT_NE(pow_consensus, nullptr);
    EXPECT_EQ(pow_consensus->getAlgorithmName(), "PoW");
}

TEST_F(ConsensusTest, PoSConsensusCreation) {
    // Ensure PoS can be created
    std::unique_ptr<osiris::consensus::IConsensus> pos_consensus = 
        osiris::consensus::ConsensusFactory::create("PoS", *chain_, config_);
    EXPECT_NE(pos_consensus, nullptr);
    EXPECT_EQ(pos_consensus->getAlgorithmName(), "PoS");
}

TEST_F(ConsensusTest, PoWBlockMining) {
    std::unique_ptr<osiris::consensus::IConsensus> pow_consensus = 
        osiris::consensus::ConsensusFactory::create("PoW", *chain_, config_);
    
    // Create a dummy transaction
    osiris::Transaction tx;
    tx.from = "test_sender";
    tx.to = "test_receiver";
    tx.amount = 10.0;
    tx.timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                       std::chrono::system_clock::now().time_since_epoch()).count();
    tx.senderPublicKey = "dummy_public_key";
    tx.signature = "dummy_signature";

    std::vector<osiris::Transaction> transactions;
    transactions.push_back(tx);

    osiris::Block new_block = pow_consensus->createNewBlock(transactions);
    EXPECT_EQ(new_block.number, 1);
    EXPECT_FALSE(new_block.hash.empty());
    EXPECT_EQ(new_block.transactions.size(), 1);
}

TEST_F(ConsensusTest, PoSBlockMining) {
    std::unique_ptr<osiris::consensus::IConsensus> pos_consensus = 
        osiris::consensus::ConsensusFactory::create("PoS", *chain_, config_);
    
    // Create a dummy transaction
    osiris::Transaction tx;
    tx.from = "test_sender";
    tx.to = "test_receiver";
    tx.amount = 10.0;
    tx.timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                       std::chrono::system_clock::now().time_since_epoch()).count();
    tx.senderPublicKey = "dummy_public_key";
    tx.signature = "dummy_signature";

    std::vector<osiris::Transaction> transactions;
    transactions.push_back(tx);

    osiris::Block new_block = pos_consensus->createNewBlock(transactions);
    EXPECT_EQ(new_block.number, 1);
    EXPECT_FALSE(new_block.hash.empty());
    EXPECT_EQ(new_block.transactions.size(), 1);
}

TEST_F(ConsensusTest, PoWBlockValidation) {
    std::unique_ptr<osiris::consensus::IConsensus> pow_consensus = 
        osiris::consensus::ConsensusFactory::create("PoW", *chain_, config_);
    
    // Create a dummy transaction
    osiris::Transaction tx;
    tx.from = "test_sender";
    tx.to = "test_receiver";
    tx.amount = 10.0;
    tx.timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                       std::chrono::system_clock::now().time_since_epoch()).count();
    tx.senderPublicKey = "dummy_public_key";
    tx.signature = "dummy_signature";

    std::vector<osiris::Transaction> transactions;
    transactions.push_back(tx);

    osiris::Block new_block = pow_consensus->createNewBlock(transactions);
    EXPECT_TRUE(pow_consensus->validateBlock(new_block));
}

TEST_F(ConsensusTest, PoSBlockValidation) {
    std::unique_ptr<osiris::consensus::IConsensus> pos_consensus = 
        osiris::consensus::ConsensusFactory::create("PoS", *chain_, config_);
    
    // Create a dummy transaction
    osiris::Transaction tx;
    tx.from = "test_sender";
    tx.to = "test_receiver";
    tx.amount = 10.0;
    tx.timestamp = std::chrono::duration_cast<std::chrono::seconds>(
                       std::chrono::system_clock::now().time_since_epoch()).count();
    tx.senderPublicKey = "dummy_public_key";
    tx.signature = "dummy_signature";

    std::vector<osiris::Transaction> transactions;
    transactions.push_back(tx);

    osiris::Block new_block = pos_consensus->createNewBlock(transactions);
    EXPECT_TRUE(pos_consensus->validateBlock(new_block));
}