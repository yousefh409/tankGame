#ifndef MAPS_H
#define MAPS_H
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <array>
#include "EnemyTank.h"

struct GameInfo; //Forward Decleration

namespace Maps {
    static const string filePrefix = "../data/";
    static const int numLevels = 2;

    static const int MAP_X = 20;
    static const int MAP_Y = 18;


    extern vector<shared_ptr<EnemyTank>> mapOneEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapOne;

    extern vector<shared_ptr<EnemyTank>> mapTwoEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapTwo;

    extern map<int, GameInfo> levels;
}


struct GameInfo {
    vector<shared_ptr<EnemyTank>> enemyTanks;
    array<array<int, Maps::MAP_Y>, Maps::MAP_X> mapArray;

    GameInfo(vector<shared_ptr<EnemyTank>> e, array<array<int, Maps::MAP_Y>, Maps::MAP_X> m) : enemyTanks(e), mapArray(m) {}
    GameInfo() = default;
};
#endif

