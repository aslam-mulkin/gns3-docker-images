# docker image with basic networking tools and web browser

FROM debian:jessie

# minimal init, see https://github.com/Yelp/dumb-init
ADD https://github.com/Yelp/dumb-init/releases/download/v1.0.3/dumb-init_1.0.3_amd64 /usr/local/sbin/dumb-init

RUN set -ex \
    && chmod 755 /usr/local/sbin/dumb-init \
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
        net-tools tcpdump telnet traceroute iperf3 openssh-client vim-tiny \
        firefox-esr xterm jwm menu \
    && rm -rf /var/lib/apt/lists/* \
    && /bin/echo -e '\
\x23!/bin/sh\n\
\n\
\x23 use home page on first start\n\
[ -e "$HOME/.mozilla" ] || start_url="about:home"\n\
\n\
\x23 start firefox\n\
start=$(date +%s)\n\
firefox $start_url\n\
status=$?\n\
\n\
\x23 workaround: restart firefox, if it crashes during initialization\n\
if [ $status -eq 139 -a $(($(date +%s)-start)) -le 10 ]; then\n\
        firefox $start_url\n\
fi' \
        > /usr/local/bin/start-firefox; chmod +x /usr/local/bin/start-firefox \
    && /bin/echo -e '\
?package(firefox-esr):\\\n\
 needs="x11"\\\n\
 section="Applications"\\\n\
 title="Mozilla Firefox"\\\n\
 command="start-firefox"' \
        > /etc/menu/firefox \
    && echo "postrun="\""sed -i '/^    </ d' debian-menu"\" >> /etc/menu-methods/jwm \
    && sed -i 's/\(Desktops width\)="[0-9]*"/\1="2"/' /etc/jwm/system.jwmrc \
    && update-menus \
    && /bin/echo -e '\
\x23!/bin/sh\n\
\n\
cd\n\
start-firefox &\n\
jwm' \
        > /start_browser.sh; chmod +x /start_browser.sh

VOLUME [ "/root" ]
CMD [ "dumb-init", "/start_browser.sh" ]
