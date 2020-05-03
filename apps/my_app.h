// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/ObjLoader.h>
#include <cinder/app/App.h>
#include <mylibrary/ObjectInfo.h>
#include "cinder/gl/gl.h"

#include <glm/vec2.hpp>

#include "cinder/ObjLoader.h"

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  float kStep = 1;
  std::string kHotDog = "/Users/angelaluo/CS-126/cinder_0.9.2_mac/my-projects/final-project-AngelaLuo49021/resources/hotdog.obj";
  std::string kSausage = "/Users/angelaluo/CS-126/cinder_0.9.2_mac/my-projects/final-project-AngelaLuo49021/resources/sausage.obj";
  std::string kBun = "/Users/angelaluo/CS-126/cinder_0.9.2_mac/my-projects/final-project-AngelaLuo49021/resources/bun.obj";
  std::string kMustard = "/Users/angelaluo/CS-126/cinder_0.9.2_mac/my-projects/final-project-AngelaLuo49021/resources/mustard.obj";
  std::string kRelish = "/Users/angelaluo/CS-126/cinder_0.9.2_mac/my-projects/final-project-AngelaLuo49021/resources/relish.obj";
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseWheel(cinder::app::MouseEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;

 private:
  float horz, vert, radi;
  std::vector<mylibrary::ObjectInfo>mObjects;
  cinder::vec2 perspective;
  float bgR, bgG, bgB;
  std::chrono::time_point<std::chrono::system_clock> last_time_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
