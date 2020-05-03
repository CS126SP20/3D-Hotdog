//
// Created by Angela Luo on 5/2/20.
//
#include <mylibrary/ItemDropper.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <cinder/app/App.h>

namespace mylibrary {
  ItemDropper::ItemDropper() {
    position = cinder::vec3(0, 5, 0);
  }
  void ItemDropper::dropDown() {
    position[1] = position[1] - 1;
  }
}
