# BIRD routing daemon, see http://bird.network.cz

FROM debian:jessie

RUN set -ex \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get -y --no-install-recommends install \
        bird vim-tiny \
    && rm -rf /var/lib/apt/lists/* \
    && mv /etc/bird/bird.conf /etc/bird/bird.conf.example \
    && mv /etc/bird/bird6.conf /etc/bird/bird6.conf.example \
    && /bin/echo -e '\
\x23!/bin/sh\n\
\n\
\x23 start bird daemon\n\
mkdir -p /run/bird\n\
[ -s /etc/bird/bird.conf ] && bird\n\
[ -s /etc/bird/bird6.conf ] && bird6\n\
\n\
exec bash -i' \
        > /start_bird.sh && chmod +x /start_bird.sh \
    && /bin/echo -e '\
\x23!/usr/bin/awk -f\n\
\n\
BEGIN {\n\
	if (ARGC < 3 || ARGC > 4) {\n\
		print "Usage: create_routes <start IP> <count> [<output file>]"\n\
		exit 1\n\
	}\n\
\n\
	split(ARGV[1], ip, ".")\n\
	ip[1] += 0; ip[2] += 0; ip[3] += 0; ip[4] += 0\n\
	cnt = ARGV[2]\n\
	out = "/dev/stdout"\n\
	if (ARGC > 3) out = ARGV[3]\n\
\n\
	while (--cnt >= 0) {\n\
		print "route " ip[1] "." ip[2] "." ip[3] "." ip[4] "/32 unreachable;" > out\n\
\n\
		for (i=4; i>0 && ++ip[i] >= 256; i--)\n\
			ip[i] = 0\n\
	}\n\
}' \
        > /usr/local/bin/create_routes && chmod +x /usr/local/bin/create_routes

VOLUME [ "/etc/bird" ]
CMD [ "/start_bird.sh" ]
