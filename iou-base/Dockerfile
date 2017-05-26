FROM alpine

#
# install iouyap, (frozen) ioutools and run-stop
#
RUN set -ex \
    && dd if=/dev/zero bs=4 count=1 of=/etc/hostid \
    && apk add --update-cache iouyap \
    && apk add --virtual build_pkg py3-cx_freeze wget ca-certificates \
# install and freeze IOUtools
    && cd /tmp \
    && wget -q https://raw.githubusercontent.com/ehlers/IOUtools/master/iou_import \
    && wget -q https://raw.githubusercontent.com/ehlers/IOUtools/master/iou_export \
    && echo -e '\
from cx_Freeze import setup, Executable\n\
setup (\n\
    options = { "build_exe": { "build_exe": "/usr/local/bin", "zip_exclude_packages": None, "zip_include_packages": "*" } },\n\
    executables = [ Executable("iou_import"), Executable("iou_export") ]\n\
)' \
        > setup.py \
    && ln -s `which ldd` ldd \
    && python3 setup.py build \
    && rm /usr/local/bin/ldd \
    && rm iou_export iou_import setup.py ldd \
    && cd - \
# add run-stop
    && mkdir -p /usr/local/sbin \
    && url=`wget -q -O - https://api.github.com/repos/ehlers/run-stop/releases/latest | sed -n 's/^ *"browser_download_url": "\([^"]*_amd64\)".*/\1/p'` \
    && if [ -z "$url" ]; then echo "run-stop not found" >&2; exit 1; fi \
    && wget -q -O /usr/local/sbin/run-stop $url \
    && chmod 755 /usr/local/sbin/run-stop \
# cleanup
    && apk del build_pkg \
    && rm -rf /var/cache/apk/*

ADD libc-i386.tar.gz /
ADD do-run do-stop /etc/init.d/

RUN chmod 755 /etc/init.d/do-run /etc/init.d/do-stop

CMD [ "run-stop", "/etc/init.d/do-run", "---", "/etc/init.d/do-stop" ]
