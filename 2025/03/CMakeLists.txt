configure_file(input.txt input.txt COPYONLY)
configure_file(input_example.txt input_example.txt COPYONLY)

add_executable(aoc_03
    main.cpp
)