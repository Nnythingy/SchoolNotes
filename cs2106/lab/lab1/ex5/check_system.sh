#!/bin/bash

####################
# Lab 1 Exercise 5
# Name: Ng Jong Ray, Edward
# Student No: A0216695U
# Lab Group: B05
####################

# Fill the below up
hostname=$(uname -n)
machine_hardware=$(uname -m)
max_user_process_count=$(ulimit -u)
user_process_count=$(ps -u $(who | awk {'print $1'}) | awk 'END {print NR}')
user_with_most_processes=$(ps -ef | awk {'print $1'} | uniq -c | sort -n | awk 'END {print $2}')
mem_free_percentage=$(awk '/MemFree/{free=$2} /MemTotal/{total=$2} END{print (free*100)/total}' /proc/meminfo)
swap_free_percentage=$(awk '/SwapFree/{free=$2} /SwapTotal/{total=$2} END{print (free*100)/total}' /proc/meminfo)

echo "Hostname: $hostname"
echo "Machine Hardware: $machine_hardware"
echo "Max User Processes: $max_user_process_count"
echo "User Processes: $user_process_count"
echo "User With Most Processes: $user_with_most_processes"
echo "Memory Free (%): $mem_free_percentage"
echo "Swap Free (%): $swap_free_percentage"
