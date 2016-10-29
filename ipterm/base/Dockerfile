# docker base image for basic networking tools

FROM debian:jessie

RUN set -ex \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        curl ca-certificates \
#
# compile and install mtools (msend & mreceive)
#
    && dpkg-query -f '${binary:Package}\n' -W | sort > base_packages \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        gcc libc6-dev make \
    && curl -s -S -L https://github.com/troglobit/mtools/releases/download/v2.3/mtools-2.3.tar.gz | tar xfz - \
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
        net-tools tcpdump telnet traceroute iperf3 knot-host openssh-client mtr-tiny socat nano vim-tiny \
    && rm -rf /var/lib/apt/lists/* \
#
# install start-stop from GitHub repository
#
    && url=`curl -s -S -L https://api.github.com/repos/ehlers/start-stop/releases/latest | sed -n 's/^ *"browser_download_url": "\([^"]*_amd64\)".*/\1/p'` \
    && if [ -z "$url" ]; then echo "start-stop not found" >&2; exit 1; fi \
    && curl -s -S -L -o /usr/local/sbin/start-stop $url \
    && chmod 755 /usr/local/sbin/start-stop
