#include <iostream>
#include <memory>
#include <vector>
#include "EnemyTank.h"

namespace Maps {
    const int MAP_X = 20;
    const int MAP_Y = 18;


    extern vector<shared_ptr<EnemyTank>> mapOneEnemyTanks;
    extern int mapOne[MAP_X][MAP_Y];

    extern vector<shared_ptr<EnemyTank>> mapTwoEnemyTanks;
    extern int mapTwo[MAP_X][MAP_Y];
}