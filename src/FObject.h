#pragma once
#include "Models.h"

#ifndef FOBJECT_H
    #define FOBJECT_H

    class FObject
    {
        public:
            void draw(unsigned int modelLoc, unsigned int modelTypeLoc) const;
            virtual ~FObject() = default;
            int fragmentID;

        protected:
            float x, y, z;
            float pitch, yaw, roll;
            Model model;
            FObject(float x, float y, float z, float pitch, float yaw, float roll, const Mesh& mesh, int fragmentID);
    };

#endif