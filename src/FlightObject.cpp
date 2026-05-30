#include "FlightObject.h"
#include <GL/glew.h>
#include <cmath>

FlightObject::FlightObject(float x, float y, float z, float pitch, float yaw, float roll, const Mesh& mesh, int fragmentID)
:model(mesh), fragmentID(fragmentID) 
{
    transform.x = x;
    transform.y = y;
    transform.z = z;
    transform.pitch = pitch;
    transform.yaw = yaw;
    transform.roll = roll;
}

void FlightObject::draw(unsigned int modelLoc, unsigned int objectTypeLoc) const 
{
    float Cy = cosf(transform.yaw), Sy = sinf(transform.yaw);
    float Cp = cosf(transform.pitch), Sp = sinf(transform.pitch);
    float Cr = cosf(transform.roll), Sr = sinf(transform.roll);

    float mat[16] = {
        Cy*Cr+Sy*Sp*Sr,   Cp*Sr,        -Sy*Cr+Cy*Sp*Sr,  0,
        -Cy*Sr+Sy*Sp*Cr,  Cp*Cr,        Sy*Sr+Cy*Sp*Cr,   0,
        Sy*Cp,            -Sp,          Cy*Cp,            0,
        transform.x,      transform.y,  transform.z,      1
    };

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, mat);
    glUniform1i(objectTypeLoc, fragmentID);
    model.draw();
}

Transform FlightObject::get_transform()
{
    return transform;
}