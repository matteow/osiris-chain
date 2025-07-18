#include <gtest/gtest.h>
#include <filesystem>
#include "../src/chain.hpp"
#include "../src/config.hpp"
#include "../src/storage/StorageFactory.hpp"

class ChainTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a dummy config for storage
        config_.load("../config/dev.yaml");
        storage_ = osiris::storage::StorageFactory::create(config_.getStorageType());
    }

    void TearDown() override {
        // Cleanup test data
        std::filesystem::remove_all("./test_data");
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
    chain.addTransactionToPool(tx);
    EXPECT_EQ(chain.getTransactionPool().size(), 1);
}