FROM alpine

### cx_freeze 5.0 is totally broken
COPY py2-cx_freeze* /tmp
#
# install iouyap, (frozen) ioutools and run-stop
#
RUN set -ex \
    && dd if=/dev/zero bs=4 count=1 of=/etc/hostid \
    && apk add --update-cache /tmp/py2-cx_freeze* iouyap wget ca-certificates \
    && cd /tmp \
    && wget -q https://raw.githubusercontent.com/ehlers/IOUtools/master/iou_import \
    && wget -q https://raw.githubusercontent.com/ehlers/IOUtools/master/iou_export \
    && ln -s `which ldd` ldd \
    && cxfreeze iou_import --target-dir /usr/local/bin \
    && cxfreeze iou_export --target-dir /usr/local/bin \
    && rm /usr/local/bin/ldd \
    && rm iou_export iou_import ldd \
    && cd - \
    && mkdir -p /usr/local/sbin \
    && url=`wget -q -O - https://api.github.com/repos/ehlers/run-stop/releases/latest | sed -n 's/^ *"browser_download_url": "\([^"]*_amd64\)".*/\1/p'` \
    && if [ -z "$url" ]; then echo "run-stop not found" >&2; exit 1; fi \
    && wget -q -O /usr/local/sbin/run-stop $url \
    && chmod 755 /usr/local/sbin/run-stop \
    && apk del py2-cx_freeze wget ca-certificates \
    && rm -rf /var/cache/apk/*

ADD libc-i386.tar.gz /
ADD do-run do-stop /etc/init.d/

RUN chmod 755 /etc/init.d/do-run /etc/init.d/do-stop

CMD [ "run-stop", "/etc/init.d/do-run", "---", "/etc/init.d/do-stop" ]
