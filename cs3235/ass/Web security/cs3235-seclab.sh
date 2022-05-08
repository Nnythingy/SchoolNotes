portable_readlink() {
    DIR="${1%/*}"
    (cd "$DIR" && echo "$(pwd -P)")
}

seclab-run() {
    docker run -i -t --rm --volume=$(pwd):/assignment:rw -a stdin -a stdout -w /assignment -u $(id -u):$(id -g) corank/cs3235-seclab env -i qemu-x86_64 -L /usr/x86_64-linux-gnu/ -0 prog $1
}


seclab-gdb() {
    docker run -i -t --rm --volume=$(pwd):/assignment:rw -a stdin -a stdout -w /assignment -u $(id -u):$(id -g) corank/cs3235-seclab bash -c 'env -i qemu-x86_64 -L /usr/x86_64-linux-gnu/ -0 prog -g 11111 '$1' & gdb-multiarch -ex "target remote localhost:11111" --exec='$1' --symbols='$1
}


seclab-peda() {
    docker run -i -t --rm --volume=$(pwd):/assignment:rw -a stdin -a stdout -w /assignment -u $(id -u):$(id -g) corank/cs3235-seclab bash -c 'env -i qemu-x86_64 -L /usr/x86_64-linux-gnu/ -0 prog -g 11111 '$1' & gdb-multiarch -ex "source /peda/peda.py" -ex "target remote localhost:11111" --exec='$1' --symbols='$1
}

seclab-serve() {
    docker run -i -t --rm --volume="$(portable_readlink $1)":/var/www/html:ro -a stdin -a stdout -p 8080:80  --hostname 127.0.0.1 corank/cs3235-seclab bash -c 'apachectl start > /dev/null 2>&1 && read -p "Press any key to shut down"'
}

seclab-serve-browse() {
    docker run -i -t --rm \
        --volume="$(portable_readlink $1)":/var/www/html:ro \
        --volume=$HOME/.Xauthority:/root/.Xauthority:ro \
        --env=DISPLAY=$DISPLAY --env=XAUTHORITY=/root/.Xauthority \
        --add-host=demo.org:127.0.0.1 \
        --add-host=bbs.demo.org:127.0.0.1 \
        --add-host=blog.demo.org:127.0.0.1 \
        --network=host \
        -a stdin -a stdout --hostname 127.0.0.1 -u student corank/cs3235-seclab bash -c 'sudo /usr/sbin/apachectl start > /dev/null 2>&1 && firefox --new-window http://localhost > /dev/null 2>&1 & read -p "Press any key to shut down"' 
}

seclab-serve-demo() {
    docker run -i -t --rm --volume="$(portable_readlink $1)":/var/www/html:ro -a stdin -a stdout -p 8888:8888 -p 80:80  --hostname 127.0.0.1 corank/cs3235-seclab bash -c 'apachectl start > /dev/null 2>&1 && read -p "Press any key to shut down"'
}

seclab-setup-demo() {
    sudo tee -a /etc/hosts > /dev/null << EOF
127.0.0.1 demo.org
127.0.0.1 bbs.demo.org
127.0.0.1 blog.demo.org
EOF
}

seclab-clean-demo() {
    sudo sed -i'' '/demo.org/d' /etc/hosts
}
