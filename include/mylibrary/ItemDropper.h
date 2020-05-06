//
// Created by Angela Luo on 5/2/20.
//

#ifndef FINALPROJECT_INCLUDE_ITEMDROPPER_H_
#define FINALPROJECT_INCLUDE_ITEMDROPPER_H_

#endif  // FINALPROJECT_INCLUDE_ITEMDROPPER_H_

#include <cinder/app/App.h>

#include <cstdio>
namespace mylibrary {
class ItemDropper {
 public:
  bool shouldDrop;
  cinder::vec3 position;

  ItemDropper();
  // lets the item fall
  void dropDown();
  // resets coordinates to the top
  void reset();
  // checks for collision with rest of hotdog
  bool madeCollision(cinder::vec3 hotdog_pos);

 private:
  int kHotDogLength = 14;
  int kHeightAbove = 20;
};
}  // namespace mylibrary