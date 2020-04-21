// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
namespace objectloader {
 public:
  std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
  std::vector< glm::vec3 > temp_vertices;
  std::vector< glm::vec2 > temp_uvs;
  std::vector< glm::vec3 > temp_normals;

}  // namespace objectloader


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
