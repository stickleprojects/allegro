
#ifndef SPAWNER_H_
#define SPAWNER_H_

#include <functional>
class Spawner;

typedef std::function<void(Spawner*)> SpawnFunction;

class Spawner {
   private:
    int y;
    int spawnFrequency;
    int timeSinceLastSpawn = 0;
    void spawn();
    SpawnFunction spawnFunction;

   public:
    Spawner(int y, int spawnFrequency, SpawnFunction spawnFunction);
    void Update();
};
#endif  // SPAWNER_H_
