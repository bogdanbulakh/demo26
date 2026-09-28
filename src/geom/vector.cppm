export module vector;

import std;

export namespace geom
{
  const std::size_t dimension_size = 3;
  const std::size_t coord_x = 0;
  const std::size_t coord_y = 1;
  const std::size_t coord_z = 2;
  using coords_t = std::array<double, dimension_size>;

  class vector
  {
  private:
    struct coords_setter;

  public:
    vector(const coords_t & coords = {});

    double magnitude() const;

    auto operator[] (std::size_t coord_idx) -> coords_setter;
    auto operator[] (std::size_t coord_idx) const -> const double &;

    static double calc_magnitude(const coords_t & coords);

  private:
    coords_t coords;
    double magnitude_cached;

    struct coords_setter
    {
      coords_setter(vector & target_vector, std::size_t target_coord_idx);

      operator double() const;
      auto operator= (double val) -> coords_setter &;
      auto operator+= (double val) -> coords_setter &;
      auto operator*= (double val) -> coords_setter &;

    private:
      vector & target_vector;
      std::size_t target_coord_idx;

      bool no_assignment(double val);
      void post_assignment();
    };

    void throw_if_idx_out_of_range(std::size_t coord_idx) const;
  };
}