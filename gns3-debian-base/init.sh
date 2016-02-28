#!/bin/sh
# init.sh - start the service and a shell, then wait for termination

# Trap handling
trap_stop() {
	echo; echo; echo "*** Stopping container..."
	# kill all subprocesses
	kill $(pgrep -P 1) 2> /dev/null
	sleep 2
	exit 0
}
trap 'trap_stop' TERM

trap_child() {
	trap '' CHLD
	# find zombie processes
	pids=`ps -e -o pid,ppid,stat | awk '$2 == '$$' && $3 ~ /Z/ {print $1}'`
	[ -n "$pids" ] && wait $pids
	trap 'trap_child' CHLD
}
trap 'trap_child' CHLD

# start service, must background itself
[ $# -gt 0 ] && "$@"

# wait forever
mkfifo /tmp/.init_do_not_delete 2> /dev/null
while [ true ]; do
	read < /tmp/.init_do_not_delete
done 2> /dev/null
