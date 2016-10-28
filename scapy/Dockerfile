# docker image with scapy and basic networking tools

FROM gns3/ipterm-base

RUN set -ex \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        python python-crypto tcpdump \
    && rm -rf /var/lib/apt/lists/* \
#
# install scapy
#
    && curl -s -S -L -k https://github.com/secdev/scapy/archive/v2.3.2.tar.gz | tar xfz - \
    && cd scapy* \
    && python setup.py install \
    && cd .. \
    && rm -rf scapy*

VOLUME [ "/root" ]
CMD [ "sh", "-c", "cd; exec bash -i" ]
