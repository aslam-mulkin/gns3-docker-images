# FTP and TFTP Server

This image provides an (anonymous) FTP and TFTP server.

The security is very lax, so don't use it in a security
sensitive environment.

I use it mainly for saving/restoring configs on network elements
and as a test image for the GNS3 docker functionality.

## Minimal init

The minimal init system `tini` handles the basic stuff
all docker images need:

- Start the service
- Reaps zombies
- Forwards the stop signal to service processes for a graceful shutdown

For further information, see https://github.com/krallin/tini
