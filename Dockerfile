FROM ubuntu:24.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

# 🔧 System dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake git curl ca-certificates \
    libssl-dev libcurl4-openssl-dev \
    zlib1g-dev \
    libboost-all-dev \
    libyaml-cpp-dev \
    libcrypto++-dev \
    libleveldb-dev \
    liblmdb-dev \
    libgtest-dev \
    libgmock-dev \
    libsnappy-dev \
    && rm -rf /var/lib/apt/lists/*

# 📦 Build Osiris-Core
WORKDIR /osiris-core
COPY . .
COPY run_tests.sh /usr/local/bin/run_tests.sh
RUN chmod +x /usr/local/bin/run_tests.sh

# Remove manual Boost installation as we are using libboost-all-dev
# Remove Crypto++ include fix as we are using standard includes now

RUN mkdir -p build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release \
          -DBUILD_TESTING=OFF \
          .. && \
    make -j"$(nproc)"

# ##################################################################
# Etap wykonawczy (Runtime)
# ##################################################################
FROM ubuntu:24.04 AS runtime

# 1. Zainstaluj tylko niezbędne pakiety i utwórz wymagane katalogi
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && \
    rm -rf /var/lib/apt/lists/* && \
    mkdir -p /etc/osiris-core

WORKDIR /osiris-core

# 2. Skopiuj plik binarny
COPY --from=builder /osiris-core/build/src/osiris-node /usr/local/bin/osiris-node

# 3. Skopiuj biblioteki współdzielone do ich standardowej lokalizacji i zaktualizuj cache linkera
COPY --from=builder /usr/lib/x86_64-linux-gnu/libboost_system.so* /usr/lib/x86_64-linux-gnu/
COPY --from=builder /usr/lib/x86_64-linux-gnu/libboost_thread.so* /usr/lib/x86_64-linux-gnu/
COPY --from=builder /usr/lib/x86_64-linux-gnu/libyaml-cpp.so* /usr/lib/x86_64-linux-gnu/
COPY --from=builder /usr/lib/x86_64-linux-gnu/libcrypto++.so* /usr/lib/x86_64-linux-gnu/
COPY --from=builder /usr/lib/x86_64-linux-gnu/libleveldb.so* /usr/lib/x86_64-linux-gnu/
COPY --from=builder /usr/lib/x86_64-linux-gnu/liblmdb.so* /usr/lib/x86_64-linux-gnu/
COPY --from=builder /usr/lib/x86_64-linux-gnu/libcurl.so* /usr/lib/x86_64-linux-gnu/
COPY --from=builder /usr/lib/x86_64-linux-gnu/libz.so* /usr/lib/x86_64-linux-gnu/
COPY --from=builder /usr/lib/x86_64-linux-gnu/libsnappy.so* /usr/lib/x86_64-linux-gnu/
RUN ldconfig

# 4. Ustaw domyślne polecenie. Zwróć uwagę na poprawną flagę --config i nazwę pliku .yaml
ENTRYPOINT ["/usr/local/bin/osiris-node"]
CMD ["--config", "/etc/osiris-core/config.yaml"]