ps -A | grep qemu-system-arm | awk '{print $1}' | xargs sudo kill -9
#ps -A | grep java | awk '{print $1}' | xargs sudo kill -9
