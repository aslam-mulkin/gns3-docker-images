FROM debian:stretch-slim

RUN set -ex \
#
# install ftp, tftp and ssh server
#
    && apt-get update \
    && echo 'proftpd-basic shared/proftpd/inetd_or_standalone string standalone' | debconf-set-selections \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        net-tools inetutils-ping procps nano vim-tiny \
        dumb-init proftpd-basic tftpd-hpa openssh-server \
    && rm -rf /var/lib/apt/lists/* \
#
# setup ftp, tftp and openssh
#
    && addgroup --system ftp \
    && usermod -d /ftp -g ftp -s /bin/bash ftp \
    && /bin/echo -e "ftp\nftp" | passwd ftp 2> /dev/null \
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
    && /bin/echo -e '\
\n\
Ciphers +aes256-cbc\n\
KexAlgorithms +diffie-hellman-group1-sha1\n\
\n\
AllowUsers ftp' >> /etc/ssh/sshd_config \
    && rm -f /etc/ssh/ssh_host_* \
#
# startup script
#
    && /bin/echo -e '\
\x23!/bin/sh\n\
[ $$ -eq 1 ] && exec dumb-init -- "$0" "$@"\n\
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
\x23 create missing SSH keys\n\
ssh-keygen -A\n\
\n\
\x23 start ftp, tftp and ssh services\n\
service proftpd start\n\
service tftpd-hpa start\n\
service ssh start\n\
\n\
cd; bash -i' \
        > /etc/init.sh && chmod +x /etc/init.sh

VOLUME [ "/etc/ssh", "/ftp" ]
CMD [ "/etc/init.sh" ]
