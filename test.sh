
main() {
    cmake .

    # Rebuild library
    make
    sudo make install

    # compile and run tests
    cd tests

    make
    make test

    cd ..
}

main
