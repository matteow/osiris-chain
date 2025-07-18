WORKING DIRECTORY v0.10
# Osiris Blockchain (`osiris-core`)

**Opis:** Modularny blockchain napisany w C++20, wspierający różne algorytmy konsensusu (PoW, PoS, PoA, PBFT, Tendermint), zaawansowaną kryptografię, monitorowanie Prometheus, API i systemy społeczne.

**Struktura katalogów:**
*   `src/consensus/`: Implementacje algorytmów konsensusu.
*   `src/modules/`: Moduły funkcjonalne, np. `social`, `identity`.
*   `src/crypto/`: Funkcje i klasy kryptograficzne.
*   `src/network/`: Komunikacja P2P i API.
*   `src/storage/`: Warstwa przechowywania danych.
*   `docs/`: Szczegółowa dokumentacja projektu.

**Wymagania systemowe:**
*   Kompilator C++20 (GCC 12+ / Clang 15+)
*   CMake 3.20+
*   Boost 1.75+
*   Crypto++ 8.7+

**Instrukcja budowania:**
```bash
mkdir build
cd build
cmake ..
make
```

**Jak uruchomić node:**
```bash
./build/bin/osiris-node --config config/mainnet.yaml
```

**Tryby konsensusu:**
Konfiguracja odbywa się w pliku `config.yml`. Dostępne tryby: `PoW`, `PoS`, `PoA`, `PBFT`, `Tendermint`.

**Licencja:**
[TODO: Dodaj licencję, np. MIT]

**Kontakt i zespół:**
*   **Architekt:** Mateusz Wojtyś
