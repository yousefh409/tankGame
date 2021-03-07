#include "Maps.h"


vector<shared_ptr<EnemyTank>> Maps::mapOneEnemyTanks = { make_shared<PeriodicFire>(PeriodicFire("images/enemyTank1.png", sf::Vector2f(1024.0f/4, 768.0f/4), 0, 0.4, 2)),
                                                         make_shared<PeriodicFire>(PeriodicFire("images/enemyTank2.png", sf::Vector2f(1024.0f/1.8, 768.0f/1.3), 180, 0.4, 2.2)) };

int Maps::mapOne[MAP_X][MAP_Y] =   { {1,1,1,1,1,1,1,1,1,1,1,1 },
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



vector<shared_ptr<EnemyTank>> Maps::mapTwoEnemyTanks = { make_shared<PeriodicFire>(PeriodicFire("images/enemyTank2.png", sf::Vector2f(1024.0f/1.8, 768.0f/1.3), 180, 0.4, 2.2)) };

int Maps::mapTwo[MAP_X][MAP_Y] = { {1,1,1,1,1,1,1,1,1,1,1,1 },
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
