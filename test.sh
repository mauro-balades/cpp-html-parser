
main() {
    cmake -DCMAKE_BUILD_TYPE=Debug .

    # Rebuild library
    make
    # make clean
    sudo make install

    # compile and run tests
    cd tests

    make
    ctest -VV --output-on-failure

    cd ..
}

main
