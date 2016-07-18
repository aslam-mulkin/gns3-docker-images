# snmp - SNMP tools

This image includes the NET-SNMP tools (snmpget, snmpset, snmpwalk)
and the SNMP MIB browser qtmib (see http://qtmib.sourceforge.net).

Furthermore the basic networking tools from ipterm are included.

Like ipterm, the /root directory is persistent.

## Build the Image

Before ipterm-base has to be build.

```
docker build -t snmp .
```
