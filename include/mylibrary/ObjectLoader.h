// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <vector>
namespace mylibrary {
//based on this tutorial:
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

  class ObjectLoader {
   public:
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    //outputs
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;

    //prolly shouldn't be a string, fix later
    std::string filename;
    ObjectLoader(std::string filepath);
    bool readFile();
    void processData();



  };

}  // namespace objectloader


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
