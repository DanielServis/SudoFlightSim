#include "FObject.h"
#include <GL/glew.h>
#include <cmath>

FObject::FObject(float x, float y, float z, float pitch, float yaw, float roll, const Mesh& mesh, int fragmentID)
: x(x), y(y), z(z), pitch(pitch), yaw(yaw), roll(roll), model(mesh), fragmentID(fragmentID) {}

void FObject::draw(unsigned int modelLoc, unsigned int objectTypeLoc) const 
{
    float Cy = cosf(yaw),   Sy = sinf(yaw);
    float Cp = cosf(pitch), Sp = sinf(pitch);
    float Cr = cosf(roll),  Sr = sinf(roll);

    float mat[16] = {
        Cy*Cr+Sy*Sp*Sr,  Cp*Sr,  -Sy*Cr+Cy*Sp*Sr,  0,
       -Cy*Sr+Sy*Sp*Cr,  Cp*Cr,   Sy*Sr+Cy*Sp*Cr,  0,
        Sy*Cp,          -Sp,       Cy*Cp,            0,
        x,               y,        z,                1
    };

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, mat);
    glUniform1i(objectTypeLoc, fragmentID);
    model.draw();
}