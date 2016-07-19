# scapy - scapy plus networking toolbox

This image adds scapy, a python program that enables the user
to send, sniff and dissect and forge network packets.
For further information see http://scapy.readthedocs.io/en/latest/

This appliance contains the following networking tools:

- scapy
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

## Build the Image

Before ipterm-base has to be build.

```
docker build -t scapy .
```
