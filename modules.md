# Moduły Funkcjonalne Osiris

Osiris jest zbudowany z niezależnych modułów, które można łatwo rozwijać i modyfikować. Poniżej znajduje się opis głównych modułów i ich integracji.

## 1. `social`
*   **Opis:** Implementuje funkcjonalności zdecentralizowanych mediów społecznościowych, takie jak posty, komentarze, głosy i profile użytkowników.
*   **Integracja:** Działa na warstwie aplikacji, definiując własne typy transakcji, które są przetwarzane przez silnik kontraktów lub bezpośrednio przez logikę walidacji bloku.

## 2. `identity`
*   **Opis:** Moduł do zarządzania zdecentralizowaną tożsamością (DID). Umożliwia tworzenie, aktualizację i weryfikację tożsamości cyfrowych.
*   **Integracja:** Dostarcza funkcje kryptograficzne i struktury danych do zarządzania kluczami i atrybutami tożsamości.

## 3. `contract`
*   **Opis:** Silnik smart kontraktów. Obecnie wspiera prosty, natywny język skryptowy, z planami na integrację WebAssembly (WASM).
*   **Integracja:** Jest wywoływany podczas walidacji bloku do wykonania kodu kontraktu powiązanego z transakcją. Interfejs `Engine` zarządza stanem kontraktów.

## 4. `network`
*   **Opis:** Zarządza komunikacją P2P (peer-to-peer) między węzłami. Odpowiada za odkrywanie peerów, synchronizację blockchaina oraz propagację transakcji i bloków.
*   **Integracja:** Używa biblioteki Boost.ASIO do asynchronicznej obsługi sieci. Komunikuje się z warstwą konsensusu i pulą transakcji.

## 5. `storage`
*   **Opis:** Warstwa abstrakcji dla bazy danych. Odpowiada za zapisywanie i odczytywanie bloków, transakcji i metadanych łańcucha.
*   **Integracja:** Domyślnie używa LevelDB lub RocksDB. Dostarcza prosty interfejs `put(key, value)` i `get(key)`.

## 6. `metrics_server`
*   **Opis:** Wbudowany serwer metryk kompatybilny z Prometheus. Eksportuje kluczowe wskaźniki wydajności węzła, takie jak wysokość łańcucha, liczba transakcji w puli czy czas walidacji bloku.
*   **Integracja:** Działa jako osobny wątek, udostępniając endpoint `/metrics`.

## 7. `seth`
*   **Opis:** Protokół lub moduł rozszerzający funkcjonalność Osiris. [TODO: Wymaga dalszej specyfikacji].
*   **Integracja:** [TODO: Opisać, jak Seth integruje się z resztą systemu].
