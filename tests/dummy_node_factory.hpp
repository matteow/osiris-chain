#pragma once

#include "consensus/ConsensusType.hpp"
#include <string>

namespace osiris::tests {

struct DummyNode {
    std::string id;
    crypto::ConsensusType consensus;
    std::string public_key;
};

class DummyNodeFactory {
public:
    static DummyNode create_node(crypto::ConsensusType type);
};

}
