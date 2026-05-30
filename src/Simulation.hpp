#pragma once

#include "physics/Physics.hpp"

class Simulation {
public:
    int Run();
private:
    Physics physics;
};