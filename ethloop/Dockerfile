# ethloop - virtual RJ45 loopback plug

FROM alpine

ADD ethloop.c /root/

RUN set -ex \
    && cd /root \
    && apk add --update-cache libpcap \
    && apk add --virtual build-dependencies gcc musl-dev libpcap-dev \
    && gcc -Wall -O2 -s -lpcap -o /usr/local/bin/ethloop ethloop.c \
    && apk del build-dependencies \
    && rm -rf /var/cache/apk/*

CMD [ "ethloop", "eth0" ]
