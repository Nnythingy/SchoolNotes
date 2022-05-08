export QEMU_IMAGE_NAME="corank/qemu"


portable_readlink() {
    DIR="${1%/*}"
    (cd "$DIR" && echo "$(pwd -P)")
}

portable_readlink_in() {
    (cd "$1" && echo "$(pwd -P)")
}

qemu_exec() {
    docker exec -it \
        seclab-qemu \
        ssh localhost -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null \
            -o LogLevel=quiet -o ConnectTimeout=5 \
            -p 5555 -l student -t /bin/bash -c "\"${@}\""
}

