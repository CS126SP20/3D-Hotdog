// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/app/Window.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/app/Window.h"
#include "cinder/gl/gl.h"
#include "cinder/ObjLoader.h"
#include "CinderImGui.h"


namespace myapp {
using namespace ci;
using namespace ci::app;
using namespace std;

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  ui::initialize();

  //set Camera position
  x = 5;
  y = 5;
  zoom = 5;

  //initial objects
  mObjects = {
      { "Object0", Color( 0.34f, 0.78f, 1.0f ), vec3( 0 , 0 , 0)},
      { "Object1", Color( 1.0f, 0.0f, 0.36f ), vec3( 20.0f, 100.0f , 40.0f )},
      { "Object2", Color( 0.48f, 0.86f, 0.22f ), vec3( 100.0f, 350.0f , 80.0f )},
      { "Object3", Color( 1.0f, 0.53f, 0.0f ), vec3( 450.0f, 100.0f , 130.0f )}
  };
}

void MyApp::update() {


  // Our List / Object selector
  static const Object* selection = &mObjects[1];
  {
    ui::ScopedWindow window( "Ingredients" );

    // add / remove buttons
    if( ui::Button( "Add" ) ) {
      static int objCount = mObjects.size();
      mObjects.push_back( { "Object" + std::to_string( objCount++ ), Color::white(), vec3( 0.0f ) } );
      selection = &mObjects.back();
    }
    if( selection ) {
      ui::SameLine();
      if( ui::Button( "Remove" ) ) {
        auto it = std::find_if( mObjects.begin(), mObjects.end(), [] ( const Object& obj ) { return &obj == selection; } );
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
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  static float gray = 0.65f;
  gl::clear( ColorA::gray( gray ) );
  CameraPersp cam;
  cam.lookAt( vec3( x, y, zoom), vec3( 0 ) );
  gl::setMatrices( cam );

  gl::color(Color( 0.34f, 0.78f, 1.0f ));
  auto lambert = gl::ShaderDef().lambert().color();
  auto shader = gl::getStockShader( lambert );
  shader->bind();
  //translate gives the position of the hotdog
  //Some syntax derived from:
  //https://mottosso.gitbooks.io/cinder/book/cinder/gl/Batch.html
  gl::translate(vec3(0, 0, 0));
  cinder::gl::BatchRef myCubeRef;
  ObjLoader loader( loadFile( kHotDog) );
  myCubeRef = gl::Batch::create( loader, shader);
  gl::color(Color( 0.34f, 0.78f, 1.0f ));
  myCubeRef->draw();

//  static float gray = 0.65f;
//  gl::clear( ColorA::gray( gray ) );

  // any widget added without a window will be added
  // in the default "debug" window
//  ui::DragFloat( "Gray", &gray, 0.01f, 0.0f, 1.0f );
  // render our "objects"
  gl::ScopedBlendAlpha alphaBlending;
  for( auto object : mObjects ) {
    gl::color( object.mColor );
    gl::drawSphere( object.getPosition(), object.mSize, 40 );
//    gl::drawSolidCircle( object.getPosition(), object.mSize );
//    gl::drawStringCentered( object.mName, vec2( ivec2( object.getPosition() ) ) - vec2( 0, 5 ), ColorA::black() );
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
