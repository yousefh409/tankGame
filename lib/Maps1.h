#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "EnemyTank.h"

struct maps {
    static const int MAP_X = 20;
    static const int MAP_Y = 18;
	int m[MAP_X][MAP_Y];
};
struct maps makeMapOne()
{
    struct maps map1 = {
        {
            {1,1,1,1,1,1,1,1,1,1,1,1 },
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
            {1,1,1,1,1,1,1,1,1,1,1,1 },
         }
	};
	return map1;
}

class Map
{
private:
	int mapNumEnemies;
	vector<shared_ptr<EnemyTank>> mapEnemyTanks;
    maps map;

public:
 
    //Constuctor
    Map();
    //setters
	void setMapNumEnemies(int n) { mapNumEnemies = n; }
	void setmapEnemyTanks(); // work in progress
    void setMap();

    //getters
	vector<shared_ptr<EnemyTank>> getMapEnemyTank() { return mapEnemyTanks; }
	int getMapNumEnemies() { return mapNumEnemies; }
    struct maps& getMap() { return& map; }
	
	
};

