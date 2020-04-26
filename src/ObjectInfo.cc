// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/ObjectInfo.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <cinder/app/App.h>

namespace mylibrary {

ObjectInfo::ObjectInfo(std::string name, cinder::Color color, cinder::vec3 position, int type) {
  mName = name;
  mColor = color;
  mPosition = position;
  mType = type;

}
ObjectInfo::ObjectInfo() {
  mName = "random object";
  mColor = cinder::Color( 0.34f, 0.78f, 1.0f );
  mPosition = cinder::vec3(0, 5, 0);
  mType = rand() % 2;
}

}  // namespace mylibrary