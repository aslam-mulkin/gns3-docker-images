# nicer alpine image

FROM alpine

RUN set -ex \
#
# install start-stop and nodnsd
#
    && apk add --update-cache wget ca-certificates libcap \
    && mkdir -p /usr/local/sbin \
    && cd /usr/local/sbin \
    && url=`wget -q -O - https://api.github.com/repos/ehlers/start-stop/releases/latest | sed -n 's/^ *"browser_download_url": "\([^"]*_amd64\)".*/\1/p'` \
    && if [ -z "$url" ]; then echo "start-stop not found" >&2; exit 1; fi \
    && wget -q -O start-stop $url \
    && chmod 755 start-stop \
    && wget -q -O nodnsd https://github.com/ehlers/nodnsd/releases/download/v0.1/nodnsd_0.1_amd64 \
    && chmod 755 nodnsd \
    && setcap cap_net_bind_service=+ep nodnsd \
    && cd - \
    && apk del wget ca-certificates libcap \
    && rm -rf /var/cache/apk/* \
#
# startup script
#
    && echo -e '\
\x23!/bin/sh\n\
[ $$ -eq 1 ] && exec start-stop -- "$0" "$@"\n\
\n\
nodnsd\n\
\n\
[ $# -gt 0 ] && exec "$@" || exec ash -i' \
        > /etc/init.sh && chmod +x /etc/init.sh

ENTRYPOINT [ "/etc/init.sh" ]
STOPSIGNAL SIGHUP
