#pragma once
#include <vector>

#ifndef MODELS_H
    #define MODELS_H

    struct Mesh
    {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
    };

    class Model
    {
        public:
            Model(const Mesh& mesh);
            ~Model();
            void draw() const;

            Model(const Model&) = delete;
            Model& operator=(const Model&) = delete;
            Model(Model&&) = default;
            Model& operator=(Model&&) = default;

        private:
            unsigned int VAO, VBO, EBO;
            int indexCount;
    };

#endif