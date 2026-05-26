#pragma once
#include <iostream>
#include "../FObject.h"

#ifndef AIRPORTS_H
    #define AIRPORTS_H

    class Runway : public FObject
    {
        private:
            static Mesh createMesh();

        public:
            Runway(float x, float y, float z, float pitch, float yaw, float roll);
            ~Runway();
    };

#endif