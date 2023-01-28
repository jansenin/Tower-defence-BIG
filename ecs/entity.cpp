#include "entity.h"

#include "ecs.h"

namespace ECS {
Entity::Entity() : id_(ecs.GenerateNewEntityId()) {}

bool Entity::operator==(const Entity& rhs) const {
  return id_ == rhs.id_;
}

bool Entity::operator!=(const Entity& rhs) const {
  return !(rhs == *this);
}

void Entity::Destroy() {
  ecs.Destroy(*this);
}

EntityId Entity::GetId() const {
  return id_;
}
}
