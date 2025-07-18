#include "dummy_node_factory.hpp"
#include "crypto/key_generator.hpp"
#include <random>
#include <sstream>

namespace osiris::tests {

std::string generate_uuid() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    std::stringstream ss;
    for (int i = 0; i < 32; i++) {
        ss << std::hex << dis(gen);
    }
    return ss.str();
}

DummyNode DummyNodeFactory::create_node(crypto::ConsensusType type) {
    DummyNode node;
    node.id = generate_uuid();
    node.consensus = type;

    std::vector<std::string> params;
    switch(type) {
        case crypto::ConsensusType::PoW:
            params.push_back("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
            params.push_back("12345");
            break;
        case crypto::ConsensusType::PoS:
            params.push_back("1000000");
            params.push_back("osiris1abcdefg");
            break;
        case crypto::ConsensusType::Custom:
            params.push_back("a1b2c3d4");
            params.push_back("54321");
            break;
        default:
            // Add other consensus types here
            break;
    }
    node.public_key = crypto::KeyGenerator::generate_address(type, params);

    return node;
}

}
