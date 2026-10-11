export module property:indexed;

import :getter;
import :setter;

export namespace util
{
  template
  <
    typename owner_class,
    typename value_type,
    typename index_type,

    indexed_getter_method <owner_class, value_type, index_type> getter,
    indexed_setter_method <owner_class, value_type, index_type> setter
  >
  class indexed_property
  {
  private:

    owner_class & owner;

    struct property_proxy
    {
      owner_class & owner_ref;
      index_type index;

      operator value_type() const
      {
        return (owner_ref.*getter)(index);
      }

      property_proxy & operator = (const value_type & value)
      {
        (owner_ref.*setter)(index, value);
        return *this;
      }

      template <typename some_type>
      requires requires(value_type a, const some_type & b) { { a += b }; }

      property_proxy & operator += (const some_type & value)
      {
        (owner_ref.*setter)(index, (owner_ref.*getter)(index) + value);
        return *this;
      }

      template <typename some_type>
      requires requires(value_type a, const some_type & b) { { a -= b }; }

      property_proxy & operator -= (const some_type & value)
      {
        (owner_ref.*setter)(index, (owner_ref.*getter)(index) - value);
        return *this;
      }

      template <typename some_type>
      requires requires(value_type a, const some_type & b) { { a *= b }; }

      property_proxy & operator *= (const some_type & value)
      {
        (owner_ref.*setter)(index, (owner_ref.*getter)(index) * value);
        return *this;
      }

      template <typename some_type>
      requires requires(value_type a, const some_type & b) { { a /= b }; }

      property_proxy & operator /= (const some_type & value)
      {
        (owner_ref.*setter)(index, (owner_ref.*getter)(index) / value);
        return *this;
      }
    };

  public:

    explicit indexed_property(owner_class & owner)
      : owner(owner)
    {}

    property_proxy operator [] (index_type index)
    {
      return property_proxy{owner, index};
    }
  };
}
