#include <iostream>
#include "../FObject.h"

#include "Planes.h"

Plane::Plane(float x, float y, float z, float pitch, float yaw, float roll, const Mesh& mesh, int fragmentID)
: FObject(x, y, z, pitch, yaw, roll, mesh, fragmentID) {}

Plane::~Plane() {}