#include "vector.h"
#include <cmath>

geometry::vector::vector()
: length_cached(.0)
{
  for (std::size_t i = 0; i < geometry::dimension_size; ++i)
  {
    coord[i] = .0;
  }
}

double geometry::vector::length() const
{
  return length_cached;
}

double geometry::vector::get_length(const geometry::vector & v)
{
  double accum = .0;
  for (std::size_t i = 0; i < geometry::dimension_size; ++i)
  {
    accum += v.coord[i] * v.coord[i];
  }
  return std::sqrt(accum);
}

const double & geometry::vector::operator[](std::size_t coord_idx) const
{
  return coord[coord_idx];
}

double & geometry::vector::operator[](std::size_t coord_idx)
{
  return const_cast<double &>(
    static_cast<const geometry::vector &>(*this)[coord_idx]);
}
