FROM debian:jessie

RUN set -ex \
#
# install ftp and tftp server
#
    && apt-get update \
    && echo 'proftpd-basic shared/proftpd/inetd_or_standalone string standalone' | debconf-set-selections \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        proftpd-basic tftpd-hpa \
#
# install tini from alpine/tini-static
#
    && apt-get -y --no-install-recommends install wget \
    && cd /usr/local \
    && repository="http://dl-cdn.alpinelinux.org/alpine/latest-stable/community/x86_64" \
    && package=`wget -q -O - $repository/ | sed -n 's/^.*href="\(tini-static[^"]*\).*/\1/p'` \
    && if [ -z "$package" ]; then echo "tini not found" >&2; exit 1; fi \
    && wget -q -O - $repository/$package | tar xfz - --warning=no-unknown-keyword sbin/tini-static \
    && mv sbin/tini-static sbin/tini \
    && cd - \
    && apt-get -y --purge autoremove wget \
    && rm -rf /var/lib/apt/lists/* \
#
# setup ftp, tftp
#
    && addgroup --system ftp \
    && usermod -d /ftp -g ftp ftp \
    && /bin/echo -e '\
\x23 A basic anonymous configuration, no security !!!\n\
\n\
<Anonymous ~ftp>\n\
  User			ftp\n\
  Group			ftp\n\
  \x23 We want clients to be able to login with "anonymous" as well as "ftp"\n\
  UserAlias		anonymous ftp\n\
\n\
  \x23 Don\x27t require valid shell for anonymous user\n\
  RequireValidShell	off\n\
\n\
  \x23 Limit the maximum number of anonymous logins\n\
  MaxClients		10\n\
\n\
  \x23 We want "welcome.msg" displayed at login, and ".message" displayed\n\
  \x23 in each newly chdired directory.\n\
  DisplayLogin		welcome.msg\n\
  DisplayChdir		.message\n\
\n\
</Anonymous>' \
        > /etc/proftpd/conf.d/anonymous.conf \
\
    && /bin/echo -e '\
\x23 /etc/default/tftpd-hpa\n\
\n\
TFTP_USERNAME="ftp"\n\
TFTP_DIRECTORY="/ftp"\n\
TFTP_ADDRESS=":69"\n\
TFTP_OPTIONS="--secure --permissive --create --umask 022"' \
        > /etc/default/tftpd-hpa \
#
# startup script
#
    && /bin/echo -e '\
\x23!/bin/sh\n\
[ $$ -eq 1 ] && exec tini -- "$0" "$@"\n\
\n\
\x23 Function to stop services\n\
stop_services () {\n\
	trap - EXIT HUP INT QUIT TERM\n\
	echo\n\
	service proftpd stop\n\
	service tftpd-hpa stop\n\
	exit 0\n\
}\n\
\n\
\x23 try to set ftp to same user/group id as GNS3 process\n\
\x23 /etc/network/interfaces is managed by GNS3\n\
uid=`stat -c %u /etc/network/interfaces 2> /dev/null`\n\
if [ 0$uid -ne 0 ]; then\n\
	gid=`stat -c %g /etc/network/interfaces`\n\
	usermod -o -u $uid ftp\n\
	groupmod -o -g $gid ftp\n\
fi\n\
\n\
\x23 create /ftp directory\n\
mkdir -p /ftp\n\
chown ftp:ftp /ftp\n\
chmod 775 /ftp\n\
\n\
\x23 start ftp and tftp services\n\
service proftpd start\n\
service tftpd-hpa start\n\
trap stop_services EXIT HUP INT QUIT TERM\n\
\n\
tail -F /var/log/proftpd/proftpd.log &\n\
wait $!' \
        > /etc/init.sh && chmod +x /etc/init.sh

VOLUME [ "/ftp" ]
CMD [ "/etc/init.sh" ]
