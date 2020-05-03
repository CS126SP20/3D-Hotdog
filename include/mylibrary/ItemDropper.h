//
// Created by Angela Luo on 5/2/20.
//

#ifndef FINALPROJECT_INCLUDE_ITEMDROPPER_H_
#define FINALPROJECT_INCLUDE_ITEMDROPPER_H_

#endif  // FINALPROJECT_INCLUDE_ITEMDROPPER_H_

#include <cinder/app/App.h>
namespace mylibrary {
class ItemDropper {
 public:
  ItemDropper();
  bool shouldDropItem;

 private:
  cinder::vec3 position;
};
}