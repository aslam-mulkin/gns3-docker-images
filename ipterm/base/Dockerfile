# docker base image for basic networking tools

FROM debian:jessie

RUN set -ex \
    && apt-get update \
#
# compile and install mtools (msend & mreceive)
#
    && dpkg-query -f '${binary:Package}\n' -W | sort > base_packages \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        gcc libc6-dev make curl ca-certificates \
    && curl -OL https://github.com/troglobit/mtools/releases/download/v2.3/mtools-2.3.tar.gz \
    && tar xfz mtools-2.3.tar.gz \
    && cd mtools-2.3 \
    && make \
    && make install \
    && mv /usr/local/sbin/mreceive /usr/local/sbin/msend /usr/local/bin/ \
    && cd .. \
    && rm -r mtools-2.3* \
    && dpkg-query -f '${binary:Package}\n' -W | sort > packages \
    && DEBIAN_FRONTEND=noninteractive apt-get -y purge \
        `comm -13 base_packages packages` \
    && rm -f base_packages packages \
#
# install remaining tools
#
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        net-tools tcpdump telnet traceroute curl iperf3 knot-host openssh-client mtr-tiny socat nano vim-tiny \
    && rm -rf /var/lib/apt/lists/* \
#
# install tini from alpine/tini-static
#
    && cd /usr/local \
    && curl -s -S http://dl-cdn.alpinelinux.org/alpine/v3.4/community/x86_64/tini-static-0.9.0-r1.apk | tar xfz - sbin/tini-static \
    && mv sbin/tini-static sbin/tini \
    && cd -
