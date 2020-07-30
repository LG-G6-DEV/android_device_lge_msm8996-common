#!/system/bin/sh
# loggy.sh.

_date=`date +%F_%H-%M-%S`
logcat -b all -f  /cache/logcat_${_date}.log &
dmesg -w > /cache/kmsg_${_date}.log &

exit 0
