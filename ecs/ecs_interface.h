#ifndef _ECS_INTERFACE_H_
#define _ECS_INTERFACE_H_

#include "entity.h"
#include "system.h"
#include "component.h"
#include "types.h"

namespace ECS {
void AddSystem(const System& system);
void Tick();
}

#endif //_ECS_INTERFACE_H_
