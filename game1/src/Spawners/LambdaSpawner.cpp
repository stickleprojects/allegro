#include "Spawners/LambdaSpawner.h"

LambdaSpawner::LambdaSpawner(int y, int spawnFrequency, SpawnFunction spawnFunction) {
    this->y = y;
    this->spawnFrequency = spawnFrequency;
    this->spawnFunction = spawnFunction;
}

void LambdaSpawner::Spawn() {
    timeSinceLastSpawn = 0;
    spawnFunction(this);
}

void LambdaSpawner::Update() {
    timeSinceLastSpawn++;

    if (timeSinceLastSpawn > spawnFrequency) {
        Spawn();
    }
}

std::string LambdaSpawner::ToString() {
    auto txt = stringFormat("Spawner %d,f=%d,t=%d", y, spawnFrequency, timeSinceLastSpawn);

    return txt;    
}