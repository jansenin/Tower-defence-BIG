#pragma once

#include <unordered_set>

#include "entity.h"

namespace ECS {
class System {
 public:
  void OnComponentBeingAddedTo(const Entity& entity);
  void OnComponentBeingRemovedFrom(const Entity& entity);
  void OnEntityCreated(const Entity& entity);
  void OnEntityDestroyed(const Entity& entity);
  const std::unordered_set<Entity>& GetRelevantEntities();

  virtual bool ShouldBeConsideredBySystem(const Entity& entity) const = 0;
  virtual void Tick() = 0;

 private:
  std::unordered_set<Entity> relevant_entities_;
};
}
