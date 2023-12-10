#!/bin/bash

BASEDIR=$(dirname $(readlink -f "$0"))
CMD=$1

if [ "$CMD" = "" ]; then
	echo "Usage: $0 start/stop"
	exit
fi

if [ "$CMD" = "start" ]; then
        sudo bash $BASEDIR/audit/config.sh
	exit
fi

if [ "$CMD" = "stop" ]; then
        sudo bash $BASEDIR/audit/collect.sh
        exit
fi
