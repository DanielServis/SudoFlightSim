#pragma once
#include <iostream>
#include "Planes.h"

#ifndef AIRBUSA320NEO_H
    #define AIRBUSA320NEO_H

    class AirbusA320neo : public Plane
    {
        private:
            static Mesh createMesh();

        public:
            AirbusA320neo(float x, float y, float z, float pitch, float yaw, float roll);
            ~AirbusA320neo();
    };

#endif