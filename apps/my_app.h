// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

#include <glm/vec2.hpp>

namespace myapp {

struct Object {

  cinder::vec3 getPosition() const { return mPosition; }
  void setPosition( const ci::vec3 & position ) { mPosition = position; }

  std::string	mName;
  cinder::Color	mColor;
  cinder::vec3	mPosition;
  float	mSize;
  int mType;

};

class MyApp : public cinder::app::App {
 public:
  float kStep = 1;
  std::string kHotDog = "/Users/angelaluo/CS-126/cinder_0.9.2_mac/my-projects/final-project-AngelaLuo49021/resources/hotdog.obj";
  std::string kSausage = "/Users/angelaluo/CS-126/cinder_0.9.2_mac/my-projects/final-project-AngelaLuo49021/resources/sausage.obj";
  std::string kBun = "/Users/angelaluo/CS-126/cinder_0.9.2_mac/my-projects/final-project-AngelaLuo49021/resources/bun.obj";
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseWheel(cinder::app::MouseEvent) override;

 private:
  float x, y, zoom;
  std::vector<Object>mObjects;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
