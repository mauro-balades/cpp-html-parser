
main() {
    cmake .

    # Rebuild library
    make
    sudo make install

    # compile and run tests
    cd examples

    make
    make run-examples

    cd ..
}

main
