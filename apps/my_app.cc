// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/app/Window.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/app/Window.h"
#include "cinder/gl/gl.h"
#include "cinder/ObjLoader.h"

namespace myapp {
using namespace ci;
using namespace ci::app;

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  x = 3;
  y = 3;
  zoom = 3;
}

void MyApp::update() { }

void MyApp::draw() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  gl::clear();
  CameraPersp cam;
  cam.lookAt( vec3( x, y, zoom), vec3( 0 ) );
  gl::setMatrices( cam );

  auto lambert = gl::ShaderDef().lambert();
  auto shader = gl::getStockShader( lambert );
  shader->bind();

  cinder::gl::BatchRef myCubeRef;
  ObjLoader loader( loadFile( "/Users/angelaluo/CS-126/cinder_0.9.2_mac/my-projects/final-project-AngelaLuo49021/apps/Donut.obj" ) );
  myCubeRef = gl::Batch::create( loader, gl::getStockShader( gl::ShaderDef().color() ) );
  myCubeRef->draw();
//  gl::drawSphere( vec3(), 1.0f, 40);
//  gl::drawCube( vec3(), vec3( 2 ) );
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_k:
    case KeyEvent::KEY_w: {
      zoom = zoom + 1;
      break;
    }
    case KeyEvent::KEY_DOWN: {
      zoom = zoom - 1;
      break;
    }
  }
}
void MyApp::mouseWheel(MouseEvent event) {
  float direction = event.getWheelIncrement();
  if (direction > 0) {
    zoom = zoom + 1;
  } else if (direction < 0) {
    zoom = zoom - 1;
  }
  std::cout << zoom;
  std::cout << "\n";
}

}  // namespace myapp
