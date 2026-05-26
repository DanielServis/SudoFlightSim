#include <iostream>
#include "../FObject.h"

#include "Airports.h"

Runway::Runway(float x, float y, float z, float pitch, float yaw, float roll)
    : FObject(x, y, z, pitch, yaw, roll, createMesh(), 2) {}

Runway::~Runway() {}

Mesh Runway::createMesh() 
{
    Mesh mesh;

    mesh.vertices = {
        -30.0f,  0.0f,  1000.0f,
        30.0f,  0.0f,  1000.0f,
        30.0f,  0.02f,  1000.0f,
        -30.0f,  0.02f,  1000.0f,

        -30.0f, 0.0f, -1000.0f,
        30.0f, 0.0f, -1000.0f,
        30.0f,  0.02f, -1000.0f,
        -30.0f,  0.02f, -1000.0f,
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