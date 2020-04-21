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
  x = 5;
  y = 5;
  zoom = 5;
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
  //TODO: Load in a blender object.
  //http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
  ObjLoader loader( loadFile( "/Users/angelaluo/CS-126/cinder_0.9.2_mac/my-projects/final-project-AngelaLuo49021/resources/cube.obj" ) );
  myCubeRef = gl::Batch::create( loader, gl::getStockShader(gl::ShaderDef().color()) );
  //gl::ShaderDef().color()
  myCubeRef->draw();
//  gl::drawSphere( vec3(), 1.0f, 40);
//  gl::drawCube( vec3(), vec3( 2 ) );
}

//TODO: do circle calculations about the point 0, 0 so that the point it moves by will always make it rotate around the object probably create a seperate function to do the calculations like that.
void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP: {
      y = y + kStep;
      break;
    }
    case KeyEvent::KEY_DOWN: {
      y = y - kStep;
      break;
    }
    case KeyEvent::KEY_LEFT: {
      x = x - kStep;
      break;
    }
    case KeyEvent::KEY_RIGHT: {
      x = x + kStep;
      break;
    }

  }
}
void MyApp::mouseWheel(MouseEvent event) {
  float direction = event.getWheelIncrement();
  if (direction > 0) {
    zoom = zoom + kStep;
  } else if (direction < 0) {
    zoom = zoom - kStep;
  }
}

}  // namespace myapp
