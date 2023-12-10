#!/bin/bash

BASEDIR=$(dirname $(readlink -f "$0"))
OUTDIR=$(dirname $BASEDIR)

folder=$OUTDIR/audit_out

echo "stop system auditing"
service auditbeat stop

echo "copying audit records from /var/log/auditbeat to ${folder}"
cp /var/log/auditbeat/* $folder

echo "change access permissions"
# only the user who creates auditbeat can modify it
chmod -R 555 $folder
chmod 777 $folder
