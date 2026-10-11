module;

//#include <concepts>

export module property:full;

import :getter;
import :setter;

export namespace util
{
  template
  <
    typename owner_class,
    typename value_type,

    getter_method <owner_class, value_type> getter,
    setter_method <owner_class, value_type> setter
  >
  class property
  {
  private:

    owner_class & owner;

  public:

    explicit property(owner_class & owner)
      : owner(owner)
    {}

    operator value_type() const
    {
      return (owner.*getter)();
    }

    property & operator = (const value_type & value)
    {
      (owner.*setter)(value);
      return *this;
    }

    template <typename some_type>
    requires requires(value_type a, const some_type & b) { { a += b }; }

    property & operator += (const some_type & value)
    {
      (owner.*setter)((owner.*getter)() + value);
      return *this;
    }

    template <typename some_type>
    requires requires(value_type a, const some_type & b) { { a -= b }; }

    property & operator -= (const some_type & value)
    {
      (owner.*setter)((owner.*getter)() - value);
      return *this;
    }

    template <typename some_type>
    requires requires(value_type a, const some_type & b) { { a *= b }; }

    property & operator *= (const some_type & value)
    {
      (owner.*setter)((owner.*getter)() * value);
      return *this;
    }

    template <typename some_type>
    requires requires(value_type a, const some_type & b) { { a /= b }; }

    property & operator /= (const some_type & value)
    {
      (owner.*setter)((owner.*getter)() / value);
      return *this;
    }
  };
}
