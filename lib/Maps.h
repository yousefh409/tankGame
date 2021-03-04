#include <iostream>
#include <memory>
#include <vector>
#include "EnemyTank.h"

namespace Maps {
    const int MAP_X = 20;
    const int MAP_Y = 18;


    const int mapOneNumEnemies = 2;
    extern vector<shared_ptr<EnemyTank>> mapOneEnemyTanks;
    extern int mapOne[MAP_X][MAP_Y];
}
