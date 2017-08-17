# docker image with Ansible and basic networking tools
FROM ehlers/ipterm-base

RUN set -ex \
#
# install ansible
#
    && echo "deb [trusted=yes] http://ppa.launchpad.net/ansible/ansible/ubuntu trusty main" > /etc/apt/sources.list.d/ansible.list \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
       ansible \
#
# install dependencies for junos network modules
#
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
       python-lxml python-netaddr python-scp python-serial \

    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
       python-pip python-wheel \
    && pip install --no-cache-dir ncclient jxmlease junos-eznc \
    && apt-get autoremove -y --purge python-pip python-wheel \
    && rm -rf /var/lib/apt/lists/* \
#
# startup script
#
    && /bin/echo -e '\
\x23!/bin/sh\n\
\n\
\x23 symlink /etc/hosts to persistent directory\n\
mount | fgrep -q "on /etc/hosts "\n\
if [ $? -ne 0 ]; then\n\
	[ -s /etc/ansible/etc_hosts ] || cp -p /etc/hosts /etc/ansible/etc_hosts\n\
	ln -sf /etc/ansible/etc_hosts /etc/hosts\n\
fi\n\
\n\
cd; exec bash -i' \
        > /etc/init.sh && chmod +x /etc/init.sh

VOLUME [ "/root", "/etc/ansible" ]
CMD [ "/etc/init.sh" ]
