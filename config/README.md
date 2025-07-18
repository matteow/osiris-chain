# config/ - Configuration Files

This directory contains various configuration files for the Osiris blockchain node. These files define different operational parameters, network settings, and module-specific configurations.

## Key Files:

- `dev.yaml`: Configuration for development environments.
- `mainnet.yaml`: Configuration for the main Osiris network.
- `node1.yaml`, `node2.yaml`, `node3.yaml`: Example configurations for individual nodes in a multi-node setup, often used for testing or specific deployments.
- `config.yaml`: A general or default configuration file.
- `config.tests.yaml`: Configuration specifically used for running tests.

## Advanced Documentation:

### Configuration Structure

- **YAML Format:** All configuration files are in YAML format. Details on the expected structure and data types for each section.
- **Sections:** Explanation of major configuration sections, such as:
    - `network`: Network listening ports, peer discovery settings, and connection limits.
    - `storage`: Database paths, type of storage backend (LevelDB, LMDB), and caching settings.
    - `consensus`: Chosen consensus algorithm and its specific parameters (e.g., PoW difficulty, PoS stake requirements).
    - `rpc`: RPC API settings, including port, enabled methods, and access control.
    - `logging`: Log levels, output destinations, and rotation policies.
    - `modules`: Configuration specific to various modules (e.g., social module settings, identity contract addresses).

### Overriding Configurations

- **Precedence:** Explains the order of precedence for loading configuration files (e.g., command-line arguments overriding environment variables, which override default config files).
- **Environment-Specific Settings:** How to manage different configurations for development, testing, and production environments.

### Security Considerations

- **Sensitive Information:** Guidelines on handling sensitive information (e.g., private keys, API tokens) in configuration files, recommending environment variables or secure vaults for production.
- **Access Control:** How to configure network and RPC access controls to prevent unauthorized access.
