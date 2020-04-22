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
  x = 5;
  y = 5;
  zoom = 5;

  mObjects = {
      { "Object0", Color( 0.34f, 0.78f, 1.0f ), vec3( 200.0f , 100.0f , 0)},
      { "Object1", Color( 1.0f, 0.0f, 0.36f ), vec3( 20.0f, 100.0f , 40.0f )},
      { "Object2", Color( 0.48f, 0.86f, 0.22f ), vec3( 100.0f, 350.0f , 80.0f )},
      { "Object3", Color( 1.0f, 0.53f, 0.0f ), vec3( 450.0f, 100.0f , 130.0f )}
  };
}

void MyApp::update() {
  static bool showDemoWindow = false;
  static bool showWindowWithMenu = false;

  // a few scoped object like ScopedWindow allow to quickly
  // push and pop states
  if( showWindowWithMenu ) {
    ui::ScopedWindow window( "Window with Menu", ImGuiWindowFlags_MenuBar );

    // setup the window menu bar
    if( ui::BeginMenuBar() ){
      if( ui::BeginMenu( "Edit" ) ){
        ui::MenuItem( "Copy" );
        ui::MenuItem( "Cut" );
        ui::MenuItem( "Paste" );
        ui::EndMenu();
      }
      ui::EndMenuBar();
    }

    // add some text
    ui::Text( "Window Content" );
  }

  // create the main menu bar
  {
    ui::ScopedMainMenuBar menuBar;

    // add a file menu
    if( ui::BeginMenu( "File" ) ){
      ui::MenuItem( "Open" );
      ui::MenuItem( "Save" );
      ui::MenuItem( "Save As" );
      ui::EndMenu();
    }

    // and a view menu
    if( ui::BeginMenu( "View" ) ){
      ui::MenuItem( "TestWindow", nullptr, &showDemoWindow );
      ui::MenuItem( "Window with Menu", nullptr, &showWindowWithMenu );
      ui::EndMenu();
    }
  }

//  if( showDemoWindow ){
//    // have a look at this function for more examples
//    ui::ShowDemoWindow();
//  }


  // Our List / Object selector
  static const Object* selection = &mObjects[1];
  {
    ui::ScopedWindow window( "Objects" );

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
    if( ui::DragFloat2( "Position", &pos[0] ) ) object->setPosition( pos );
    ui::DragFloat( "Size", &object->mSize );
  }
}

void MyApp::draw() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  static float gray = 0.65f;
  gl::clear( ColorA::gray( gray ) );
//  gl::clear();
  CameraPersp cam;
  cam.lookAt( vec3( x, y, zoom), vec3( 0 ) );
  gl::setMatrices( cam );

  auto lambert = gl::ShaderDef().lambert();
  auto shader = gl::getStockShader( lambert );
  shader->bind();
//  //translate gives the position of the hotdog
//  //https://mottosso.gitbooks.io/cinder/book/cinder/gl/Batch.html
//  gl::translate(vec3(0, 0, 0));
  cinder::gl::BatchRef myCubeRef;
//  //TODO: Load in a blender object.
//  //http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
  ObjLoader loader( loadFile( "/Users/angelaluo/CS-126/cinder_0.9.2_mac/my-projects/final-project-AngelaLuo49021/resources/hotdog.obj" ), loadFile( "/Users/angelaluo/CS-126/cinder_0.9.2_mac/my-projects/final-project-AngelaLuo49021/resources/cube.mtl" ) );
  myCubeRef = gl::Batch::create( loader, shader);
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
