# nicer alpine image

FROM alpine

RUN set -ex \
#
# install tini and nodnsd
#
    && apk add --update-cache tini wget libcap \
    && wget -q --no-check-certificate -O nodnsd https://github.com/ehlers/nodnsd/releases/download/v0.1/nodnsd_0.1_amd64 \
    && chmod 755 nodnsd \
    && setcap cap_net_bind_service=+ep nodnsd \
    && mv nodnsd /sbin/ \
    && apk del wget libcap \
    && rm -rf /var/cache/apk/* \
#
# startup script
#
    && echo -e '\
\x23!/bin/sh\n\
[ $$ -eq 1 ] && exec /sbin/tini -- "$0" "$@"\n\
\n\
nodnsd\n\
\n\
[ $# -gt 0 ] && exec "$@" || exec ash -i' \
        > /etc/init.sh && chmod +x /etc/init.sh

ENTRYPOINT [ "/etc/init.sh" ]
STOPSIGNAL SIGHUP
