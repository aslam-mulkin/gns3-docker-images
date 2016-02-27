# GNS3 Base Image for Debian Jessie

This base image is divided into two parts:

## GNS3 specific section

Currently the enviroment of docker containers started by GNS3
differs from the normal docker environment.

- The interfaces (including loopback) are not enabled
- IP addresses are not configured
- No (default) routes
- /etc/hosts is empty
- /etc/resolv.conf is empty

`__GNS3__/init.sh` takes care about that.
It should be easily portable to other linux distributions.

In future GNS3 (hopefully) will take over that task,
then docker images need no special adaption for GNS3.

## Simple Init

The simple shell script `init.sh` handles the basic stuff
all docker images need:

- Start the service
- Start a shell
- Reaps zombies
- Forwards the stop signal to service processes for a graceful shutdown

Starting the shell is mainly useful in the GNS3 environment,
as there is currently no "docker exec" equivalent.
So that might be moved to the GNS3 specific part or removed altogether.

Furthermore it adds busybox to the image and links all commands to busybox,
that busybox provides but that are not included in the base debian image.
This provides some useful commands with minimum overhead for debugging.
It's not recommended to use them for creating a service,
use the regular debian packages for that.

