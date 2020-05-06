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
    position = cinder::vec3(0, kHeightAbove, 0);
  }
  void ItemDropper::dropDown() {
    position[1] = position[1] - 1;
  }
  void ItemDropper::reset() {
    position = cinder::vec3(0, kHeightAbove, 0);
  }
  bool ItemDropper::madeCollision(cinder::vec3 hotdog_pos) {
    //range of about 10 for the length of hotdog
    if (abs(position[2] - hotdog_pos[2]) < kHotDogLength/2) {
      if (abs(position[1] - hotdog_pos[1]) < 4) {
        return true;
      }
    }
    return false;
  }
  }
