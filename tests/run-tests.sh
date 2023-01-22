#!/bin/bash

# Runs tests using environments and stores the result in an outfile
# Runs diff on files to show any issues

# set up function to print results
print_result() {
    if [ "$1" == "" ]
    then
        echo -e "\033[0,32mPassed!\033[0m"
    else 
        echo -e "\033[0,31mFailed!\033[0m"
    fi
}
# First compile the program 
make

# Execute tests with compiled program
# Milestone 2 Tests

echo "Program Testing"

TEST_NAME="Testing: Menu → Select credits - credits.input"
./qwirkle < tests/credits.input > tests/credits.gameout 
TEST=$(diff -w -B tests/credits.output tests/credits.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Menu → Select new game - newGame.input"
./qwirkle T < tests/newGame.input > tests/newGame.gameout 
TEST=$(diff -w tests/newGame.output tests/newGame.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Menu → Exit game - quit.input"
./qwirkle < tests/quit.input > tests/quit.gameout 
TEST=$(diff -w -B tests/quit.output tests/quit.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Top left corner place tiles - corner1.input"
./qwirkle T < tests/corner1.input > tests/corner1.gameout 
TEST=$(diff tests/corner1.output tests/corner1.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Top right corner place tiles - corner2.input"
./qwirkle T < tests/corner2.input > tests/corner2.gameout 
TEST=$(diff tests/corner2.output tests/corner2.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Bottom left corner place tiles - corner3.input"
./qwirkle T < tests/corner3.input > tests/corner3.gameout 
TEST=$(diff tests/corner3.output tests/corner3.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Bottom right corner place tiles - corner4.input"
./qwirkle T < tests/corner4.input > tests/corner4.gameout 
TEST=$(diff tests/corner4.output tests/corner4.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Qwirkle row scoring - qwirkleRow.input"
./qwirkle T < tests/qwirkleRow.input > tests/qwirkleRow.gameout 
TEST=$(diff tests/qwirkleRow.output tests/qwirkleRow.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Qwirkle column scoring - qwirkleColumn.input"
./qwirkle T < tests/qwirkleColumn.input > tests/qwirkleColumn.gameout 
TEST=$(diff tests/qwirkleColumn.output tests/qwirkleColumn.gameout) 
echo $TEST_NAME
print_result $TEST

 