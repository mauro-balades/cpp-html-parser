# Source files
set (SOURCE
    parsing.cc
)

# Add the target
add_executable (run-examples ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${SOURCE})

target_link_libraries (run-examples LINK_PUBLIC HTMLParser)
