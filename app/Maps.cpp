#ifndef MAPS_CPP
#define MAPS_CPP
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "Maps.h"
#include "EnemyTank.h"




vector<shared_ptr<EnemyTank>> Maps::mapOneEnemyTanks = { make_shared<EnemyTank>(EnemyTank(Maps::filePrefix + "enemyTank-basic-1.png", sf::Vector2f(1024.0f/3, 768.0f/3), 180, 0.4, 2.2, 50, Maps::filePrefix)) };

array<array<int, Maps::MAP_Y>, Maps::MAP_X> Maps::mapOne = {{{1,1,1,1,1,1,1,1,1,1,1,1 },
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
                                                             {1,1,1,1,1,1,1,1,1,1,1,1 } }};



vector<shared_ptr<EnemyTank>> Maps::mapTwoEnemyTanks = { make_shared<EnemyTank>(EnemyTank(Maps::filePrefix + "enemyTank-boss.png", sf::Vector2f(1024.0f/1.8, 768.0f/1.3), 180, 0.4, 2.2, 50, Maps::filePrefix)) };

array<array<int, Maps::MAP_Y>, Maps::MAP_X> Maps::mapTwo = {{{1,1,1,1,1,1,1,1,1,1,1,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,0,0,0,0,0,0,0,0,0,0,1 },
                                                             {1,1,1,1,1,1,1,1,1,1,1,1 } }};


map<int, GameInfo> Maps::levels = {{1, GameInfo(Maps::mapOneEnemyTanks, Maps::mapOne)},
                                   {2, GameInfo(Maps::mapTwoEnemyTanks, Maps::mapTwo)}};

#endif