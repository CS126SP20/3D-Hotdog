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
int kTypeMustard = 2;
int kTypeRelish = 3;

int kTimeGap = 5;

MyApp::MyApp() { }

void MyApp::setup() {
  //set up gui
  ui::initialize();
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();

  //set Camera position
  horz = 5;
  vert = 5;
  radi = 5;

  //set up background color
  bgR = .765f;
  bgG = .545f;
  bgB = .408f;

  ObjectInfo init_bun("bun", Color( .769f, .545f, 0.349f), vec3( 0.0f , 0.0f , 0.0f), 0);
  ObjectInfo init_sausage("sausage", Color( .769f, 0.345f, .408f ), vec3( 0.0f , 0.0f , 0.0f), 1);
  mObjects.push_back(init_bun);
  mObjects.push_back(init_sausage);
  last_time_ = std::chrono::system_clock::now();
}

void MyApp::update() {
  const auto time = std::chrono::system_clock::now();

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

    ObjectInfo* object = (ObjectInfo*) selection;
    ui::InputText( "Name", &object->mName );
    ui::ColorEdit3( "Color", &object->mColor[0] );
    // getter/setters are a bit longer but still possible
    vec3 pos = object->getPosition();
    if( ui::DragFloat3( "Position", &pos[0] ) ) object->setPosition( pos );
    ui::RadioButton("Bun", &object->mType, 0);
    ui::RadioButton("Sausage", &object->mType, 1);
    ui::RadioButton("Mustard", &object->mType, 2);
    ui::RadioButton("Relish", &object->mType, 3);
  }

  //drop special item
  if (time - last_time_ > std::chrono::seconds(kTimeGap)) {
    last_drop_time_ = std::chrono::system_clock::now();
    last_time_ = time;
    item_dropper_.reset();
    item_dropper_.shouldDrop = true;
  }
  //change positions every couple milliseconds
  if (item_dropper_.shouldDrop && time - last_drop_time_ > std::chrono::milliseconds(kTimeGap)) {
    item_dropper_.dropDown();
    //check location of item relative to the most recent object
    //this allows the player to move their object to other places and still have item drops happen
    if (item_dropper_.position[1] < mObjects[0].getPosition()[1] - 20) {
      item_dropper_.shouldDrop = false;
    }
  }

}

void MyApp::draw() {
  //clear screen
  gl::clear( Color( bgR, bgG, bgB ) );

  //load files (unable to set variables outside of draw)
  cinder::ObjLoader sausage(loadFile(kSausage));
  cinder::ObjLoader bun(loadFile(kBun));
  cinder::ObjLoader mustard(loadFile(kMustard));
  cinder::ObjLoader relish(loadFile(kRelish));


  //set up camera position
  CameraPersp cam;
  cam.lookAt( vec3(radi, vert, horz), vec3( 0, 0, 0 ) );
  gl::setMatrices( cam );

  //set up shading
  auto lambert = gl::ShaderDef().lambert().color();
  auto shader = gl::getStockShader( lambert );
  shader->bind();


  // render all ingredients
  gl::ScopedBlendAlpha alphaBlending;
  for( auto object : mObjects ) {
    gl::color( object.mColor );
    gl::translate(object.getPosition());
    if (object.mType == kTypeSausage) {
      gl::Batch::create(sausage, shader)->draw();
    } else if (object.mType == kTypeBun) {
      gl::Batch::create(bun, shader)->draw();
    } else if (object.mType == kTypeMustard) {
      gl::Batch::create(mustard, shader)->draw();
    } else if (object.mType == kTypeRelish) {
      gl::Batch::create(relish, shader)->draw();
    }
  }

  //draw special item if needed
  if (item_dropper_.shouldDrop) {
    drawDropDown();
  }

}
void MyApp::drawDropDown() {
  auto lambert = gl::ShaderDef().lambert().color();
  auto shader = gl::getStockShader( lambert );
  shader->bind();

  cinder::ObjLoader relish(loadFile(kRelish));
  gl::color(Color( .769f, .545f, 0.349f));
  gl::translate(item_dropper_.position);
  gl::Batch::create(relish, shader)->draw();
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP: {
      vert = vert + kStep;
      break;
    }
    case KeyEvent::KEY_DOWN: {
      vert = vert - kStep;
      break;
    }
    case KeyEvent::KEY_LEFT: {
      horz = horz - kStep;
      break;
    }
    case KeyEvent::KEY_RIGHT: {
      horz = horz + kStep;
      break;
    }

  }
}
void MyApp::mouseWheel(MouseEvent event) {
  float direction = event.getWheelIncrement();
  if (direction > 0) {
    radi = radi + kStep;
  } else if (direction < 0) {
    radi = radi - kStep;
  }
}

void MyApp::mouseDown(MouseEvent event) {
  bgR = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  bgG = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  bgB = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}
}  // namespace myapp
