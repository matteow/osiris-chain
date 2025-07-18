# Portfel Linii Komend (`osiris-cli`)

`osiris-cli` to narzędzie do interakcji z blockchainem Osiris z poziomu terminala. Umożliwia zarządzanie portfelami, wysyłanie transakcji i odpytywanie stanu sieci.

## Struktura i Użycie
Narzędzie jest planowane jako część modułu `osiris-cli` w `src/modules/`.

Przykładowe użycie:
```bash
./osiris-cli [moduł] [komenda] [argumenty]
```

## Komendy

### Zarządzanie Portfelem
*   **Tworzenie nowego portfela:**
    ```bash
    ./osiris-cli wallet create --password [hasło]
    ```
    Generuje nową parę kluczy (prywatny i publiczny) i zapisuje je w zaszyfrowanym pliku.

*   **Wyświetlanie adresu:**
    ```bash
    ./osiris-cli wallet address
    ```

*   **Sprawdzanie salda:**
    ```bash
    ./osiris-cli wallet balance [adres]
    ```
    Wykonuje zapytanie RPC do węzła, aby pobrać saldo dla podanego adresu.

### Transakcje
*   **Wysyłanie tokenów:**
    ```bash
    ./osiris-cli tx send --to [adres_odbiorcy] --amount [ilość] --fee [opłata]
    ```
    Tworzy i wysyła transakcję do węzła za pośrednictwem RPC.

*   **Wysyłanie transakcji z danymi (dla smart kontraktów):**
    ```bash
    ./osiris-cli tx raw --to [adres_kontraktu] --data "0x..."
    ```

### Synchronizacja i Sieć
*   **Pobieranie informacji o bloku:**
    ```bash
    ./osiris-cli chain getblock [hash_bloku | numer_bloku]
    ```

*   **Sprawdzanie statusu węzła:**
    ```bash
    ./osiris-cli net status
    ```

## Bezpieczeństwo Kluczy Prywatnych
*   Klucze prywatne są szyfrowane przy użyciu AES-256 z hasłem podanym przez użytkownika.
*   Pliki portfela są przechowywane w dedykowanym, chronionym katalogu (np. `~/.osiris/keystore`).
*   Narzędzie nigdy nie wyświetla klucza prywatnego i wymaga potwierdzenia hasłem przy każdej transakcji.
