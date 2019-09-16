#ifndef SPAWNERS_LAWNMOWERSPAWNER_H_
#define SPAWNERS_LAWNMOWERSPAWNER_H_

#include "Sprite.h"
#include "Spawner.h"
#include "Logging.h"

#include <functional>
#include <list>

typedef std::function<void(int, int, int)> NPCSpawnAndAddFunction;
struct Node
{
    int spawnTime;
    Node *next;
};

class LANE
{
private:
    Node *head = NULL;
    Node *currentSpawn = NULL;
    int currentSpawnTime = 0;

public:
    int xinc;
    int ypos;
    int xpos;

    LANE(){};
    LANE(int xinc, int xpos, int ypos, std::list<int> spawnTimes)
    {
        this->xinc = xinc;
        this->ypos = ypos;
        this->xpos = xpos;
        initSpawnTimes(spawnTimes);
    }

    void initSpawnTimes(std::list<int> times)
    {
        Node *current = NULL;
        for (auto i : times)
        {
            Node *newItem = new Node();
            newItem->spawnTime = i;
            newItem->next = head;

            if (!current)
            {
                head = newItem;
            }
            else
            {
                current->next = newItem;
            }
            current = newItem;
        }
    }
    bool Update()
    {
        if (currentSpawn == NULL)
        {
            currentSpawn = head;
        }
        currentSpawnTime++;

        if (currentSpawnTime > currentSpawn->spawnTime)
        {
            currentSpawn = currentSpawn->next;
            currentSpawnTime=0;
            return false;
        }
        return true;
    }
};

class LawnmowerSpawner : public Spawner
{
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
