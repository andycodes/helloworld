

# get local ip addr
local_ip=$(ifconfig eth0 | grep 'inet ' | awk '{print $2}'| cut -f2 -d:)
echo local_ip: $local_ip

# get cpu idle 
cpu_idle=$(mpstat | grep all | awk '{print $11}')
echo cpu_idle: $cpu_idle

# get mem free
free_mem=$(free | grep Mem | awk '{print $4}')
echo free_mem: $free_mem

# get mem total
total_mem=$(free | grep Mem | awk '{print $2}')
echo total_mem: $total_mem

# mem free pcent
free_mem_pcent=$(free | grep Mem | awk '{print $4/$2}')
echo free_mem_pcent: $free_mem_pcent