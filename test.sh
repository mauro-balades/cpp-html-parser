
main() {
    cmake .

    # Rebuild library
    make
    sudo make install

    # compile and run tests
    cd tests

    make
    ctest -V --output-on-failure

    cd ..
}

main
