//
// Created by Angela Luo on 5/2/20.
//

#ifndef FINALPROJECT_INCLUDE_ITEMDROPPER_H_
#define FINALPROJECT_INCLUDE_ITEMDROPPER_H_

#endif  // FINALPROJECT_INCLUDE_ITEMDROPPER_H_

#include <cinder/app/App.h>
#include <cstdio>

/**
 * Implementation plan:
 * the item will drop, and take in the position of Object 0 as the one it
 * compares itself to If it is within 10 of object 0 in the z direction
 * (horizontal), then it will stop one above the y direction (vertical) in this
 * case, add it to the object list Otherwise, it will disappear if the y
 * (vertical) coordinate is below the object 0 y coordinate dont add it to the
 * object list If it is not, then it will continue to drop down.
 *
 * Track the position of the item dropper
 *  every 5 miliseconds, it will drop 1 block
 */
namespace mylibrary {
class ItemDropper {
 public:
  bool shouldDrop;
  cinder::vec3 position;

  ItemDropper();
  //lets the item fall
  void dropDown();
  //resets coordinates to the top
  void reset();
  //checks for collision with rest of hotdog
  bool madeCollision(cinder::vec3 hotdog_pos);
 private:
  int kHotDogLength = 10;
};
}