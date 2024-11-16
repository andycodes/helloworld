#!/bin/sh
module="cdata"
device="cdata"
mode="777"


major=234
echo "major number= $major"

rm -f /dev/${device}

set -o xtrace
mknod /dev/${device} c $major 0
set +o xtrace

insmod ./$module.ko $* || exit 1
ls -l /dev/${device}
