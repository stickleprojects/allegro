
#ifndef SPAWNER_H_
#define SPAWNER_H_

#include <string>

#include "StringFormat.h"

class Spawner {
   public:
    virtual void Update();
    virtual void Spawn();
    virtual std::string ToString();
};

#endif  // SPAWNER_H_
