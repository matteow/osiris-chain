 # Zbiorcza Dokumentacja Projektu Osiris Blockchain

## 1. Wprowadzenie

**Osiris** to modularny i wysoce konfigurowalny rdzeń blockchaina, napisany w C++20. Został zaprojektowany z myślą o elastyczności, umożliwiając deweloperom łatwe tworzenie i wdrażanie zdecentralizowanych aplikacji. Projekt wspiera szeroką gamę algorytmów konsensusu, posiada wbudowane mechanizmy do monitorowania, a także modularną architekturę, która pozwala na rozszerzanie funkcjonalności.

**Kluczowe cechy:**
*   **Modularność:** Jasno zdefiniowane moduły dla konsensusu, sieci (z wykorzystaniem Boost.ASIO), przechowywania danych, smart kontraktów i logiki aplikacji.
*   **Wsparcie dla wielu algorytmów konsensusu:** PoW, PoS, PoA, PBFT, Tendermint i inne.
*   **Nowoczesny C++:** Wykorzystanie standardu C++20.
*   **Kryptografia:** Oparty o sprawdzoną bibliotekę Crypto++.
*   **Konteneryzacja:** Pełne wsparcie dla Dockera i Docker Compose do łatwego wdrażania.
*   **Monitoring:** Integracja z Prometheus i Grafana.
*   **Smart Kontrakty:** Obsługa natywnych kontraktów oraz planowane wsparcie dla WebAssembly (WASM).

## 2. Architektura

Architektura systemu jest warstwowa, co zapewnia separację poszczególnych komponentów i ułatwia ich rozwój.

*   **`src/`**: Główny katalog z kodem źródłowym.
    *   **`chain.hpp/.cpp`**: Centralna logika blockchaina, zarządzanie blokami i transakcjami.
    *   **`config.hpp/.cpp`**: Parsowanie i zarządzanie konfiguracją z plików YAML.
    *   **`TransactionPool.hpp/.cpp`**: Zarządzanie pulą niepotwierdzonych transakcji.
    *   **`types.hpp`**: Definicje podstawowych struktur danych, takich jak `Block` i `Transaction`.
    *   **`consensus/`**: Implementacje algorytmów konsensusu. Każdy algorytm implementuje interfejs `IConsensus`.
    *   **`contract/`**: Silnik smart kontraktów.
    *   **`crypto/`**: Funkcje kryptograficzne, w tym generowanie kluczy i haszowanie.
    *   **`network/`**: Komunikacja P2P między węzłami, zaimplementowana przy użyciu Boost.ASIO.
    *   **`storage/`**: Warstwa abstrakcji dla baz danych (LevelDB, LMDB).
    *   **`modules/`**: Dodatkowe moduły, takie jak `social` (funkcje społecznościowe) czy `identity` (zarządzanie tożsamością).
    *   **`metrics_server/`**: Serwer metryk dla Prometheus.
*   **`tests/`**: Testy jednostkowe i integracyjne (Google Test).
*   **`config/`**: Przykładowe pliki konfiguracyjne dla różnych środowisk (dev, testnet, mainnet).
*   **`contracts/`**: Przykładowe smart kontrakty.
*   **`docs/`**: Szczegółowa dokumentacja projektu.
*   **`monitoring/`**: Konfiguracja dla Prometheus i Grafana.

## 3. Budowa i Uruchomienie

### Wymagania
*   Kompilator C++20 (GCC 12+ / Clang 15+)
*   CMake 3.20+
*   Boost 1.75+
*   Crypto++ 8.7+
*   yaml-cpp
*   LevelDB / LMDB

### Budowa z `CMake`
```bash
mkdir build
cd build
cmake ..
make
```

### Uruchomienie Węzła
```bash
./build/src/osiris-node --config config/mainnet.yaml
```

### Użycie Dockera
Projekt jest w pełni skonteneryzowany. Do uruchomienia lokalnej sieci testowej można użyć `docker-compose`:
```bash
docker-compose up -d
```

## 4. Konfiguracja

Konfiguracja węzła odbywa się za pomocą plików w formacie YAML. Główne sekcje konfiguracyjne to:
*   **`network`**: Ustawienia sieciowe (porty, adresy, węzły bootstrapowe).
*   **`consensus`**: Wybór i parametry algorytmu konsensusu.
*   **`storage`**: Typ i ścieżka bazy danych.
*   **`contracts`**: Ustawienia silnika smart kontraktów.
*   **`metrics`**: Konfiguracja serwera metryk.

## 5. Smart Kontrakty

Osiris wspiera dwa formaty smart kontraktów:
*   **`.kontrakt`**: Prosty, natywny format kontraktu (przykład: `vote.kontrakt`).
*   **`.seth`**: Bardziej zaawansowany format, przypominający składnią Solidity (przykład: `SocialContract.seth`).

## 6. Postęp i Roadmapa

Plik `progress.txt` śledzi postęp prac nad projektem, który jest już w zaawansowanej fazie. Zaimplementowano większość kluczowych funkcjonalności, a dalsze plany obejmują m.in. rozwój modułów, optymalizację i audyty bezpieczeństwa.
