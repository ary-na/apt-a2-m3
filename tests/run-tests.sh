#!/bin/bash

# Runs tests using environments and stores the result in an outfile
# Runs diff on files to show any issues

# First compile the program 
make

# Execute tests with compiled program
# Milestone 2 Tests

echo "Program Testing"

echo "Menu → Select credits"
./qwirkle < tests/credits.input > tests/credits.gameout 
diff -w -B tests/credits.output tests/credits.gameout 

echo "Menu → Select new game"
./qwirkle T < tests/newGame.input > tests/newGame.gameout 
diff -w tests/newGame.output tests/newGame.gameout 

echo "Menu → Exit game"
./qwirkle < tests/quit.input > tests/quit.gameout 
diff -w -B tests/quit.output tests/quit.gameout 

echo "Top left corner place tiles"
./qwirkle T < tests/corner1.input > tests/corner1.gameout 
diff tests/corner1.output tests/corner1.gameout 

echo "Top right corner place tiles"
./qwirkle T < tests/corner2.input > tests/corner2.gameout 
diff tests/corner2.output tests/corner2.gameout 

echo "Bottom left corner place tiles"
./qwirkle T < tests/corner3.input > tests/corner3.gameout 
diff tests/corner3.output tests/corner3.gameout 

echo "Bottom right corner place tiles"
./qwirkle T < tests/corner4.input > tests/corner4.gameout 
diff tests/corner4.output tests/corner4.gameout 

echo "Qwirkle row scoring"
./qwirkle T < tests/qwirkleRow.input > tests/qwirkleRow.gameout 
diff tests/qwirkleRow.output tests/qwirkleRow.gameout 

echo "Qwirkle column scoring"
./qwirkle T < tests/qwirkleColumn.input > tests/qwirkleColumn.gameout 
diff tests/qwirkleColumn.output tests/qwirkleColumn.gameout 

 