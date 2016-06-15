# Networking Toolbox

This appliance contains the following networking tools:

- net-tools (basic network administration tools)
- iproute2 (advanced network administration tools)
- ping and traceroute
- iperf3
- ssh client
- tcpdump
- telnet
- mtools (multicast tools msend & mreceive),
  see https://github.com/troglobit/mtools

It is divided into several sub-images:

- nettools-base  
  This image includes the common utilities mentioned previously.
  It creates the foundation for the next images.
  It's not intended, that the user directly uses this image.
- nettools-cli  
  It adds a default command (bash) and a persistent directory (/root)
  to the nettools-base image.
- nettools-web  
  This adds the Firefox web browser to the nettools.
  Like nettools-cli, the /root directory is persistent.

## Build and publish the Images

First the base image has to be created:

```
docker build -t gns3/nettools-base base
docker push gns3/nettools-base
```

Afterwards the cli and/or the web image can be build:

```
docker build -t gns3/nettools cli
docker push gns3/nettools
```

```
docker build -t gns3/nettools-web web
docker push gns3/nettools-web
```
