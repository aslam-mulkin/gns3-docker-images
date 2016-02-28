#!/bin/sh
# init.sh - GNS3 specific docker initialization

# Wait 2 seconds to settle the network interfaces
sleep 2

# /etc/hosts
[ -s /etc/hosts ] || cat > /etc/hosts << __EOF__
127.0.1.1	$HOSTNAME
127.0.0.1	localhost
::1	localhost ip6-localhost ip6-loopback
fe00::0	ip6-localnet
ff00::0	ip6-mcastprefix
ff02::1	ip6-allnodes
ff02::2	ip6-allrouters
__EOF__

# configure loopback interface
ip link set dev lo up

# configure eth interfaces
sed -n 's/^ *\(eth[0-9]*\):.*/\1/p' < /proc/net/dev | while read dev; do
	eval ip=\$IP_$dev
	[ -n "$ip" ] && ip -family inet address add $ip dev $dev
	eval ip=\$IPv6_$dev
	[ -n "$ip" ] && ip -family inet6 address add $ip dev $dev
	ip link set dev $dev up
done

# IP routes
[ -n "$IP_default_gw" ] && \
	ip -family inet route add default via $IP_default_gw
for i in "" 0 1 2 3 4 5 6 7 8 9; do
	eval route=\$IP_route$i
	net=${route%% *}
	dest=${route#* } ; dest=${dest%% *}
	[ -n "$dest" ] && ip -family inet route add $net via $dest
done

# IPv6 routes
[ -n "$IPv6_default_gw" ] && \
	ip -family inet6 route add default via $IPv6_default_gw
for i in "" 0 1 2 3 4 5 6 7 8 9; do
	eval route=\$IPv6_route$i
	net=${route%% *}
	dest=${route#* } ; dest=${dest%% *}
	[ -n "$dest" ] && ip -family inet6 route add $net via $dest
done

# start shell in background
echo '(sleep 1; kill $$) &' > /tmp/start_sh
echo 'bash 2>&1' >> /tmp/start_sh
sh /tmp/start_sh 2> /dev/null
rm /tmp/start_sh
echo

# continue normal docker startup
exec "$@"
