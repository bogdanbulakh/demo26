module vector;

import std;

namespace geom
{
  vector::vector(const coords_t & coords)
    : coords(coords),
      magnitude_cached(vector::calc_magnitude(coords))
  {}

  double vector::magnitude() const
  {
    return magnitude_cached;
  }

  double vector::calc_magnitude(const coords_t & coords)
  {
    double accum = .0;
    for (std::size_t i = 0; i < dimension_size; ++i)
    {
      accum += coords[i] * coords[i];
    }
    return std::sqrt(accum);
  }

  auto vector::operator[](std::size_t coord_idx) const
    -> const double &
  {
    return coords[coord_idx];
  }

  auto vector::operator[](std::size_t coord_idx)
    -> coords_setter
  {
    return coords_setter {
      .target_vector = *this,
      .target_coord_idx = coord_idx
    };
  }

  vector::coords_setter::operator double() const
  {
    return target_vector.coords[target_coord_idx];
  }

  auto vector::coords_setter::operator= (double val)
    -> coords_setter &
  {
    if (!no_assignment(val))
    {
      target_vector.coords[target_coord_idx] = val;
      post_assignment();
    }
    return *this;
  }

  auto vector::coords_setter::operator+= (double val)
    -> coords_setter &
  {
    return operator=(
      target_vector.coords[target_coord_idx] + val);
  }

  auto vector::coords_setter::operator*= (double val)
    -> coords_setter &
  {
    return operator=(
      target_vector.coords[target_coord_idx] * val);
  }

  bool vector::coords_setter::no_assignment(double val)
  {
    return target_vector.coords[target_coord_idx] == val;
  }

  void vector::coords_setter::post_assignment()
  {
    target_vector.magnitude_cached =
      vector::calc_magnitude(target_vector.coords);
  }
}