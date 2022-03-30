
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable( runUnitTests main.cc )

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main)
add_test( runUnitTests runUnitTests )
