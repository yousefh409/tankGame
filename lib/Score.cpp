#include <iostream>
#include "Score.h"

using namespace std;

ostream& operator<< (ostream& out, Score& output) {
    out << output.levelIndex << "   " << output.levelScore << endl;
    return out;
}

istream& operator>> (istream& in,  Score& input) {
    in >> input.levelIndex >> input.levelScore;
    return in;
}

bool Score::operator<(const Score& comp) const {
    return (levelScore < comp.levelScore);
}

bool Score::operator>(const Score& comp) const {
    return (levelScore > comp.levelScore);
}

bool Score::operator==(const Score& comp) const {
    return (levelScore == comp.levelScore);
}
