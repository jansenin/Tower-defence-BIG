#pragma once

#include <unordered_map>

#include "system.h"
#include "types.h"

namespace ECS {
class ECS {
 public:
  void AddSystem(const System& system);

  EntityId GenerateNewEntityId();

  void Destroy(const Entity& entity);

  void Tick();

  template<typename ComponentType>
  void AddComponent(const Entity& entity, const ComponentType& component);
  template<typename ComponentType>
  void RemoveComponent(const Entity& entity);
  template<typename ComponentType>
  void HasComponent(const Entity& entity);

 private:
  template<typename ComponentType>
  struct EntitiesWithSpecifiedComponentHolder {
    static std::unordered_set<EntityId> entities;
  };

  template<typename ComponentType>
  struct ComponentsOfSpecifiedTypeHolder {
    static std::unordered_map<EntityId, Component> components;
  };

  std::vector<System> systems_;
};

template<typename ComponentType>
void ECS::HasComponent(const Entity& entity) {
  return EntitiesWithSpecifiedComponentHolder<ComponentType>::entities.count(entity.GetId());
}

template<typename ComponentType>
void ECS::RemoveComponent(const Entity& entity) {
  ComponentsOfSpecifiedTypeHolder<ComponentType>::components.erase(entity.GetId());
  EntitiesWithSpecifiedComponentHolder<::ComponentType>::entities.erase(entity.GetId());
}

template<typename ComponentType>
void ECS::AddComponent(const Entity& entity, const ComponentType& component) {
  ComponentsOfSpecifiedTypeHolder<ComponentType>::components.template insert({entity.GetId(), component});
  EntitiesWithSpecifiedComponentHolder<::ComponentType>::entities.insert(entity.GetId());
}

ECS ecs;

void ECS::Tick() {
  for (System& system : systems_) {
    system.Tick();
  }
}

void AddSystem(const System& system) {
  ecs.AddSystem(system);
}

void Tick() {
  ecs.Tick();
}

}
