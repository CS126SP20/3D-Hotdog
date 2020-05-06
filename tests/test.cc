// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <mylibrary/ObjectInfo.h>
#include <mylibrary/ItemDropper.h>

#include <catch2/catch.hpp>

TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}
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