#include "Simulation.hpp"

#include "physics/Shape.hpp"

void Simulation::Run() {
    physics.AddShape(Circle{5});
}