#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "EnemyTank.h"

namespace Maps {
    const int MAP_X = 20;
    const int MAP_Y = 18;

    const int mapOneNumEnemies = 2;
    vector<shared_ptr<EnemyTank>> mapOneEnemyTanks = { make_shared<PeriodicFire>(PeriodicFire("images/enemyTank1.png", sf::Vector2f(1024.0f/4, 768.0f/4), 0, 0.4, 2)),
                                                       make_shared<PeriodicFire>(PeriodicFire("images/enemyTank2.png", sf::Vector2f(1024.0f/1.8, 768.0f/1.3), 180, 0.4, 2.2)) };
    int mapOne[MAP_X][MAP_Y] = { {1,1,1,1,1,1,1,1,1,1,1,1 },
                                 {1,0,0,0,0,0,0,0,0,0,0,1 },
                                 {1,0,0,0,0,0,0,0,0,0,0,1 },
                                 {1,0,0,0,0,0,0,0,0,0,0,1 },
                                 {1,0,0,0,0,0,0,0,0,0,0,1 },
                                 {1,0,0,0,0,1,0,0,0,0,0,1 },
                                 {1,0,0,0,0,1,0,0,0,0,0,1 },
                                 {1,0,0,0,0,1,0,0,0,0,0,1 },
                                 {1,0,0,0,0,1,0,0,0,0,0,1 },
                                 {1,0,0,0,0,0,0,0,0,0,0,1 },
                                 {1,0,0,0,0,0,0,0,0,0,0,1 },
                                 {1,0,0,0,0,0,0,0,0,0,0,1 },
                                 {1,0,0,0,0,0,0,0,0,0,0,1 },
                                 {1,0,0,0,0,0,0,1,0,0,0,1 },
                                 {1,0,0,0,0,0,0,1,1,1,1,1 },
                                 {1,0,0,0,0,0,0,0,0,0,0,1 },
                                 {1,0,0,0,0,0,0,0,0,0,0,1 },
                                 {1,0,0,0,0,0,0,0,0,0,0,1 },
                                 {1,0,0,0,0,0,0,0,0,0,0,1 },
                                 {1,1,1,1,1,1,1,1,1,1,1,1 } };

}
