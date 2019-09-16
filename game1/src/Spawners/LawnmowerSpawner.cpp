#include "Spawners/LawnmowerSpawner.h"

LawnmowerSpawner::LawnmowerSpawner(int min_x, int max_x, NPCCreatorFunction npcCreatorFunction) {
    initLanes(min_x, max_x);
    this->npcCreatorFunction = npcCreatorFunction;
}

void LawnmowerSpawner::initLanes(int min_x, int max_x)  {
    lanes[0] = LANE(1,min_x, 320);
    lanes[1] = LANE(-1,max_x, 364);
    lanes[2] = LANE(1,min_x, 400);

}
Sprite *LawnmowerSpawner::CreateLawnmowerNPC(int laneIdx) {
    int x = lanes[laneIdx].xpos;
    int directionX = lanes[laneIdx].xinc;
    int y = lanes[laneIdx].ypos;

    return npcCreatorFunction(x, y, directionX);
}

void LawnmowerSpawner::Update() {
    
}


void LawnmowerSpawner::Spawn() {
    
}
