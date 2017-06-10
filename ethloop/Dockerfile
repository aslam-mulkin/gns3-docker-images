# ethloop - virtual RJ45 loopback plug

FROM alpine

ADD ethloop.c /root/

RUN set -ex \
    && cd /root \
    && apk add --update-cache libpcap \
    && apk add --virtual build-deps gcc musl-dev libpcap-dev \
    && gcc -Wall -O2 -s -o /usr/local/bin/ethloop ethloop.c -lpcap \
    && apk del build-deps \
    && rm -rf /var/cache/apk/*

CMD [ "ethloop", "eth0" ]
