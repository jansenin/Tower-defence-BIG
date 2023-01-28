#pragma once

#include <functional>

class ComponentType {
  friend std::hash<ComponentType>;

 public:
  explicit ComponentType(int id);
  explicit operator int();

 private:
  int id_;
};

template<>
struct std::hash<ComponentType> {
  std::size_t operator()(ComponentType const& s) const noexcept {
    return s.id_;
  }
};
