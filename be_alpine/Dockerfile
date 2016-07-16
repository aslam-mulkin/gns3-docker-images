# nicer alpine image

FROM alpine

ADD [ "https://github.com/Yelp/dumb-init/releases/download/v1.1.1/dumb-init_1.1.1_amd64", "https://github.com/ehlers/nodnsd/releases/download/v0.1/nodnsd_0.1_amd64", "/usr/local/sbin/" ]

RUN set -ex \
    && mv /usr/local/sbin/dumb-init* /usr/local/sbin/dumb-init \
    && mv /usr/local/sbin/nodnsd* /usr/local/sbin/nodnsd \
    && chmod 755 /usr/local/sbin/* \
    && echo -e '\
\x23!/bin/sh\n\
[ $$ -eq 1 ] && exec dumb-init -c -r 15:1 "$0" "$@"\n\
\n\
nodnsd\n\
\n\
[ $# -gt 0 ] && exec "$@" || exec ash -i' \
        > /etc/init.sh && chmod +x /etc/init.sh

ENTRYPOINT [ "/etc/init.sh" ]
