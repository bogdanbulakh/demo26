export module property:item;

import :getter;
import :setter;

export namespace util
{
  template
  <
    typename owner_class,
    typename value_type,
    typename index_type,
    index_type index_value,

    indexed_getter_method <owner_class, value_type, index_type> getter,
    indexed_setter_method <owner_class, value_type, index_type> setter
  >
  class indexed_item_property
  {
  private:

    owner_class & owner;

  public:

    explicit indexed_item_property(owner_class & owner)
      : owner(owner)
    {}

    operator value_type() const
    {
      return (owner.*getter)(index_value);
    }

    indexed_item_property & operator = (const value_type & value)
    {
      (owner.*setter)(index_value, value);
      return *this;
    }

    template <typename some_type>
    requires requires(value_type a, const some_type & b) { { a += b }; }

    indexed_item_property & operator += (const some_type & value)
    {
      (owner.*setter)(index_value, (owner.*getter)(index_value) + value);
      return *this;
    }

    template <typename some_type>
    requires requires(value_type a, const some_type & b) { { a -= b }; }

    indexed_item_property & operator -= (const some_type & value)
    {
      (owner.*setter)(index_value, (owner.*getter)(index_value) - value);
      return *this;
    }

    template <typename some_type>
    requires requires(value_type a, const some_type & b) { { a *= b }; }

    indexed_item_property & operator *= (const some_type & value)
    {
      (owner.*setter)(index_value, (owner.*getter)(index_value) * value);
      return *this;
    }

    template <typename some_type>
    requires requires(value_type a, const some_type & b) { { a /= b }; }

    indexed_item_property & operator /= (const some_type & value)
    {
      (owner.*setter)(index_value, (owner.*getter)(index_value) / value);
      return *this;
    }
  };
}
