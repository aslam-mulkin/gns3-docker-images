# docker base image for basic networking tools

FROM debian:stretch-slim

RUN set -ex \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        curl ca-certificates \
# openssl is fine with perl-base, saves 40 MByte
    && sed -i '/^Package: openssl$/,/^Depends: / s/perl\([ ,]\|$\)/perl-base\1/' /var/lib/dpkg/status \
    && apt-get -y --purge autoremove perl \
#
# compile and install mtools (msend & mreceive)
#
    && dpkg-query -f '${binary:Package}\n' -W | sort > base_packages \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        gcc libc6-dev make \
    && curl -s -S -L https://github.com/troglobit/mtools/archive/v2.3.tar.gz | tar xfz - \
    && cd mtools* \
    && make \
    && make install \
    && mv /usr/local/sbin/mreceive /usr/local/sbin/msend /usr/local/bin/ \
    && cd .. \
    && rm -r mtools* \
    && dpkg-query -f '${binary:Package}\n' -W | sort > packages \
    && DEBIAN_FRONTEND=noninteractive apt-get -y purge \
        `comm -13 base_packages packages` \
    && rm -f base_packages packages \
#
# install remaining tools
#
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        net-tools iproute2 telnet inetutils-ping traceroute procps nano vim-tiny \
        dumb-init iperf3 knot-host mtr-tiny openssh-client socat tcpdump \
    && rm -rf /var/lib/apt/lists/* \
