#include <catch2/catch_test_macros.hpp>

import vector;

TEST_CASE ("Default vector is zero vector", "[geom::vector]") {
  const geom::vector v{};

  REQUIRE (v[geom::coord_x] == .0);
  REQUIRE (v[geom::coord_y] == .0);
  REQUIRE (v[geom::coord_z] == .0);
  REQUIRE (v.magnitude() == .0);
}

TEST_CASE ("Vector magnitude formula", "[geom::vector]") {
  geom::coords_t coords{3., 4., 0.};

  REQUIRE (geom::vector::calc_magnitude(coords) == 5.);
}

TEST_CASE ("Vector magnitude calculation", "[geom::vector]") {
  geom::vector v{geom::coords_t{3., 4., 0.}};

  REQUIRE (v.magnitude() == 5.);
}

TEST_CASE ("Vector magnitude re-calculation", "[geom::vector]") {
  geom::vector v{geom::coords_t{3., 4., 0.}};

  v[geom::coord_x] *= 2.;
  v[geom::coord_y] = 8.;

  REQUIRE (v.magnitude() == 10.);
}

TEST_CASE ("Range check for index", "[geom::vector]") {
  geom::vector v{};

  REQUIRE_THROWS (v[-1] == 0.);
  REQUIRE_THROWS (v[-1] += 1.);

  REQUIRE_THROWS ([&v]()
  {
    auto v_coord = v[geom::coord_z + 1];
    v_coord = 0.;
  }());
}

TEST_CASE ("Range check for index #2", "[geom::vector][!shouldfail]") {
  geom::vector v{};

  auto v_coord = v[geom::coord_z + 1];
  v_coord *= 0.;
}

SCENARIO ("Vector's magnitude follows coordinates' changes", "[geom::vector]")
{
  GIVEN ("A zero-length vector with zero coordinates")
  {
    geom::vector v{};

    REQUIRE (v[geom::coord_x] == 0.);
    REQUIRE (v[geom::coord_y] == 0.);
    REQUIRE (v[geom::coord_z] == 0.);
    REQUIRE (v.magnitude() == 0.);

    WHEN ("Coordinates assigned")
    {
      v[geom::coord_x] = 3.;
      v[geom::coord_y] = 4.;

      REQUIRE (v[geom::coord_x] == 3.);
      REQUIRE (v[geom::coord_y] == 4.);
      REQUIRE (v[geom::coord_z] == 0.);

      THEN ("Magnitude gets updated accordingly")
      {
        REQUIRE (v.magnitude() == 5.);
      }
    }

    WHEN ("Coordinates modified")
    {
      v[geom::coord_x] += 6.;
      v[geom::coord_y] = 8.;

      REQUIRE (v[geom::coord_x] == 6.);
      REQUIRE (v[geom::coord_y] == 8.);
      REQUIRE (v[geom::coord_z] == 0.);

      THEN ("Magnitude gets updated accordingly")
      {
        REQUIRE (v.magnitude() == 10.);
      }
    }
  }

  GIVEN ("An non-empty vector")
  {
    geom::vector v{geom::coords_t{0., 4., 3.}};

    REQUIRE (v[geom::coord_x] == 0.);
    REQUIRE (v[geom::coord_y] == 4.);
    REQUIRE (v[geom::coord_z] == 3.);
    REQUIRE (v.magnitude() == 5.);

    WHEN ("Coordinates modified")
    {
      v[geom::coord_y] += 4.;
      v[geom::coord_z] *= -2.;

      REQUIRE (v[geom::coord_x] == 0.);
      REQUIRE (v[geom::coord_y] == 8.);
      REQUIRE (v[geom::coord_z] == -6.);

      THEN ("Magnitude gets updated accordingly")
      {
        REQUIRE (v.magnitude() == 10.);
      }
    }
  }
}