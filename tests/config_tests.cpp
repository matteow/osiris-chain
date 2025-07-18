// tests/config_tests.cpp

#include <gtest/gtest.h>
#include <fstream>
#include <filesystem> // Potrzebne do std::filesystem::remove
#include "../src/config.hpp" // Ścieżka do pliku nagłówkowego Config

// Definicja testu ConfigTest
// Usuwamy SetUp i TearDown, ponieważ będziemy ładować konkretny plik
class ConfigTest : public ::testing::Test {};

// Test ładowania pliku konfiguracyjnego
TEST_F(ConfigTest, LoadFromFile) {
    osiris::Config& config = osiris::Config::getInstance();
    // Używamy CMAKE_SOURCE_DIR, aby uzyskać ścieżkę do katalogu głównego projektu
    // i załadować config/dev.yaml
    // WAŻNE: CMAKE_SOURCE_DIR musi być przekazane przez CMake do kompilatora jako definicja
    // Jeśli nie jest, będziemy musieli to dodać do CMakeLists.txt
    // Na razie zakładam, że jest dostępne lub zostanie dodane.
    // Poprawiona linia: usunięto podwójny średnik
    EXPECT_TRUE(config.load(std::string(TEST_BUILD_DIR) + "/../config/dev.yaml"));

    // Poniżej asercje, które muszą być zgodne z config/dev.yaml
    // Zaktualizuj je, jeśli zmienisz config/dev.yaml
    EXPECT_EQ(config.getNetworkConfig().listen_address, "127.0.0.1");
    EXPECT_EQ(config.getNetworkConfig().listen_port, 30333);
    EXPECT_EQ(config.getNetworkConfig().p2p_port, 30333);
    EXPECT_EQ(config.getNetworkConfig().rpc_port, 8545);
    EXPECT_EQ(config.getNetworkConfig().max_peers, 10);
    EXPECT_EQ(config.getNetworkConfig().block_time_ms, 1000);
    EXPECT_EQ(config.getNetworkConfig().maxBlockSizeBytes, 1048576);

    // Zgodnie z config/dev.yaml, typ konsensusu to "PoA"
    EXPECT_EQ(config.getConsensusConfig().type, "PoA");
    EXPECT_EQ(config.getConsensusConfig().name, "PoA"); // Dodana asercja dla 'name'
    EXPECT_EQ(config.getConsensusConfig().pow.difficulty, 1);
    EXPECT_EQ(config.getConsensusConfig().pos.min_stake, 100.0);
    // Sprawdź, czy validators są poprawnie wczytywane
    EXPECT_EQ(config.getConsensusConfig().validators.size(), 2);
    EXPECT_EQ(config.getConsensusConfig().validators[0], "0x1111111111111111111111111111111111111111");
    EXPECT_EQ(config.getConsensusConfig().validators[1], "0x2222222222222222222222222222222222222222");


    // Zgodnie z config/dev.yaml, typ storage to "leveldb"
    EXPECT_EQ(config.getStorageType(), "leveldb");
    EXPECT_EQ(config.getStorageConfig().path, "./test_db");
    EXPECT_EQ(config.getStorageConfig().cache_size_mb, 64);

    // Sekcja metrics
    EXPECT_EQ(config.getMetricsConfig().listen_address, "127.0.0.1");
    EXPECT_EQ(config.getMetricsConfig().listen_port, 9090);

    // Sekcja contracts
    EXPECT_EQ(config.getContractsConfig().path, "/etc/osiris-core/contracts");
    EXPECT_EQ(config.getContractsConfig().engine, "wasm3");
    EXPECT_EQ(config.getContractsConfig().gas_limit, 20000000);
    EXPECT_EQ(config.getContractsConfig().max_contract_size, 2097152);

    // Sekcja logging (jeśli Config ją obsługuje)
    EXPECT_EQ(config.getLoggingConfig().level, "debug");
    EXPECT_EQ(config.getLoggingConfig().file, "/var/lib/osiris/osiris-dev.log");
    EXPECT_EQ(config.getLoggingConfig().max_size_mb, 50);
}

// Test ładowania nieistniejącego pliku (pozostaje bez zmian)
TEST_F(ConfigTest, LoadNonExistentFile) {
    osiris::Config& config = osiris::Config::getInstance();
    EXPECT_FALSE(config.load("nonexistent.yaml"));
}