# docker image with snmp and basic networking tools

FROM gns3/ipterm-base

# minimal init, see https://github.com/Yelp/dumb-init
ADD https://github.com/Yelp/dumb-init/releases/download/v1.1.1/dumb-init_1.1.1_amd64 /usr/local/sbin/dumb-init

RUN set -ex \
    && chmod 755 /usr/local/sbin/dumb-init \
    && sed -i -e '/^deb / s/$/ non-free/' /etc/apt/sources.list \
    && apt-get update \
#
# install snmp tools
#
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        snmp snmp-mibs-downloader libqtgui4 lxterminal jwm menu leafpad \
    && rm -rf /var/lib/apt/lists/* \
    && sed -i -e 's/^mibs/#mibs/' /etc/snmp/snmp.conf \
    && curl -k -L -o qtmib.deb https://sourceforge.net/projects/qtmib/files/qtmib.deb/qtmib_1.1_1_amd64.deb/download \
    && dpkg -i qtmib.deb \
    && rm qtmib.deb \
    && /bin/echo -e '\
?package(qtmib):\\\n\
 needs="x11"\\\n\
 section="Applications"\\\n\
 title="SNMP MIB browser"\\\n\
 command="qtmib"' \
        > /etc/menu/qtmib \
    && echo "postrun="\""sed -i '/^    </ d' debian-menu"\" >> /etc/menu-methods/jwm \
    && sed -i 's/\(Desktops width\)="[0-9]*"/\1="2"/' /etc/jwm/system.jwmrc \
    && update-menus \
    && mkdir -p /root/.config/lxterminal \
    && /bin/echo -e '\
[general]\n\
scrollback=1000\n\
fgcolor=#ffffff' \
        > /root/.config/lxterminal/lxterminal.conf \
    && /bin/echo -e '\
\x23!/bin/sh\n\
[ $$ -eq 1 ] && exec dumb-init "$0" "$@"\n\
\n\
cd\n\
export SHELL=/bin/bash\n\
qtmib &\n\
jwm' \
        > /etc/init.sh && chmod +x /etc/init.sh

VOLUME [ "/root" ]
CMD [ "/etc/init.sh" ]
