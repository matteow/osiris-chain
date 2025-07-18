# Przewodnik po Konfiguracji (`config.yml`)

Plik `config.yml` jest głównym plikiem konfiguracyjnym dla węzła Osiris. Pozwala na dostosowanie wszystkich aspektów działania, od sieci po algorytm konsensusu.

## Struktura Pliku
```yaml
# Konfiguracja sieciowa
network:
  listen_address: "0.0.0.0"
  port: 30303
  seeds: # Węzły startowe do połączenia
    - "ip:port"

# Konfiguracja API RPC
rpc:
  enabled: true
  listen_address: "127.0.0.1"
  port: 8080

# Konfiguracja bazy danych
database:
  path: "./data/dev" # Ścieżka do bazy danych
  type: "leveldb" # Typ: leveldb lub rocksdb

# Konfiguracja konsensusu
consensus:
  name: "PoW" # Nazwa algorytmu: PoW, PoS, PoA, PBFT, Tendermint
  params:
    # Parametry specyficzne dla algorytmu
    difficulty: 4

# Inne parametry
chain:
  max_block_size: 1048576 # 1 MB
  target_block_time: 60 # w sekundach
```

## Przykłady Konfiguracji dla Różnych Trybów

### 1. Proof of Work (PoW)
```yaml
consensus:
  name: "PoW"
  params:
    difficulty: 5
```

### 2. Proof of Stake (PoS)
```yaml
consensus:
  name: "PoS"
  params:
    stake_requirement: 1000
```

### 3. Proof of Authority (PoA)
```yaml
consensus:
  name: "PoA"
  params:
    authorities:
      - "0xAddress1..."
      - "0xAddress2..."
    block_period_seconds: 15
```

## Kluczowe Parametry
*   `network.port`: Port do komunikacji P2P.
*   `network.seeds`: Lista adresów innych węzłów do nawiązania połączenia przy starcie.
*   `rpc.enabled`: Włącza/wyłącza API JSON-RPC.
*   `database.path`: Lokalizacja, w której będą przechowywane dane blockchaina.
*   `consensus.name`: Wybór aktywnego algorytmu konsensusu.
*   `chain.max_block_size`: Maksymalny rozmiar bloku w bajtach.
