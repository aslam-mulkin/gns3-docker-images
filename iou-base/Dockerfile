FROM alpine

#
# install iouyap, (frozen) ioutools and start-stop
#
RUN set -ex \
    && dd if=/dev/zero bs=4 count=1 of=/etc/hostid \
    && echo -e '\
@edge http://dl-cdn.alpinelinux.org/alpine/edge/main\n\
@edge http://dl-cdn.alpinelinux.org/alpine/edge/community' \
        >> /etc/apk/repositories \
    && apk add --update-cache py2-cx_freeze@edge iouyap@edge wget \
    && cd /tmp \
    && wget -q --no-check-certificate https://raw.githubusercontent.com/ehlers/IOUtools/master/iou_import \
    && wget -q --no-check-certificate https://raw.githubusercontent.com/ehlers/IOUtools/master/iou_export \
    && ln -s `which ldd` ldd \
    && cxfreeze iou_import --target-dir /usr/local/bin \
    && cxfreeze iou_export --target-dir /usr/local/bin \
    && rm /usr/local/bin/ldd \
    && rm iou_export iou_import ldd \
    && cd - \
    && mkdir -p /usr/local/sbin \
    && url=`wget -q --no-check-certificate -O - https://api.github.com/repos/ehlers/start-stop/releases/latest | sed -n 's/^ *"browser_download_url": "\([^"]*_amd64\)".*/\1/p'` \
    && if [ -z "$url" ]; then echo "start-stop not found" >&2; exit 1; fi \
    && wget -q --no-check-certificate -O /usr/local/sbin/start-stop $url \
    && chmod 755 /usr/local/sbin/start-stop \
    && apk del py2-cx_freeze wget \
    && rm -rf /var/cache/apk/*

ADD libc-i386.tar.gz /
ADD do-start do-stop /etc/init.d/

RUN chmod 755 /etc/init.d/do-start /etc/init.d/do-stop

CMD [ "start-stop", "/etc/init.d/do-start", "---", "/etc/init.d/do-stop" ]
