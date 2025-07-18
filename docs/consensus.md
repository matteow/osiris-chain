# Algorytmy Konsensusu w Osiris

Osiris został zaprojektowany z myślą o elastyczności, umożliwiając wybór algorytmu konsensusu odpowiedniego do danego zastosowania. Wszystkie algorytmy implementują wspólny interfejs `IConsensus`.

## Interfejs `IConsensus`
Każdy algorytm musi dostarczyć implementację następujących metod:
*   `createNewBlock()`: Tworzy nowy, pusty blok, gotowy do wypełnienia transakcjami.
*   `validateBlock(block)`: Weryfikuje poprawność bloku zgodnie z zasadami danego algorytmu (np. poprawność PoW, podpisy w PoA).
*   `getAlgorithmName()`: Zwraca nazwę algorytmu.

## Zaimplementowane Algorytmy

### 1. Proof of Work (PoW)
*   **Opis:** Klasyczny algorytm oparty na mocy obliczeniowej, znany z Bitcoina.
*   **Konfiguracja (`config.yml`):**
    ```yaml
    consensus:
      name: "PoW"
      params:
        difficulty: 4 # Liczba zer w hashu
    ```

### 2. Proof of Stake (PoS)
*   **Opis:** Tworzenie bloków jest proporcjonalne do posiadanej stawki (ilości monet). Bardziej energooszczędny niż PoW.
*   **Konfiguracja (`config.yml`):**
    ```yaml
    consensus:
      name: "PoS"
      params:
        stake_requirement: 1000 # Minimalna stawka do zostania walidatorem
    ```

### 3. Proof of Authority (PoA)
*   **Opis:** Bloki są tworzone przez zaufane węzły (autorytety). Szybki i wydajny, ale scentralizowany. Idealny dla sieci prywatnych.
*   **Konfiguracja (`config.yml`):**
    ```yaml
    consensus:
      name: "PoA"
      params:
        authorities:
          - "0x..." # Adres pierwszego autorytetu
          - "0x..." # Adres drugiego autorytetu
    ```

### 4. Practical Byzantine Fault Tolerance (PBFT)
*   **Opis:** Algorytm odporny na błędy bizantyjskie, zapewniający finalność transakcji. Wymaga co najmniej 4 węzłów.
*   **Konfiguracja (`config.yml`):**
    ```yaml
    consensus:
      name: "PBFT"
      params:
        validators: # Lista początkowych walidatorów
          - "tcp://node1_ip:port"
          - "tcp://node2_ip:port"
    ```

### 5. Tendermint
*   **Opis:** Nowoczesny algorytm BFT, który łączy w sobie zalety PoS i PBFT. Zapewnia szybką finalność i skalowalność.
*   **Konfiguracja (`config.yml`):**
    ```yaml
    consensus:
      name: "Tendermint"
      params:
        # Konfiguracja specyficzna dla Tendermint
    ```
