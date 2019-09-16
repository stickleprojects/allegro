#include "Spawners/LawnmowerSpawner.h"

LawnmowerSpawner::LawnmowerSpawner(int min_x, int max_x, NPCSpawnAndAddFunction npcSpawnAndAddFunction)
{
    initLanes(min_x, max_x);
    this->npcSpawnAndAddFunction = npcSpawnAndAddFunction;
}

void LawnmowerSpawner::initLanes(int min_x, int max_x)
{
    int gap = 150;
    int big_gap=2;
    lanes[0] = LANE(1, min_x, 320, {gap, gap, gap*big_gap});
    lanes[1] = LANE(-1, max_x, 364, {gap,  gap*big_gap});
    lanes[2] = LANE(1, min_x, 400, {gap, gap,  gap*big_gap});
}
void LawnmowerSpawner::spawnLawnmowerNPC(int laneIdx)
{
    if (laneIdx >2)
    {
        SPDLOG_ERROR("lawnmower spawn out of range %d", laneIdx);
        return;
    }
 
    int x = lanes[laneIdx].xpos;
    int directionX = lanes[laneIdx].xinc;
    int y = lanes[laneIdx].ypos;
    npcSpawnAndAddFunction(x, y, directionX);
}

void LawnmowerSpawner::Update()
{
    // do nowt, although we should trigger a respawn here
    for(int l=0; l <=2 ; l++) {
        if(!lanes[l].Update()) {
            spawnLawnmowerNPC(l);
        }
    }
}

void LawnmowerSpawner::Spawn()
{
    SPDLOG_DEBUG("lawnmower::spawn!!!!");
    // spawn in each lane
    for (auto i = 0; i <= 2; i++)
    {
        spawnLawnmowerNPC(i);
    }
}
