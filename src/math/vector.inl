namespace math
{
  template <typename value_type, std::size_t dimension_size,
    util::range_checking_mode range_checking, util::caching_mode magnitude_caching>

  vector<value_type, dimension_size, range_checking, magnitude_caching>::
    vector(const std::array<value_type, dimension_size> & components_array):

    components_array{components_array},
    components{*this},
    magnitude{*this},
    magnitude_squared{*this},

    x { [this]() -> component_property<math::x_idx>
    {
      if constexpr (dimension_size > math::x_idx)
        return component_property <math::x_idx>{*this};
      else
        return std::monostate{};
    }()},

    y { [this]() -> component_property<math::y_idx>
    {
      if constexpr (dimension_size > math::y_idx)
        return component_property <math::y_idx>{*this};
      else
        return std::monostate{};
    }()},

    z { [this]() -> component_property<math::z_idx>
    {
      if constexpr (dimension_size > math::z_idx)
        return component_property <math::z_idx>{*this};
      else
        return std::monostate{};
    }()}
  {
    if constexpr (magnitude_caching == util::caching_mode::enabled)
    {
      magnitude_dirty.set();
    }
  }

  template <typename value_type, std::size_t dimension_size,
    util::range_checking_mode range_checking, util::caching_mode magnitude_caching>

  auto vector<value_type, dimension_size, range_checking, magnitude_caching>::
    calc_magnitude(const std::array<value_type, dimension_size> & components_array,
      value_type & magnitude_squared)
    -> value_type
  {
    magnitude_squared = calc_magnitude_squared(components_array);
    return std::sqrt(magnitude_squared);
  }

  template <typename value_type, std::size_t dimension_size,
    util::range_checking_mode range_checking, util::caching_mode magnitude_caching>

  auto vector<value_type, dimension_size, range_checking, magnitude_caching>::
    calc_magnitude(const std::array<value_type, dimension_size> & components_array)
    -> value_type
  {
    return std::sqrt(calc_magnitude_squared(components_array));
  }

  template <typename value_type, std::size_t dimension_size,
    util::range_checking_mode range_checking, util::caching_mode magnitude_caching>

  auto vector<value_type, dimension_size, range_checking, magnitude_caching>::
    calc_magnitude_squared(const std::array<value_type, dimension_size> & components_array)
    -> value_type
  {
    return std::transform_reduce(components_array.begin(), components_array.end(),
      value_type{0}, std::plus<value_type>{},
      [](value_type component_value)
      {
        return component_value * component_value;
      }
    );
  }

  template <typename value_type, std::size_t dimension_size,
    util::range_checking_mode range_checking, util::caching_mode magnitude_caching>

  auto vector<value_type, dimension_size, range_checking, magnitude_caching>::
    get_magnitude() const -> value_type
  {
    if constexpr (magnitude_caching == util::caching_mode::enabled)
    {
      if (magnitude_dirty[vector::magnitude_idx])
      {
        magnitude_cached[vector::magnitude_idx] =
          calc_magnitude(components_array,
            magnitude_cached[vector::magnitude_squared_idx]);

        magnitude_dirty.reset();
      }
      return magnitude_cached[vector::magnitude_idx];
    }
    return calc_magnitude(components_array);
  }

  template <typename value_type, std::size_t dimension_size,
    util::range_checking_mode range_checking, util::caching_mode magnitude_caching>

  auto vector<value_type, dimension_size, range_checking, magnitude_caching>::
    get_magnitude_squared() const -> value_type
  {
    if constexpr (magnitude_caching == util::caching_mode::enabled)
    {
      if (magnitude_dirty[vector::magnitude_squared_idx])
      {
        magnitude_cached[vector::magnitude_squared_idx] =
          calc_magnitude_squared(components_array);

        magnitude_dirty.reset(vector::magnitude_squared_idx);
      }
      return magnitude_cached[vector::magnitude_squared_idx];
    }
    return calc_magnitude_squared(components_array);
  }

  template <typename value_type, std::size_t dimension_size,
    util::range_checking_mode range_checking, util::caching_mode magnitude_caching>

  auto vector<value_type, dimension_size, range_checking, magnitude_caching>::
    get_component(std::size_t index) const -> value_type
  {
    if constexpr (range_checking == util::range_checking_mode::enabled)
    {
      throw_if_index_out_of_range(index);
    }
    return components_array[index] ;
  }

  template <typename value_type, std::size_t dimension_size,
    util::range_checking_mode range_checking, util::caching_mode magnitude_caching>

  void vector<value_type, dimension_size, range_checking, magnitude_caching>::
    set_component(std::size_t index, const value_type & value)
  {
    if constexpr (range_checking == util::range_checking_mode::enabled)
    {
      throw_if_index_out_of_range(index);
    }

    components_array[index] = value;

    if constexpr (magnitude_caching == util::caching_mode::enabled)
    {
      magnitude_dirty.set();
    }
  }

  template <typename value_type, std::size_t dimension_size,
    util::range_checking_mode range_checking, util::caching_mode magnitude_caching>

  void vector<value_type, dimension_size, range_checking, magnitude_caching>::
    throw_if_index_out_of_range(std::size_t index) const
      requires(range_checking == util::range_checking_mode::enabled)
  {
    if (index < math::x_idx || index >= dimension_size)
    {
      throw std::out_of_range("Index out of range");
    }
  }
}