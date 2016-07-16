# ethloop - virtual RJ45 loopback plug

FROM alpine

ADD https://github.com/Yelp/dumb-init/releases/download/v1.1.1/dumb-init_1.1.1_amd64 /usr/local/sbin/dumb-init

ADD ethloop.c /root/

RUN set -ex \
    && chmod 755 /usr/local/sbin/* \
    && cd /root \
    && apk --update add gcc musl-dev libpcap-dev libpcap \
    && gcc -Wall -O2 -s -o /usr/local/bin/ethloop ethloop.c -lpcap \
    && apk del gcc musl-dev libpcap-dev \
    && rm -rf /var/cache/apk/* \
    && echo -e '\
\x23!/bin/sh\n\
[ $$ -eq 1 ] && exec dumb-init -c -r 15:1 "$0" "$@"\n\
\n\
[ $# -gt 0 ] && exec "$@" || exec ash -i' \
        > /etc/init.sh && chmod +x /etc/init.sh

ENTRYPOINT [ "/etc/init.sh" ]
CMD [ "ethloop", "eth0" ]
