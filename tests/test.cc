// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <mylibrary/ObjectInfo.h>
#include <mylibrary/ItemDropper.h>

#include <catch2/catch.hpp>

TEST_CASE("ObjectInfo updates location correctly", "[object-info]") {
  mylibrary::ObjectInfo object_info;
  cinder::vec3 new_position (2, 3, 1);
  object_info.setPosition(new_position);
  REQUIRE(object_info.getPosition() == new_position);
}
TEST_CASE("ObjectInfo constructor stores information correctly", "[object-info][color][name]") {
  mylibrary::ObjectInfo object_info("cool name", cinder::Color( .5f, .5f, 0.5f), cinder::vec3( 0.0f , 0.0f , 0.0f), 0);
  cinder::Color expected_color( .5f, .5f, 0.5f);
  REQUIRE(object_info.mName == "cool name");
  REQUIRE(object_info.mColor== expected_color);
}
TEST_CASE("Item Dropper moves object down", "[item-dropper]") {
  mylibrary::ItemDropper item_dropper;
  item_dropper.dropDown();
  REQUIRE(item_dropper.position[1] == 19);
}
TEST_CASE("Item Dropper resets position", "[item-dropper]") {
  mylibrary::ItemDropper item_dropper;
  item_dropper.dropDown();
  item_dropper.dropDown();
  item_dropper.dropDown();
  item_dropper.reset();
  REQUIRE(item_dropper.position[1] == 20);
}