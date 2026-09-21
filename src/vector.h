#include <cstddef>

namespace geometry
{
  const int dimension_size = 3;

  class vector
  {
  public:
    vector();

    double length() const;

    double & operator[] (std::size_t coord_idx);
    const double & operator[] (std::size_t coord_idx) const;

    static double get_length(const vector & v);

  private:
    double coord[dimension_size];
    double length_cached;
  };
}
