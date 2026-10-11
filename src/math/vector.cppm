export module vector;

import std;
import property;
import enums;

export namespace math
{
  constexpr std::size_t x_idx = 0;
  constexpr std::size_t y_idx = 1;
  constexpr std::size_t z_idx = 2;

  template
  <
    typename value_type,
    std::size_t dimension_size,
    util::range_checking_mode range_checking = util::range_checking_mode::disabled,
    util::caching_mode magnitude_caching = util::caching_mode::disabled
  >
  class vector
  {
  private:

    std::array<value_type, dimension_size> components_array;

    static constexpr std::size_t magnitude_idx = 0;
    static constexpr std::size_t magnitude_squared_idx = 1;
    static constexpr std::size_t magnitudes_count = 2;

    [[no_unique_address]] mutable std::conditional_t
    <
      (magnitude_caching == util::caching_mode::enabled),
      std::array<value_type, magnitudes_count>,
      std::monostate
    >
    magnitude_cached;

    [[no_unique_address]] mutable std::conditional_t
    <
      (magnitude_caching == util::caching_mode::enabled),
      std::bitset<magnitudes_count>,
      std::monostate
    >
    magnitude_dirty;

    auto get_magnitude() const -> value_type;
    auto get_magnitude_squared() const -> value_type;
    auto get_component(std::size_t index) const -> value_type;
    void set_component(std::size_t index, const value_type & value);

    void throw_if_index_out_of_range(std::size_t index) const
      requires(range_checking == util::range_checking_mode::enabled);

  public:

    template <util::getter_method <vector, value_type> getter>
    using readonly_property =
      util::readonly_property<vector, value_type, getter>;

    template
    <
      util::indexed_getter_method<vector, value_type, std::size_t> getter,
      util::indexed_setter_method<vector, value_type, std::size_t> setter
    >
    using indexed_property =
      util::indexed_property<vector, value_type, std::size_t, getter, setter>;


    template <std::size_t component_index>
    using component_property = std::conditional_t
    <
      (dimension_size > component_index),
      util::indexed_item_property
      <
        vector, value_type, std::size_t, component_index,
        & vector::get_component,
        & vector::set_component
      >,
      std::monostate
    >;

    readonly_property<& vector::get_magnitude> magnitude;
    readonly_property<& vector::get_magnitude_squared> magnitude_squared;
    indexed_property<& vector::get_component, & vector::set_component> components;

    [[no_unique_address]] component_property<x_idx> x;
    [[no_unique_address]] component_property<y_idx> y;
    [[no_unique_address]] component_property<z_idx> z;

    vector(const std::array<value_type, dimension_size> & orig_components = {});

    auto operator [] (std::size_t index) { return components[index]; }

    [[nodiscard]] static value_type
    calc_magnitude(const std::array<value_type, dimension_size> & components);

    [[nodiscard]] static value_type
    calc_magnitude(const std::array<value_type, dimension_size> & components,
      value_type & magnitude_squared);

    [[nodiscard]] static value_type
    calc_magnitude_squared(const std::array<value_type, dimension_size> & components);
  };
}

#include "vector.inl"
