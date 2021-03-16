#ifndef MAPS_H
#define MAPS_H
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <array>
#include "EnemyTank.h"
#include "SFML/Graphics.hpp"


struct GameInfo; //Forward Decleration

namespace Maps {
    static const string filePrefix = "../data/";
    static const int numLevels = 13;

    static const int MAP_X = 20;
    static const int MAP_Y = 18;


    extern vector<shared_ptr<EnemyTank>> mapOneEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapOne;

    extern vector<shared_ptr<EnemyTank>> mapTwoEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapTwo;

    extern vector<shared_ptr<EnemyTank>> mapThreeEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapThree;

    extern vector<shared_ptr<EnemyTank>> mapFourEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapFour;

    extern vector<shared_ptr<EnemyTank>> mapFiveEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapFive;

    extern vector<shared_ptr<EnemyTank>> mapSixEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapSix;

    extern vector<shared_ptr<EnemyTank>> mapSevenEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapSeven;

    extern vector<shared_ptr<EnemyTank>> mapEightEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapEight;

    extern vector<shared_ptr<EnemyTank>> mapNineEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapNine;

    extern vector<shared_ptr<EnemyTank>> mapTenEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapTen;

    extern vector<shared_ptr<EnemyTank>> mapElevenEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapEleven;

    extern vector<shared_ptr<EnemyTank>> mapTwelveEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapTwelve;

    extern vector<shared_ptr<EnemyTank>> mapThirteenEnemyTanks;
    extern array<array<int, MAP_Y>, MAP_X> mapThirteen;

    extern map<int, GameInfo> levels;

    extern map<int, sf::Vector2f> mainTankPositions;
}


struct GameInfo {
    vector<shared_ptr<EnemyTank>> enemyTanks;
    array<array<int, Maps::MAP_Y>, Maps::MAP_X> mapArray;

    GameInfo(vector<shared_ptr<EnemyTank>> e, array<array<int, Maps::MAP_Y>, Maps::MAP_X> m) : enemyTanks(e), mapArray(m) {}
    GameInfo() = default;
};
#endif

