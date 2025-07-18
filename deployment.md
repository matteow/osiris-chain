# Wdrażanie Węzła Osiris

## 1. Użycie Dockera (Zalecane)

Dzięki konteneryzacji, uruchomienie węzła Osiris jest proste i powtarzalne.

### Budowanie Obrazu Docker
W głównym katalogu projektu znajduje się `Dockerfile`. Aby zbudować obraz, wykonaj:
```bash
docker build -t osiris-node:latest .
```

### Uruchamianie Kontenera
Przykładowa komenda do uruchomienia pojedynczego węzła:
```bash
docker run -d --name osiris1 \
  -p 30303:30303/tcp \
  -p 8080:8080/tcp \
  -v $(pwd)/data/node1:/app/data \
  -v $(pwd)/config/node1.yaml:/app/config.yml \
  osiris-node:latest
```
*   `-d`: Uruchom w tle.
*   `-p`: Mapuj porty (P2P i RPC).
*   `-v`: Mapuj wolumeny dla danych i konfiguracji, aby były trwałe.

### Uruchamianie Sieci z Docker Compose
Plik `docker-compose.yml` w repozytorium pozwala na uruchomienie lokalnej sieci testowej składającej się z kilku węzłów.
```bash
docker-compose up -d
```
Ta komenda automatycznie zbuduje obraz i uruchomi 3 węzły, które będą połączone ze sobą.

## 2. Deployment Lokalny (bez Dockera)

### Wymagania
Upewnij się, że masz zainstalowane wszystkie zależności (GCC, CMake, Boost, Crypto++).

### Kompilacja
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

### Uruchomienie
```bash
./bin/osiris-node --config ../config/dev.yaml
```

## 3. Połączenia P2P
Aby węzły mogły się ze sobą komunikować, muszą znać swoje adresy. Użyj parametru `seeds` w `config.yml`, aby wskazać inne węzły w sieci.
```yaml
network:
  seeds:
    - "192.168.1.10:30303" # Adres IP innego węzła
```
W przypadku deploymentu w chmurze, upewnij się, że porty P2P są otwarte w zaporze sieciowej.

```