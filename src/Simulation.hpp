#pragma once

#include "physics/Physics.hpp"

class Simulation {
public:
    void Run();
private:
    Physics physics;
};