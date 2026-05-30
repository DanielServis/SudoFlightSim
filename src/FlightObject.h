#pragma once
#include "Models.h"

#ifndef FLIGHTOBJECT_H
    #define FLIGHTOBJECT_H

    struct Transform
    {
        float x, y, z;
        float pitch, yaw, roll;
    };

    class FlightObject
    {
        public:
            void draw(unsigned int modelLoc, unsigned int modelTypeLoc) const;
            virtual ~FlightObject() = default;
            int fragmentID;
            Transform get_transform();

        protected:
            Transform transform;
            Model model;
            FlightObject(float x, float y, float z, float pitch, float yaw, float roll, const Mesh& mesh, int fragmentID);
    };

#endif