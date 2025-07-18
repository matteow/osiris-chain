Wytyczne dla Gemini CLI w projekcie Osiris Blockchain
Ten plik GEMINI.md służy jako trwałe źródło kontekstu dla Gemini CLI, zapewniając, że generowany kod i interakcje są zgodne z architekturą, standardami kodowania i konwencjami projektu osiris-core.

1. Wprowadzenie do Osiris
Osiris to modularny, wysoce konfigurowalny rdzeń blockchaina napisany w C++20. Został zaprojektowany z myślą o elastyczności, umożliwiając deweloperom tworzenie i wdrażanie zdecentralizowanych aplikacji. Projekt wspiera szeroką gamę algorytmów konsensusu, posiada wbudowane mechanizmy do monitorowania oraz modularną architekturę.

Kluczowe cechy:

Modularność: Jasno zdefiniowane moduły dla konsensusu, sieci, przechowywania danych, smart kontraktów i logiki aplikacji.

Wsparcie dla wielu algorytmów konsensusu: PoW, PoS, PoA, PBFT, Tendermint.

Nowoczesny C++: Wykorzystanie standardu C++20.

Kryptografia: Oparty o sprawdzoną bibliotekę Crypto++.

Konteneryzacja: Pełne wsparcie dla Dockera.

Monitoring: Integracja z Prometheus i Grafana.

Smart Kontrakty: Obsługa natywnych kontraktów oraz planowane wsparcie dla WebAssembly (WASM).

2. Architektura Systemu
Architektura Osiris jest warstwowa, co zapewnia separację komponentów i ułatwia rozwój.

Warstwa Aplikacji (API / CLI): Interfejs użytkownika i systemów zewnętrznych.

Warstwa Modułów Biznesowych: Logika specyficzna dla aplikacji (np. social, identity, contract).

Warstwa Konsensusu: Zapewnia spójność sieci, z abstrakcyjnym interfejsem dla różnych algorytmów.

Warstwa Sieci (Networking): Odpowiada za komunikację P2P, propagację bloków i transakcji.

Warstwa Przechowywania (Storage): Zarządza bazą danych blockchaina (LevelDB/RocksDB).

Katalogi główne:

src/: Główny katalog z kodem źródłowym.

chain/: Logika łańcucha bloków.

consensus/: Implementacje algorytmów konsensusu.

crypto/: Funkcje kryptograficzne (np. KeyGenerator).

network/: Komunikacja P2P.

storage/: Warstwa abstrakcji bazy danych.

modules/: Moduły biznesowe (np. social, identity, contract).

metrics_server/: Serwer metryk Prometheus.

rpc/: Implementacja API JSON-RPC.

config/: Pliki konfiguracyjne YAML.

tests/: Testy jednostkowe i integracyjne (Google Test).

docs/: Dokumentacja projektu.

monitoring/: Konfiguracja dla Prometheus i Grafana.

3. Standardy Kodowania i Konwencje
Generowany kod musi być zgodny z poniższymi wytycznymi:

Język: C++20.

Formatowanie:

Wcięcia: 4 spacje.

Długość linii: Maksymalnie 120 znaków.

Nawiasy klamrowe: Otwierający nawias klamrowy na tej samej linii co deklaracja (K&R style).

Konwencje Nazewnictwa:

Klasy i Struktury: PascalCase (np. Block, Transaction).

Funkcje i Metody: camelCase (np. mineBlock, validateTransaction).

Zmienne i Parametry: snake_case (np. block_hash, transaction_data).

Stałe (globalne/klasowe): ALL_CAPS_WITH_UNDERSCORES (np. MAX_BLOCK_SIZE).

Pola prywatne klas: Zakończone podkreśleniem _ (np. private_key_).

Komentarze: Używaj komentarzy Doxygen dla dokumentacji funkcji, klas i złożonej logiki. Komentarze liniowe dla wyjaśnienia konkretnych fragmentów kodu.

Zasady Projektowania: Przestrzegaj zasad SOLID, DRY (Don't Repeat Yourself) i KISS (Keep It Simple, Stupid).

Przestrzenie Nazw: Preferuj użycie przestrzeni nazw, aby unikać kolizji nazw.

4. Zarządzanie Pamięcią i Bezpieczeństwo
Zarządzanie Pamięcią: Preferuj inteligentne wskaźniki (std::unique_ptr, std::shared_ptr) zamiast surowych wskaźników do zarządzania zasobami. Unikaj wycieków pamięci.

Kryptografia:

Używaj biblioteki Crypto++ dla operacji kryptograficznych.

Generacja kluczy: KeyGenerator (ECDSA).

Haszowanie: SHA-256 dla identyfikacji bloków/transakcji i PoW.

Podpisy cyfrowe: ECDSA dla transakcji.

Generowanie losowości: Używaj std::random_device i std::mt19937_64.

Bezpieczeństwo: Zawsze uwzględniaj implikacje bezpieczeństwa. Waliduj wszystkie dane wejściowe, unikaj przepełnień bufora, zabezpieczaj wrażliwe dane.

5. Obsługa Błędów i Logowanie
Obsługa Błędów:

Używaj wyjątków C++ (std::exception lub niestandardowe typy wyjątków) dla błędów, które powinny przerwać wykonanie.

Zwracaj kody błędów lub std::optional dla błędów, które mogą być obsługiwane lokalnie.

Zapewnij kompleksowe komunikaty o błędach.

Logowanie:

Integracja z istniejącym systemem logowania Osiris.

Loguj istotne zdarzenia, błędy i ostrzeżenia.

Unikaj logowania wrażliwych danych.

6. Moduły Funkcjonalne (Przegląd)
social: Funkcjonalności zdecentralizowanych mediów społecznościowych.

identity: Zarządzanie zdecentralizowaną tożsamością (DID).

contract: Silnik smart kontraktów (natywny, planowane WASM).

network: Komunikacja P2P, synchronizacja, propagacja.

storage: Abstrakcja bazy danych (LevelDB/RocksDB).

metrics_server: Eksport metryk dla Prometheus.

cli-wallet: Narzędzie do interakcji z blockchainem z terminala.

7. Algorytmy Konsensusu
Osiris wspiera modularne algorytmy konsensusu, wszystkie implementujące interfejs IConsensus.

Proof of Work (PoW): Klasyczny algorytm oparty na mocy obliczeniowej.

Proof of Stake (PoS): Tworzenie bloków proporcjonalne do posiadanej stawki.

Proof of Authority (PoA): Bloki tworzone przez zaufane węzły.

Practical Byzantine Fault Tolerance (PBFT): Odporny na błędy bizantyjskie, zapewnia finalność.

Tendermint: Planowany do implementacji.

8. Strategia Testowania
Projekt kładzie duży nacisk na jakość kodu poprzez wielopoziomową strategię testowania z Google Test (GTest).

Testy Jednostkowe: Weryfikacja izolowanych fragmentów kodu (tests/).

Testy Integracyjne: Sprawdzenie współpracy komponentów.

Scenariusze Testowe: Definiowane w tests/consensus_scenarios.test.

Uruchamianie: ctest lub make test w katalogu build.

Przy generowaniu kodu, zawsze proś o towarzyszące testy jednostkowe, obejmujące scenariusze pozytywne, przypadki brzegowe i obsługę błędów.

9. Deployment
Docker: Zalecany do łatwego wdrażania. Obraz osiris-node:latest.

Docker Compose: Do uruchamiania lokalnych sieci testowych.

Lokalny: Kompilacja z CMake (cmake .. -DCMAKE_BUILD_TYPE=Release, make).

10. Interakcja z Gemini CLI
Aby efektywnie współpracować z Gemini CLI w kontekście osiris-core, postępuj zgodnie z poniższymi wytycznymi:

Specyfika Promptów: Bądź niezwykle precyzyjny. Określ język (C++), konkretne algorytmy, struktury danych, nazwy plików i przestrzenie nazw.

Promptowanie Oparte na Rolach: Rozpocznij prompt od „Jesteś ekspertem w C++ z doświadczeniem w systemach blockchain i architekturze osiris-core.”

Łańcuch Myśli: Zachęcaj Gemini do rozumowania krok po kroku, używając zwrotów typu „Zastanówmy się nad tym krok po kroku: najpierw zidentyfikuj... następnie zdefiniuj...”.

Iteracyjne Udoskonalanie: Rozkładaj złożone zadania na mniejsze etapy. Po każdym etapie przeglądaj kod, przekazuj konkretne uwagi i proś o modyfikacje.

Kontekstowe Primowanie: Dostarczaj odpowiednie fragmenty istniejącego kodu osiris-core (np. sygnatury funkcji, definicje klas), aby Gemini mogło bezproblemowo zintegrować nowy kod. Użyj funkcji „Szuflady kontekstowej” lub wklej fragmenty kodu bezpośrednio do promptu.

Jawne Ograniczenia: Określ wymagania niefunkcjonalne, takie jak złożoność czasowa, użycie konkretnych bibliotek, czytelność, wydajność i bezpieczeństwo.

Formatowanie Wyjścia: Wymagaj konkretnego formatu dla generowanego kodu (np. „Podaj funkcję w pojedynczym bloku kodu C++.”).

Testy i Dokumentacja: Zawsze proś o kompleksowe testy jednostkowe i szczegółową dokumentację (komentarze Doxygen, docstringi) dla generowanego kodu.

Zarządzanie Kontekstem:

Unikaj flagi --all-files dla dużych zadań, aby zapobiec degradacji kontekstu.

Używaj .aiexclude do wykluczania nieistotnych katalogów.

Polegaj na narzędziach Gemini (ReadFile, SearchText) do dynamicznego pozyskiwania kontekstu.

Po weryfikacji i poprawieniu kodu, poinformuj Gemini o zaktualizowanym kontekście (np. „Komponent X jest teraz zintegrowany. Zaktualizuj swoje zrozumienie Y.”).

Nadzór Człowieka: Pamiętaj, że Gemini jest asystentem. Zawsze dokładnie przeglądaj i weryfikuj generowany kod przed integracją go z bazą kodu osiris-core.
