
main() {
    cmake .

    # Rebuild library
    make
    sudo make install

    cd examples
    cmake .
}

main
