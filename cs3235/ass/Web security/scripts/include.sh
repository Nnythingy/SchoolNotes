portable_readlink() {
    DIR="${1%/*}"
    (cd "$DIR" && echo "$(pwd -P)")
}

portable_readlink_in() {
    (cd "$1" && echo "$(pwd -P)")
}
