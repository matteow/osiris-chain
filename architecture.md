# Architektura Osiris Blockchain

## 1. Architektura Wysokopoziomowa

System Osiris został zaprojektowany w architekturze warstwowej, aby zapewnić modularność, skalowalność i łatwość w utrzymaniu. Każda warstwa ma jasno zdefiniowane obowiązki i komunikuje się z innymi przez stabilne interfejsy.

![Diagram Architektury](architecture.png)

**Warstwy:**
1.  **Warstwa Aplikacji (API / CLI):** Interfejs użytkownika i systemów zewnętrznych. Odpowiada za przyjmowanie transakcji, zapytania o stan blockchaina i zarządzanie węzłem.
2.  **Warstwa Modułów Biznesowych:** Zawiera logikę specyficzną dla danej aplikacji, np. `social` (media społecznościowe), `identity` (zarządzanie tożsamością) czy `contract` (silnik smart kontraktów).
3.  **Warstwa Konsensusu:** Kluczowy element zapewniający spójność sieci. Abstrakcyjny interfejs pozwala na dynamiczne przełączanie algorytmów (PoW, PoS, PBFT).
4.  **Warstwa Sieci (Networking):** Odpowiada za komunikację P2P między węzłami, propagację bloków i transakcji. Wykorzystuje `Boost.ASIO` do asynchronicznej obsługi sieci.
5.  **Warstwa Przechowywania (Storage):** Zarządza bazą danych blockchaina, przechowując bloki, transakcje i stan systemu.

## 2. Schemat Komponentów i Przepływ Danych

### Przepływ Transakcji
1.  Transakcja jest wysyłana do węzła przez API (np. JSON-RPC) lub CLI.
2.  API przekazuje transakcję do **Transaction Pool**, gdzie czeka na włączenie do bloku.
3.  Moduł **Konsensusu** pobiera transakcje z puli, aby stworzyć nowy blok.
4.  Nowo utworzony blok jest walidowany zgodnie z zasadami danego algorytmu konsensusu.
5.  Po pomyślnej walidacji, blok jest przekazywany do modułu **Chain**, który dodaje go do lokalnego łańcucha.
6.  Moduł **Storage** zapisuje blok w bazie danych.
7.  Moduł **Sieci (P2P)** rozgłasza nowy blok do innych węzłów w sieci.

### Wątkowość
System jest wielowątkowy, aby zapewnić wysoką wydajność:
*   Główny wątek obsługuje logikę aplikacji.
*   Osobny wątek dla serwera API (np. CivetWeb).
*   Osobny wątek dla komunikacji P2P (Boost.ASIO).
*   Wątki robocze dla algorytmów konsensusu (np. kopanie w PoW).
