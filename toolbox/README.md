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

- toolbox-base  
  This image includes the common utilities mentioned previously.
  It creates the foundation for the next images.
  It's not intended, that the user directly uses this image.
- toolbox-cli  
  It adds a default command (bash) and a persistent directory (/root)
  to the toolbox-base image.
- toolbox-web  
  This adds the Firefox web browser to the toolbox.
  Like toolbox-cli, the /root directory is persistent.

## Build, run and publish

First the base image has to be created:

```
docker build -t gns3/toolbox-base base
docker push gns3/toolbox-base
```

Afterwards the cli and/or the web images can be build:

```
docker build -t gns3/toolbox cli
docker push gns3/toolbox
```

```
docker build -t gns3/toolbox-web web
docker push gns3/toolbox-web
```
