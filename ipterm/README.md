# ipterm - Networking Toolbox

This appliance contains the following networking tools:

- net-tools (basic network administration tools)
- iproute2 (advanced network administration tools)
- ping and traceroute
- curl (data transfer utility)
- host (DNS lookup utility)
- iperf3
- mtr (full screen traceroute)
- socat (utility for reading/writing from/to network connections)
- ssh client
- tcpdump
- telnet
- mtools (multicast tools msend & mreceive),
  see https://github.com/troglobit/mtools

It is divided into several sub-images:

- ipterm-base  
  This image includes the common utilities mentioned previously.
  It creates the foundation for the next images.
  It's not intended, that the user directly uses this image.
- ipterm  
  Based on ipterm-base it sets bash as the default command and
  uses /root as a persistent directory.
- webterm  
  This adds the Firefox web browser to ipterm-base.
  Like ipterm, the /root directory is persistent.

## Build and publish the Images

First the base image has to be created:

```
docker build -t ipterm-base base
docker push ipterm-base    (optional)
```

Afterwards the cli and/or the web image can be built:

```
docker build -t ipterm cli
docker push ipterm
```

```
docker build -t webterm web
docker push webterm
```
