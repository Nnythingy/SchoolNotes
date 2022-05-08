#!/bin/bash
nohup authbind --deep qemu-system-x86_64 image.qcow2 -m 1024 -smp 4 \
	-enable-kvm -nographic \
	-device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::5555-:22,hostfwd=tcp::8888-:80,hostfwd=tcp::80-:80 &
echo "Launching VM..."

sleep 15

ssh -p 5555 \
	-o "UserKnownHostsFile /dev/null" \
	-o "PreferredAuthentications password" \
	-o "PubkeyAuthentication no" \
	demo@127.0.0.1 

