# docker image with scapy and basic networking tools

FROM gns3/ipterm-base

RUN set -ex \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        python python-crypto tcpdump python-pip \
    && pip install scapy \
    && apt-get -y --purge autoremove python-pip \
    && rm -rf /var/lib/apt/lists/*

VOLUME [ "/root" ]
CMD [ "sh", "-c", "cd; exec bash -i" ]
