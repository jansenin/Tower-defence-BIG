cmake_minimum_required(VERSION 3.20)
project(ECS)

set(CMAKE_CXX_STANDARD 17)

add_executable(ECS ecs/main.cpp ecs/component.cpp ecs/system.cpp ecs/component_type.cpp ecs/entity.cpp ecs/ecs.cpp)
