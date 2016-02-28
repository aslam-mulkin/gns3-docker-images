FROM gns3-debian-base

RUN set -ex \
    && apt-get update \
    && echo 'proftpd-basic shared/proftpd/inetd_or_standalone string standalone' | debconf-set-selections \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        proftpd-basic tftpd-hpa \
    && rm -rf /var/lib/apt/lists/* \
\
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
\
    && /bin/echo -e '#!/bin/sh\n\
\n\
mkdir -p /ftp\n\
chown ftp:ftp /ftp\n\
chmod 775 /ftp\n\
service proftpd start\n\
service tftpd-hpa start\n\
tail -F /var/log/proftpd/proftpd.log' \
        > /start_ftp.sh; chmod +x /start_ftp.sh

VOLUME [ "/ftp" ]
CMD [ "dumb-init", "/start_ftp.sh" ]
