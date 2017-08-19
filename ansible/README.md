# Ansible

Ansible is a radically simple IT automation system. It handles
configuration-management, application deployment, cloud provisioning,
ad-hoc task-execution, and multinode orchestration.
For further information see http://docs.ansible.com/ansible/index.html and
the sources at https://github.com/ansible/ansible .

This appliance contains the following networking tools:

- Ansible  
  including the dependencies for the junos network modules
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
docker build -t ansible .
```
