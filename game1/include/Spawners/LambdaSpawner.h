
#ifndef LAMBDASPAWNER_H_
#define LAMBDASPAWNER_H_

#include "Spawner.h"

#include <functional>

typedef std::function<void(Spawner*)> SpawnFunction;

class LambdaSpawner:public Spawner {
   private:
    int y;
    int spawnFrequency;
    int timeSinceLastSpawn = 0;

    SpawnFunction spawnFunction;

   public:
    LambdaSpawner(int y, int spawnFrequency, SpawnFunction spawnFunction);
    void Update() override;
    void Spawn() override;
    std::string ToString() override;
};
#endif  // LAMBDASPAWNER_H_
