#ifndef SCORE_H
#define SCORE_H
#include <iostream>

using namespace std;

class Score {
private:
    unsigned int levelIndex;
    unsigned int levelScore;
public:
    Score(unsigned int i, unsigned int s) : levelIndex(i), levelScore(s) {}
    Score() : levelIndex(0), levelScore(0) {}

    friend ostream& operator<< (ostream& out, Score& output);
    friend istream& operator>> (istream& in,  Score& input);

    bool operator<(const Score& comp) const;
    bool operator>(const Score& comp) const;
    bool operator==(const Score& comp) const;

    unsigned getLevel() const { return levelIndex; }
    unsigned getScore() const { return levelScore; }

    void incrScore(unsigned increase) { levelScore += increase; }
};
#endif
