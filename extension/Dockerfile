FROM php:8.4-cli

RUN set -eux; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
            libicu-dev \
            libpcre2-dev

WORKDIR /usr/src

COPY . /usr/src

RUN set -eux; \
    make clean; \
    phpize; \
    ./configure; \
    make -j"$(nproc)" install
