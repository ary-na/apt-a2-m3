#include "../include/MultipleMoves.h"

MultipleMoves::MultipleMoves() {
    this->rows = std::vector<char>();
    this->cols = std::vector<int>();
}

MultipleMoves::MultipleMoves(const MultipleMoves &other) {
    this->rows = other.rows;
    this->cols = other.cols;
}

MultipleMoves::MultipleMoves(MultipleMoves &&other) : rows(other.rows), cols(other.cols) {}

MultipleMoves::~MultipleMoves() = default;

bool MultipleMoves::isRowMatch(char row) {
    bool rowMatch = true;
    if (this->rows.size() >= 1) {
        for (auto &vectorRow: this->rows) {
            if (vectorRow != row) {
                rowMatch = false;
                this->cols.pop_back();
            }
        }
    }
    return rowMatch;
}

bool MultipleMoves::isColMatch(int col) {
    bool colMatch = true;
    if (this->rows.size() >= 1) {
        for (auto &vectorCol: this->cols) {
            if (vectorCol != col) {
                colMatch = false;
                this->cols.pop_back();
            }
        }
    }
    return colMatch;
}

void MultipleMoves::addRow(char row) {
    this->rows.push_back(row);
}

void MultipleMoves::addCol(int col) {
    this->cols.push_back(col);
}
