#!/bin/bash

CASE_COUNT=5

for i in $(seq $CASE_COUNT); do
	cookie_value=$(openssl rand --hex 20)
	flag_value=$(openssl rand --hex 20)
	echo $cookie_value $flag_value
done > $1

