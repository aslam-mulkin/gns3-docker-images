FROM debian:jessie

# GNS3 specific initialization, should be injected by GNS3
COPY __gns3__ /__gns3__
ENTRYPOINT [ "__gns3__/init.sh" ]

# simple init: starts service, a bash shell, reaps zombies,
# forwards stop signal to service processes for a graceful shutdown
COPY init.sh /

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get -q -y install busybox && \
    rm -rf /var/lib/apt/lists/*; \
    for cmd in \
        ar arp arping ash brctl bunzip2 bzcat bzip2 cal cpio dc depmod \
        dos2unix dumpleases freeramdisk ftpget ftpput hexdump httpd \
        ifconfig insmod ipcalc killall klogd less logread lsmod \
        lzcat lzma lzop lzopcat mdev microcom modinfo modprobe nameif \
        nc netstat nslookup patch rdate rmmod route rpm rpm2cpio strings \
        syslogd telnet tftp time traceroute traceroute6 udhcpc udhcpd \
        unix2dos unlzma unlzop unxz unzip usleep uudecode uuencode \
        vconfig vi wget xz xzcat; do \
            ln -s /bin/busybox /usr/local/bin/$cmd; done 
