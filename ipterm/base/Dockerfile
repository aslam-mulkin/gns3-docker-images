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
    && repository="http://dl-cdn.alpinelinux.org/alpine/latest-stable/community/x86_64" \
    && package=`curl -s -S -L $repository/ | sed -n 's/^.*href="\(tini-static[^"]*\).*/\1/p'` \
    && if [ -z "$package" ]; then echo "tini not found" >&2; exit 1; fi \
    && curl -s -S -L $repository/$package | tar xfz - --warning=no-unknown-keyword sbin/tini-static \
    && mv sbin/tini-static sbin/tini \
    && cd -
