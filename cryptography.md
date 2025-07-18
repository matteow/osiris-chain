# Kryptografia w Osiris

Bezpieczeństwo jest fundamentem każdego blockchaina. Osiris wykorzystuje nowoczesne i sprawdzone techniki kryptograficzne do zabezpieczenia sieci, transakcji i tożsamości użytkowników.

## 1. Biblioteki
*   **Crypto++:** Główna biblioteka używana do implementacji algorytmów kryptograficznych, takich jak SHA-256, AES i ECDSA.
*   **Standard C++20:** Wykorzystanie nowoczesnych narzędzi C++ do generowania liczb losowych.

## 2. Generacja Kluczy i Adresów

### Klasa `KeyGenerator`
*   **Lokalizacja:** `src/crypto/KeyGenerator.hpp`
*   **Opis:** Odpowiada za generowanie par kluczy (prywatny i publiczny) przy użyciu kryptografii krzywych eliptycznych (ECDSA).
*   **Generowanie losowości:** Używa `std::random_device` jako źródła entropii i `std::seed_seq` do inicjalizacji generatora liczb pseudolosowych `std::mt19937_64`. Zapewnia to wysoką jakość losowości.

### Proces Tworzenia Adresu
1.  Generowany jest 256-bitowy klucz prywatny.
2.  Z klucza prywatnego wyprowadzany jest klucz publiczny.
3.  Klucz publiczny jest hashowany przy użyciu `SHA-256`.
4.  Z hasha tworzony jest adres w formacie Base58Check, aby zapewnić czytelność i sumy kontrolne.

## 3. Haszowanie
*   **Algorytm:** `SHA-256` jest używany w całym systemie do:
    *   Identyfikacji bloków (hash bloku).
    *   Identyfikacji transakcji (hash transakcji).
    *   Pracy w algorytmie PoW.
    *   Tworzenia adresów.

## 4. Podpisy Cyfrowe
*   **Algorytm:** `ECDSA` (Elliptic Curve Digital Signature Algorithm) jest używany do podpisywania transakcji.
*   **Proces:**
    1.  Użytkownik tworzy transakcję.
    2.  Hash transakcji jest podpisywany kluczem prywatnym użytkownika.
    3.  Podpis jest dołączany do transakcji.
    4.  Węzły weryfikują podpis przy użyciu klucza publicznego nadawcy, co gwarantuje, że transakcja nie została zmieniona i pochodzi od prawowitego właściciela konta.

## 5. Plany Rozwoju
*   **Dowody o zerowej wiedzy (SNARKs/STARKs):** Badanie możliwości implementacji w celu zwiększenia prywatności i skalowalności.
*   **Kryptografia post-kwantowa (PQC):** Przygotowanie systemu na zagrożenia ze strony komputerów kwantowych poprzez badanie i integrację algorytmów odpornych na ataki kwantowe.
