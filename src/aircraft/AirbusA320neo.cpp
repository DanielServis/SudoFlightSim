#include <iostream>
#include "Planes.h"

#include "AirbusA320neo.h"

AirbusA320neo::AirbusA320neo(float x, float y, float z, float pitch, float yaw, float roll)
: Plane(x, y, z, pitch, yaw, roll, createMesh(), 1) {}

AirbusA320neo::~AirbusA320neo() {}

Mesh AirbusA320neo::createMesh() 
{
    Mesh mesh;

    mesh.vertices = {
        -2.0f, -2.0f,  20.0f,
        2.0f, -2.0f,  20.0f,
        2.0f,  2.0f,  20.0f,
        -2.0f,  2.0f,  20.0f,

        -2.0f, -0.5f, -20.0f,
        2.0f, -0.5f, -20.0f,
        2.0f,  0.5f, -20.0f,
        -2.0f,  0.5f, -20.0f,
    };
    
    mesh.indices = {
        0,1,2, 2,3,0, 
        4,5,6, 6,7,4,  
        0,4,7, 7,3,0,  
        1,5,6, 6,2,1,  
        3,2,6, 6,7,3, 
        0,1,5, 5,4,0  
    };
      
    return mesh;
}
