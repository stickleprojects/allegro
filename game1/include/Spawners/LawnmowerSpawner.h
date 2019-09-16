#ifndef SPAWNERS_LAWNMOWERSPAWNER_H_
#define SPAWNERS_LAWNMOWERSPAWNER_H_

#include "Sprite.h"
#include "Spawner.h"

#include <functional>

typedef std::function<Sprite*(int,int,int)> NPCCreatorFunction;

struct LANE {
    int xinc;
    int ypos;
    int xpos;

    LANE(int xinc,int xpos, int ypos) {
        this->xinc = xinc;
        this->ypos = ypos;
        this->xpos = xpos;
    }
};

class LawnmowerSpawner:public Spawner {
    private:
        Sprite* CreateLawnmowerNPC(int laneIdx);
        LANE lanes[3];
        void initLanes(int minx, int maxx);
        NPCCreatorFunction npcCreatorFunction;
        
    public:
        LawnmowerSpawner(int minx, int maxx, NPCCreatorFunction npcCreatorFunction);
        void Update() override;
        void Spawn() override;
        
};

#endif // SPAWNERS_LAWNMOWERSPAWNER_H_
