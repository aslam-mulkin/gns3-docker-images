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
# install tini from GitHub repository
#
    && repository="https://github.com/krallin/tini" \
    && version=`curl -s -S -k -I $repository/releases/latest | sed -n 's/^ *Location:.*\/tag\/\([a-zA-Z0-9._-]*\).*/\1/p'` \
    && if [ -z "$version" ]; then echo "tini not found" >&2; exit 1; fi \
    && curl -s -S -L -k -o /usr/local/sbin/tini $repository/releases/download/$version/tini \
    && chmod 755 /usr/local/sbin/tini
