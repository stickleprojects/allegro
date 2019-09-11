#include "Spawner.h"

Spawner::Spawner(int y, int spawnFrequency, SpawnFunction spawnFunction) {
    this->y = y;
    this->spawnFrequency = spawnFrequency;
    this->spawnFunction = spawnFunction;
}

void Spawner::Spawn() {
    timeSinceLastSpawn = 0;
    spawnFunction(this);
}

void Spawner::Update() {
    timeSinceLastSpawn++;

    if (timeSinceLastSpawn > spawnFrequency) {
        Spawn();
    }
}
