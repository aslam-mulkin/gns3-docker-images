# docker image with scapy and basic networking tools

FROM ehlers/ipterm-base

RUN set -ex \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
       python python-crypto python-ecdsa tcpdump \
       python-pip python-setuptools python-wheel \
    && pip install --quiet --no-cache-dir scapy \
    && rm -rf /root/.cache \
    && apt-get -y --purge autoremove python-pip python-setuptools python-wheel \
    && rm -rf /var/lib/apt/lists/*

VOLUME [ "/root" ]
CMD [ "sh", "-c", "cd; exec bash -i" ]
