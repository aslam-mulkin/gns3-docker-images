# docker image with NAPALM, Netmiko and basic networking tools

FROM ehlers/ipterm-base

RUN set -ex \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get -y install \
       python python-setuptools python-cryptography \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
       python-pip python-dev gcc \
    && pip install --no-cache-dir napalm \
    && rm -rf /root/.cache \
    && apt-get -y --purge autoremove \
       python-pip python-dev gcc \
    && rm -rf /var/lib/apt/lists/*

VOLUME [ "/root" ]
CMD [ "sh", "-c", "cd; exec bash -i" ]
