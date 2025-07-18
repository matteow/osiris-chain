# Osiris-Core C++ Light Wallet & Node

##  Core Design Principles of Osiris Core

Osiris Core is a modular, blockchain-integrated framework designed to power decentralized applications, with strong separation of logic, chain storage, and interface.

### ✅ Architecture Overview
- **Language:** C++ (core modules), TypeScript (interfaces), optional Rust bindings
- **Filesystem structure:**
```
/osiris-core
├── /modules
│   ├── /social
│   │   ├── post.cpp
│   │   ├── like.cpp
│   │   ├── comment.cpp
│   │   ├── identity.cpp
│   │   └── storage.cpp
│   ├── /wallet
│   └── /chain
├── core.cpp
├── main.cpp
├── CMakeLists.txt
```

---

##  Identity and Address
Each action (post, like, comment, etc.) is associated with a **user wallet address**.
This acts as the user's ID and can serve in any context (auth, ownership, traceability).

---

##  /modules/social

Module for social media-like features:

### Features:
- `post.cpp`: create/edit posts
- `like.cpp`: like/unlike content
- `comment.cpp`: threaded comments
- `identity.cpp`: wallet address to profile mapping
- `storage.cpp`: on-disk + on-chain hybrid storage

### Usage:
- Posts and interactions are stored locally and optionally broadcasted to Social-Chain
- All content linked to wallet-generated address
- Modules exposed as callable C++ classes (e.g. `PostManager`, `LikeHandler`)

---

##  Build & Extend

### Easy to build C++ modules:
Each file in `/modules` is self-contained and extendable with clear interfaces.
E.g. add `/modules/trust/trust.cpp` for reputation logic, or `/modules/feed/feed.cpp` for public timeline.

### Integration:
- `main.cpp` compiles all modules into a CLI
- CMake-based build system

---

##  Periodic Tools
- Progress log: `@progress.txt`
- File tree dump: `tree > tree.md`
- Core design: `@osiris_core_design.md`

---

##  Next Steps:
- [ ] Finalize base classes in `social` module
- [ ] Implement `PostManager` and `CommentManager`
- [ ] Define sync-to-chain function interface
- [ ] Connect `identity.cpp` to wallet module