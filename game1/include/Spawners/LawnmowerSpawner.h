#ifndef SPAWNERS_LAWNMOWERSPAWNER_H_
#define SPAWNERS_LAWNMOWERSPAWNER_H_

#include "Spawner.h"

class LawnmowerSpawner:public Spawner {
    public:
        LawnmowerSpawner();
        void Update() override;
        void Spawn() override;
        
};

#endif // SPAWNERS_LAWNMOWERSPAWNER_H_
