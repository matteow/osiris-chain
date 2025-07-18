#include <gtest/gtest.h>
#include "../src/modules/osiris-cli/Wallet.hpp"
#include "../src/crypto/KeyGenerator.hpp" // For KeyGenerator

class WalletTest : public ::testing::Test {
protected:
    osiris::cli::Wallet wallet_;
};

TEST_F(WalletTest, KeyGenerationAndAddress) {
    wallet_.generateNewAccount();
    std::string address = wallet_.getAddress(0);
    EXPECT_FALSE(address.empty());
    // Base58Check addresses are typically between 26-35 characters long
    EXPECT_GE(address.length(), 26);
    EXPECT_LE(address.length(), 35);
}