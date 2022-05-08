#!/bin/bash

CUR_DIR=$(dirname $(readlink -f $0))

mysql -u root < $CUR_DIR/cleanup.sql

