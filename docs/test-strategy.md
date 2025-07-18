# Strategia Testowania w Osiris

Projekt Osiris kładzie duży nacisk na jakość kodu i stabilność, co jest osiągane przez wielopoziomową strategię testowania. Głównym frameworkiem do testów jednostkowych i integracyjnych jest Google Test (GTest).

## 1. Testy Jednostkowe (Unit Tests)

*   **Cel:** Weryfikacja poprawności działania małych, izolowanych fragmentów kodu (klas, funkcji).
*   **Lokalizacja:** `tests/`
*   **Przykłady:**
    *   `config_tests.cpp`: Testuje parsowanie plików konfiguracyjnych.
    *   `chain_tests.cpp`: Testuje logikę dodawania bloków i walidacji łańcucha.
    *   `consensus_tests.cpp`: Testuje logikę poszczególnych algorytmów konsensusu.
    *   `storage_tests.cpp`: Testuje operacje zapisu i odczytu z bazy danych.
    *   `WalletTest.cpp`: Testuje funkcjonalności portfela CLI.

## 2. Testy Integracyjne (Integration Tests)

*   **Cel:** Sprawdzenie, czy różne komponenty systemu poprawnie ze sobą współpracują.
*   **Przykłady:**
    *   Testowanie pełnego cyklu życia transakcji: od wysłania przez API, przez dodanie do bloku, po zapis w bazie danych.
    *   Testowanie synchronizacji dwóch węzłów.

## 3. Scenariusze Testowe

W pliku `tests/consensus_scenarios.test` definiowane są scenariusze dla różnych algorytmów, np.:
*   Test `BlockSizeLimit`: Sprawdza, czy węzeł odrzuca bloki większe niż dozwolony limit.
*   Test `mineBlock`: Weryfikuje, czy funkcja kopania bloku w PoW generuje poprawny hash.
*   Test `validateBlock`: Sprawdza poprawność walidacji bloków dla każdego typu konsensusu.

## 4. Jak Uruchomić Testy

### Użycie `ctest`
`ctest` to standardowe narzędzie CMake do uruchamiania testów.
```bash
# W katalogu build
ctest
```

### Użycie `make test`
Alternatywnie, można użyć celu `test` w Makefile.
```bash
# W katalogu build
make test
```

### Uruchomienie Pojedynczego Zestawu Testów
Można również uruchomić skompilowany plik wykonywalny testów, aby uzyskać bardziej szczegółowe wyniki.
```bash
./bin/osiris-tests --gtest_filter="ChainTest.*"
```
Powyższa komenda uruchomi wszystkie testy z zestawu `ChainTest`.
