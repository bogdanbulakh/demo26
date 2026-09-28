module;

//#include <stdexcept>

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
    throw_if_idx_out_of_range(coord_idx);

    return coords[coord_idx];
  }

  auto vector::operator[](std::size_t coord_idx)
    -> coords_setter
  {
    return coords_setter {*this, coord_idx};

    // works only for aggregate types (no user ctor, all public, no vfunc):
    //
    // return coords_setter {
    //   .target_vector = *this,
    //   .target_coord_idx = coord_idx
    // };
  }

  vector::coords_setter::coords_setter(
    vector & target_vector, std::size_t target_coord_idx)
    : target_vector(target_vector),
      target_coord_idx(target_coord_idx)
  {
    target_vector.throw_if_idx_out_of_range(target_coord_idx);
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

  void vector::throw_if_idx_out_of_range(std::size_t coord_idx) const
  {
    if (coord_idx < geom::coord_x || coord_idx > geom::coord_z)
    {
      throw std::out_of_range("Index out of range");
    }
  }
}