// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#import <cinder/Color.h>
#include <cinder/app/App.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <vector>
namespace mylibrary {
struct ObjectInfo {
  ObjectInfo(std::string name, cinder::Color color, cinder::vec3 position,
             int type);
  ObjectInfo();
  std::string mName;
  cinder::Color mColor;
  cinder::vec3 mPosition;
  int mType;
  cinder::vec3 getPosition() const { return mPosition; }
  void setPosition(const ci::vec3& position) { mPosition = position; }
};

}  // namespace mylibrary

#endif  // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
