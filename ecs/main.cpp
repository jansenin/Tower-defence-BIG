#include <iostream>

#include "ecs_interface.h"

struct HealthComponent : ECS::Component {
  HealthComponent(int health) : health(health) {}
  int health;
};

struct PositionComponent : ECS::Component {
  PositionComponent(int x, int y) : x(x), y(y) {}
  int x;
  int y;
};

struct VelocityComponent : ECS::Component {
  VelocityComponent(int dx, int dy) : dx(dx), dy(dy) {}
  int dx;
  int dy;
};

struct DeathEventComponent : ECS::Component {
  DeathEventComponent() : listeners_(std::vector<std::function<void()>>()){}

  void AddListener(const std::function<void()>& listener) {
    listeners_.push_back(listener);
  }
 private:
  std::vector<std::function<void()>> listeners_;
};

struct MovementSystem : ECS::System {
  bool ShouldBeConsideredBySystem(const ECS::Entity& entity) const override {
    return entity.HasComponent<VelocityComponent>();
  }

  void Tick() override {
    for (const ECS::Entity& entity : GetRelevantEntities()) {
      auto& position_component = entity.GetComponent<PositionComponent>();
      auto& velocity_component = entity.GetComponent<VelocityComponent>();

      position_component.x += velocity_component.dx;
      position_component.y += velocity_component.dy;
    }
  }
};

struct DamageForSpeedSystem : ECS::System {
  bool ShouldBeConsideredBySystem(const ECS::Entity& entity) const override {
    return entity.HasComponent<HealthComponent>() && entity.HasComponent<VelocityComponent>();
  }

  void Tick() override {
    for (const ECS::Entity& entity : GetRelevantEntities()) {
      auto& health_component = entity.GetComponent<HealthComponent>();
      auto& velocity_component = entity.GetComponent<VelocityComponent>();

      health_component.health -= abs(velocity_component.dx) + abs(velocity_component.dy);
    }
  }
};

int main() {
  ECS::AddSystem(*new MovementSystem());
  ECS::AddSystem(*new DamageForSpeedSystem());

  auto* entity_hvp = new ECS::Entity();

  auto* entity_vp = new ECS::Entity();
  auto* entity_hp = new ECS::Entity();
  auto* entity_hv = new ECS::Entity();

  auto* entity_h = new ECS::Entity();
  auto* entity_v = new ECS::Entity();
  auto* entity_p = new ECS::Entity();

  entity_hvp->AddComponent(*new HealthComponent(100));
  entity_hvp->AddComponent(*new VelocityComponent(1, 2));
  entity_hvp->AddComponent(*new PositionComponent(0, 0));

  entity_vp->AddComponent(*new VelocityComponent(3, 4));
  entity_vp->AddComponent(*new PositionComponent(5, 6));

  entity_hp->AddComponent(*new HealthComponent(200));
  entity_hp->AddComponent(*new PositionComponent(7, 8));

  entity_hv->AddComponent(*new HealthComponent(300));
  entity_hv->AddComponent(*new VelocityComponent(9, 10));

  entity_h->AddComponent(*new HealthComponent(400));
  entity_v->AddComponent(*new VelocityComponent(11, 12));
  entity_p->AddComponent(*new PositionComponent(13, 14));

  ECS::Tick();

  return 0;
}
