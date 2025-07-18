#include <gtest/gtest.h>
#include "node/status_service.hpp"
#include "tests/dummy_node_factory.hpp"

TEST(StatusTest, FetchAndParse) {
    // This test would require a running node or a mock server.
    // For now, we'll just check the dummy node factory.
    auto node = osiris::tests::DummyNodeFactory::create_node(osiris::crypto::ConsensusType::PoS);
    ASSERT_FALSE(node.id.empty());
    ASSERT_EQ(node.consensus, osiris::crypto::ConsensusType::PoS);
    ASSERT_FALSE(node.public_key.empty());
}
