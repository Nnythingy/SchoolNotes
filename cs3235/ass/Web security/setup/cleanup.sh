#!/bin/bash

CUR_DIR=$(dirname $(readlink -f $0))

rm -rf $JUDGE_TARGET_SITE_DIR/*
rm -rf $JUDGE_ATTACKER_SITE_DIR/*

sudo mysql -u root -p'testpass' < $CUR_DIR/cleanup.sql

