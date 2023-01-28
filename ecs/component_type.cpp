#include "component_type.h"

ComponentType::ComponentType(int id) : id_(id) {}

ComponentType::operator int() {
  return id_;
}
