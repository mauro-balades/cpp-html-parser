# Source files
set (SOURCE
    test_attrs.cc
    test_basics.cc
    test_tokenizer.cc
)

# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add the target
add_executable (run-tests ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${SOURCE})

# Link it to gtest
target_link_libraries(run-tests LINK_PRIVATE gtest gtest_main)

if (BUILD_SHARED_LIBS)
    target_compile_definitions(run-tests PRIVATE -DGTEST_LINKED_AS_SHARED_LIBRARY)
endif()

target_link_libraries (run-tests LINK_PUBLIC HTMLParser)

# For `make test`
add_test(NAME html-parser-testing
         COMMAND run-tests --gtest_color=yes
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
