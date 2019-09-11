
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

    SpawnFunction spawnFunction;

   public:
    Spawner(int y, int spawnFrequency, SpawnFunction spawnFunction);
    void Update();
    void Spawn();
    int GetY() { return y; }
    int GetTimesSinceLastSpawn() { return timeSinceLastSpawn; }
    int GetSpawnFrequency() { return spawnFrequency; }
};
#endif  // SPAWNER_H_
