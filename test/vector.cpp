#include <catch2/catch_test_macros.hpp>
#include "../src/vector.h"

TEST_CASE("vector creation", "[geometry::vector]") {
  const geometry::vector v;

  REQUIRE(v.length() == .0);
}

TEST_CASE("vector length formula", "[geometry::vector]") {
  geometry::vector v;
  v[0] = 3.;
  v[1] = 4.;

  REQUIRE(geometry::vector::get_length(v) == 5.);
}

TEST_CASE("vector length calculation", "[geometry::vector]") {
  geometry::vector v;
  v[0] = 3.;
  v[1] = 4.;

  REQUIRE(v.length() == 5.);
}
