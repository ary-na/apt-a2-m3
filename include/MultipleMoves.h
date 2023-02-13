#ifndef MULTIPLEMOVES_H
#define MULTIPLEMOVES_H

#include <vector>

class MultipleMoves {

public:

    MultipleMoves();

    MultipleMoves(const MultipleMoves &other);

    MultipleMoves(MultipleMoves &&other);

    ~MultipleMoves();

    bool isRowMatch(char row);

    bool isColMatch(int col);

    void addRow(char row);

    void addCol(int col);

private:
    std::vector<char> rows;
    std::vector<int> cols;
};


#endif //MULTIPLEMOVES_H
