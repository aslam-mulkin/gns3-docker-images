# iou-base - Base Image for running IOU images in Docker

Cisco IOU is quite complicate to integrate, it needs 32-bit shared libraries,
a special NETMAP configuration file and iouyap (https://github.com/GNS3/iouyap)
to communicate to the outside world.

To ease that, this image packs all the necessary tools in a base image.

With `create-iou-image <image> <license> <startup-config> [<private-config>]`
the user creates new self-contained docker IOU images by adding the IOU
binary, license and startup configuration to this base image.

## Build the Image

```
docker build -t iou-base .
```

The 32-bit libraries were copied from Debian 8 (Jessie) by `sh get_libc-i386`.
