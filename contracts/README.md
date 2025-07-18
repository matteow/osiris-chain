# contracts/ - Seth Smart Contracts

This directory contains example smart contracts written in the Seth Domain Specific Language (DSL). These contracts demonstrate various functionalities and serve as a reference for developing decentralized applications on the Osiris blockchain.

## Key Files:

- `vote.kontrakt`: An example smart contract demonstrating a basic voting mechanism.
- `SocialContract.seth`: A placeholder smart contract defining data structures and functions for social media-like interactions (posts, comments, likes, identities) on the Seth blockchain.

## Advanced Documentation:

### Seth DSL Examples

- **Syntax and Semantics:** Provides practical examples of Seth DSL syntax, illustrating how to define data structures, functions, events, and state variables within a smart contract.
- **Contract Logic:** Explains the business logic implemented in each example contract, such as how votes are cast and tallied in `vote.kontrakt`, or how social data is managed in `SocialContract.seth`.
- **Best Practices:** Highlights best practices for writing secure, efficient, and upgradeable Seth smart contracts.

### Contract Deployment

- **Compilation:** Describes the process of compiling Seth DSL code into WebAssembly (Wasm) bytecode, which is executable on the Seth Virtual Machine.
- **Deployment Process:** Explains how compiled smart contracts are deployed to the Osiris blockchain, including the necessary transaction parameters and network interactions.

### Contract Interaction

- **Function Calls:** Details how external applications or other smart contracts can call functions within a deployed Seth contract, including parameter encoding and return value decoding.
- **Event Handling:** Explains how to subscribe to and process events emitted by Seth smart contracts, enabling real-time updates and off-chain data processing.
- **State Queries:** Describes how to query the state of a deployed smart contract to retrieve information stored on-chain.
