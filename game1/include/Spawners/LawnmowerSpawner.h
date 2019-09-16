#ifndef SPAWNERS_LAWNMOWERSPAWNER_H_
#define SPAWNERS_LAWNMOWERSPAWNER_H_

#include "Sprite.h"
#include "Spawner.h"
#include "Logging.h"

#include <functional>

typedef std::function<void(int,int,int)> NPCSpawnAndAddFunction;

struct LANE {
    int xinc;
    int ypos;
    int xpos;

    LANE(int xinc,int xpos, int ypos) {
        this->xinc = xinc;
        this->ypos = ypos;
        this->xpos = xpos;
    }
    LANE(){}
};

class LawnmowerSpawner:public Spawner {
    private:
        void spawnLawnmowerNPC(int laneIdx);
        LANE lanes[3];
        void initLanes(int minx, int maxx);
        NPCSpawnAndAddFunction npcSpawnAndAddFunction;

    public:
        LawnmowerSpawner(int minx, int maxx, NPCSpawnAndAddFunction npcSpawnAndAddFunction);
        void Update() override;
        void Spawn() override;
        
};

#endif // SPAWNERS_LAWNMOWERSPAWNER_H_
