#include "Simulation.hpp"

#include "physics/Shape.hpp"

void Simulation::Run() {
    physics.AddBody(Box{5, 5}, Vec2{10, 10}, 100);
}