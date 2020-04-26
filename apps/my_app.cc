// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/app/Window.h>
#include <mylibrary/ObjectInfo.h>

#include "CinderImGui.h"
#include "cinder/ObjLoader.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/app/Window.h"
#include "cinder/gl/gl.h"
// TODO:
/**
 *
 * Moving object 0 makes everything move?
 * add better key navigation
 * change colors on hotdog and toppings
 * add option for resizing.
 */

namespace myapp {
using namespace ci;
using namespace ci::app;
using namespace std;

using cinder::app::KeyEvent;
using mylibrary::ObjectInfo;

int kTypeBun = 0;
int kTypeSausage = 1;
int kMustard = 2;
int kRelish = 3;

MyApp::MyApp() { }

void MyApp::setup() {
  //set up gui
  ui::initialize();
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();

  //set Camera position
  x = 5;
  y = 5;
  zoom = 5;

  ObjectInfo bun("bun", Color( .769f, .545f, 0.349f), vec3( 0.0f , 0.0f , 0.0f), 0);
  ObjectInfo sausage("sausage", Color( .769f, 0.345f, .408f ), vec3( 0.0f , 0.0f , 0.0f), 1);
  mObjects.push_back(bun);
  mObjects.push_back(sausage);
}

void MyApp::update() {


  // Our List / Object selector
  static const ObjectInfo* selection = &mObjects[1];
  {
    ui::ScopedWindow window( "Ingredients" );

    // add / remove buttons
    if( ui::Button( "Add" ) ) {
      static int objCount = mObjects.size();
      ObjectInfo new_object;
      mObjects.push_back(new_object);
      selection = &mObjects.back();
    }
    if( selection ) {
      ui::SameLine();
      if( ui::Button( "Remove" ) ) {
        auto it = std::find_if( mObjects.begin(), mObjects.end(), [] ( const ObjectInfo& obj ) { return &obj == selection; } );
        if( it != mObjects.end() ) {
          mObjects.erase( it );
          selection = nullptr;
        }
      }
    }

    // selectable list
    ui::ListBoxHeader( "" );
    int id = 0;
    for( const auto& object : mObjects ) {
      if( ui::Selectable( ( object.mName + "###obj_" + std::to_string( ++id ) ).c_str(), selection == &object ) ) {
        selection = &object;
      }
    }
    ui::ListBoxFooter();
  }

  // The Object Inspector
  if( selection != nullptr ) {
    ui::ScopedWindow window( "Inspector" );

    Object* object = (Object*) selection;
    ui::InputText( "Name", &object->mName );
    ui::ColorEdit3( "Color", &object->mColor[0] );
    // getter/setters are a bit longer but still possible
    vec3 pos = object->getPosition();
    if( ui::DragFloat3( "Position", &pos[0] ) ) object->setPosition( pos );
    ui::DragFloat( "Size", &object->mSize );
  }
}

void MyApp::draw() {

  //clear screen
  static float gray = 0.65f;
  gl::clear( ColorA::gray( gray ) );

  //set up camera position
  CameraPersp cam;
  cam.lookAt( vec3( zoom, y, x), vec3( 0 ) );
  gl::setMatrices( cam );

  gl::color(Color( 0.34f, 0.78f, 1.0f ));
  auto lambert = gl::ShaderDef().lambert().color();
  auto shader = gl::getStockShader( lambert );
  shader->bind();
  ObjLoader loader( loadFile( kHotDog) );
  ObjLoader sausage(loadFile(kSausage));
  ObjLoader bun(loadFile(kBun));

  // render the rest of the ingredients
  gl::ScopedBlendAlpha alphaBlending;
  for( auto object : mObjects ) {
    gl::color( object.mColor );
//    gl::scale(object.mSize/4, object.mSize / 8);
    gl::translate(object.getPosition());
    if (object.mType == kTypeSausage) {
      gl::Batch::create(sausage, shader)->draw();
    } else if (object.mType == kTypeBun) {
      gl::Batch::create(bun, shader)->draw();
    }
  }
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
