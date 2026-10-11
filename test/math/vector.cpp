#include <catch2/catch_test_macros.hpp>

import enums;
import vector;

SCENARIO ("Testing non-cached magnitude")
{
  GIVEN ("A zero-length vector with zero coordinates")
  {
    math::vector<float, 3> v{};

    REQUIRE (v[math::x_idx] == 0.);
    REQUIRE (v.components[math::y_idx] == 0.);
    REQUIRE (v.z == 0.);

    REQUIRE (v.magnitude == 0.);
    REQUIRE (v.magnitude_squared == 0.);

    WHEN ("Coordinates assigned")
    {
      v.components[math::x_idx] += 3.f;
      v.y = v.x + 1.;
      v.z *= 1;

      REQUIRE (v.x == 3.);
      REQUIRE (v.y == 4.);
      REQUIRE (v.z == 0.);

      THEN ("Magnitude gets updated accordingly")
      {
        REQUIRE (v.magnitude_squared == 25.);
        REQUIRE (v.magnitude == 5.);
      }
    }
  }
}

SCENARIO ("Testing cached magnitude")
{
  GIVEN ("A zero-length vector with zero coordinates")
  {
    math::vector<float, 3,
      util::range_checking_mode::enabled,
      util::caching_mode::enabled> v{};

    REQUIRE (v[math::x_idx] == 0.);
    REQUIRE (v.components[math::y_idx] == 0.);
    REQUIRE (v.z == 0.);

    REQUIRE (v.magnitude == 0.);
    REQUIRE (v.magnitude_squared == 0.);

    WHEN ("Coordinates assigned")
    {
      v.components[math::x_idx] += 3.f;
      v.y = v.x + 1.;
      v.z *= 1;

      REQUIRE (v.x == 3.);
      REQUIRE (v.y == 4.);
      REQUIRE (v.z == 0.);

      THEN ("Magnitude gets updated accordingly")
      {
        REQUIRE (v.magnitude_squared == 25.);
        REQUIRE (v.magnitude == 5.);
      }
    }
    WHEN ("Index out of range")
    {
      THEN ("It must throw")
      {
        REQUIRE_THROWS (v.components[math::z_idx + 1] == 10.);
      }
    }
  }
}
