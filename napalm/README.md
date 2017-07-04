# NAPALM - Network Automation and Programmability Abstraction Layer with Multivendor support

This image adds NAPALM, a python library that implements a set of functions
to interact with different router vendor devices using a unified API.
For further information see https://napalm.readthedocs.io/ and
the sources at https://github.com/napalm-automation .

This appliance contains the following networking tools:

- NAPALM
- Netmiko
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
docker build -t napalm .
```
