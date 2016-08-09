# docker image for ostinato

FROM debian:jessie

RUN set -ex \
#
# install ostinato
#
    && echo 'deb [trusted=yes] http://download.opensuse.org/repositories/home:/pstavirs:/ostinato/Debian_8.0/ /' > /etc/apt/sources.list.d/ostinato.list \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        net-tools tcpdump telnet traceroute nano vim-tiny \
        ostinato lxterminal jwm menu leafpad \
#
# install tini from alpine/tini-static
#
    && apt-get -y --no-install-recommends install wget \
    && cd /usr/local \
    && wget -q -O - http://dl-cdn.alpinelinux.org/alpine/v3.4/community/x86_64/tini-static-0.9.0-r1.apk | tar xfz - sbin/tini-static \
    && mv sbin/tini-static sbin/tini \
    && cd - \
    && apt-get -y --purge autoremove wget \
    && rm -rf /var/lib/apt/lists/* \
#
# customize jwm menu
#
    && /bin/echo -e '\
?package(ostinato):\\\n\
 needs="x11"\\\n\
 section="Applications"\\\n\
 title="Ostinato"\\\n\
 command="ostinato"' \
        > /etc/menu/ostinato \
    && echo "postrun="\""sed -i '/^    </ d' debian-menu"\" >> /etc/menu-methods/jwm \
    && sed -i 's/\(Desktops width\)="[0-9]*"/\1="2"/' /etc/jwm/system.jwmrc \
    && update-menus \
#
# configure ostinato drone
#
    && mkdir -p /root/.config/Ostinato \
    && /bin/echo -e '\
[General]\n\
RateAccuracy=Low\n\
[PortList]\n\
Include=eth*' \
        > /root/.config/Ostinato/drone.ini \
#
# set lxterminal defaults
#
    && mkdir -p /root/.config/lxterminal \
    && /bin/echo -e '\
[general]\n\
scrollback=1000\n\
fgcolor=#ffffff' \
        > /root/.config/lxterminal/lxterminal.conf \
#
# startup script
#
    && /bin/echo -e '\
\x23!/bin/sh\n\
[ $$ -eq 1 ] && exec tini -- "$0" "$@"\n\
\n\
\x23 on unconfigured interfaces disable IPv6, set MTU to 9000\n\
sed -n '\''s/^ *\\(eth[0-9]*\\):.*/\\1/p'\'' /proc/net/dev | sort > /tmp/netdev\n\
sed -n '\''s/^iface  *\\(eth[0-9]*\\).*/\\1/p'\'' /etc/network/interfaces | sort -u > /tmp/confdev\n\
for DEVICE in `comm -13 /tmp/confdev /tmp/netdev`; do\n\
	ip link set dev $DEVICE down\n\
	sysctl -q -w net.ipv6.conf.$DEVICE.disable_ipv6=1\n\
	ip link set dev $DEVICE mtu 9000\n\
	ip link set dev $DEVICE up\n\
done\n\
rm /tmp/confdev /tmp/netdev\n\
sleep 0.5\n\
\n\
cd\n\
export SHELL=/bin/bash\n\
drone < /dev/null > /var/log/ostinato-drone.log 2>&1 &\n\
sleep 0.5\n\
ostinato &\n\
jwm' \
        > /etc/init.sh && chmod +x /etc/init.sh

VOLUME [ "/root" ]
CMD [ "/etc/init.sh" ]
