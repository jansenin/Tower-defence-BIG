#include "system.h"

namespace ECS {
void System::OnComponentBeingAddedTo(const Entity& entity) {
  if (ShouldBeConsideredBySystem(entity)) {
    relevant_entities_.erase(entity);
  }
}

void System::OnComponentBeingRemovedFrom(const Entity& entity) {
  if (ShouldBeConsideredBySystem(entity)) {
    relevant_entities_.erase(entity);
  }
}

void System::OnEntityCreated(const Entity& entity) {
  if (ShouldBeConsideredBySystem(entity)) {
    relevant_entities_.erase(entity);
  }
}

void System::OnEntityDestroyed(const Entity& entity) {
  relevant_entities_.erase(entity);
}

const std::unordered_set<Entity>& System::GetRelevantEntities() {
  return relevant_entities_;
}
}
