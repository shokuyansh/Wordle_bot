cmake_minimum_required(VERSION 4.2.3)
project(wordle_bot)
enable_testing()
set(SOURCE_FILES
    main.cpp
    engine.cc
    game_loop.cc
)
set(TEST_FILES
    testing.cc
    engine.cc
    game_loop.cc
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_executable(wordle_bot_test ${TEST_FILES})
add_test(NAME performance_test COMMAND wordle_bot_test)
