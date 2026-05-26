#pragma once
#include <iostream>
#include "../FObject.h"

#ifndef PLANES_H
    #define PLANES_H

    class Plane: public FObject
    {
        public:
            Plane(float x, float y, float z, float pitch, float yaw, float roll, const Mesh& mesh, int fragmentID);
            ~Plane();
    };

#endif