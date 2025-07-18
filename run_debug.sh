#!/usr/bin/env bash
set -euo pipefail

# Ścieżki (dopasuj jeśli potrzeba)
ROOT_DIR="$(pwd)"
BUILD_DIR="$ROOT_DIR/build"
CONFIG_PATH="$ROOT_DIR/config/dev.yaml"
EXAMPLE_CONFIG="$ROOT_DIR/examples/config/dev.yaml"
LOG_DIR="$BUILD_DIR/logs"

echo "===== Krok 1: Weryfikacja konfiguracji YAML ====="
if [ ! -f "$CONFIG_PATH" ]; then
  echo "Brak dev.yaml → kopiowanie przykładu"
  cp "$EXAMPLE_CONFIG" "$CONFIG_PATH"
fi
echo "Sprawdzanie składni pliku YAML: $CONFIG_PATH"
python3 - <<EOF
import yaml, sys
try:
    yaml.safe_load(open("$CONFIG_PATH"))
    print("Składnia YAML jest poprawna.")
except Exception as e:
    sys.exit("Błąd YAML: " + str(e))
EOF
echo "============================================="

echo
echo "===== Krok 2: Generacja CMake i kompilacja ====="
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
echo "Uruchamiam: cmake .."
cmake .. 
echo "Uruchamiam: cmake --build . -- -j$(nproc)"
cmake --build . -- -j$(nproc)
echo "==========================================="

echo
echo "===== Krok 3: Tworzenie katalogu na logi ====="
mkdir -p "$LOG_DIR"
echo "Katalog na logi: $LOG_DIR"
echo "========================================="

echo
echo "===== Krok 4: Uruchamianie testów z debugowaniem ====="
# lista testów (binariów) do uruchomienia
tests=(
  "config_tests"
  "consensus_tests"
  "contract_tests"
  "network_tests"
  "storage_tests"
  "metrics_tests"
  "ChainTest"
  "WalletTest"
)

for t in "${tests[@]}"; do
  BIN="$BUILD_DIR/tests/$t"
  LOG="$LOG_DIR/$t.log"
  echo
  echo ">>> Test: $t" | tee -a "$LOG"
  if [ ! -x "$BIN" ]; then
    echo "   Błąd: binarium $BIN nie istnieje lub nie jest wykonywalne." | tee -a "$LOG"
    continue
  fi

  if "$BIN" &>> "$LOG"; then
    echo "   $t PASSED" | tee -a "$LOG"
  else
    echo "   $t FAILED – generuję backtrace" | tee -a "$LOG"
    gdb --batch \
        -ex "file $BIN" \
        -ex "run" \
        -ex "bt full" \
        &>> "$LOG"
  fi
done

echo
echo "===== Krok 5: Podsumowanie ====="
grep -H "PASSED" "$LOG_DIR"/*.log || true
grep -H "FAILED" "$LOG_DIR"/*.log || true
echo "Logi dostępne w: $LOG_DIR"
