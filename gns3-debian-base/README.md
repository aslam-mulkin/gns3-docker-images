# GNS3 Base Image for Debian Jessie

This base image is divided into two parts:

## GNS3 specific section

Currently the enviroment of docker containers started by GNS3
differs from the normal docker environment.

1. The interfaces (including loopback) are not enabled
2. IP addresses are not configured
3. No (default) routes
4. /etc/hosts is empty
5. /etc/resolv.conf is empty

GNS3 already handles item #1 and #4 by it's own init script,
`__gns3__/init.sh` does the IP address and route configuration (#2 and #3).
In future GNS3 (hopefully) will take over also those tasks,
then docker images will need no special adaption for GNS3.

## Minimal init

The minimal init system `dumb-init` handles the basic stuff
all docker images need:

- Start the service
- Reaps zombies
- Forwards the stop signal to service processes for a graceful shutdown

For further information, see https://github.com/Yelp/dumb-init

Furthermore it adds busybox to the image and links all commands to busybox,
that busybox provides but that are not included in the base debian image.
This provides some useful commands with minimum overhead for debugging.
It's not recommended to use them for creating a service,
use the regular debian packages for that.

