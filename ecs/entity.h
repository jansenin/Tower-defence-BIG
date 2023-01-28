#pragma once

#include <cstdint>
#include <functional>

#include "component.h"
#include "types.h"

namespace ECS {
class Entity {
  friend std::hash<Entity>;

 public:
  Entity();

  template<typename ComponentType>
  void AddComponent(ComponentType& component);
  template<typename ComponentType>
  void RemoveComponent();
  template<typename ComponentType>
  bool HasComponent() const;
  template<typename ComponentType>
  ComponentType& GetComponent() const;

  void Destroy();

  EntityId GetId() const;

  bool operator==(const Entity& rhs) const;
  bool operator!=(const Entity& rhs) const;
 private:
  const EntityId id_;
};
}

template<>
struct std::hash<ECS::Entity> {
  std::size_t operator()(ECS::Entity const& s) const noexcept {
    return s.id_;
  }
};
