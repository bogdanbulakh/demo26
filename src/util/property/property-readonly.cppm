export module property:readonly;

import :getter;

export namespace util
{
  template
  <
    typename owner_class,
    typename value_type,

    getter_method <owner_class, value_type> getter
  >
  class readonly_property
  {
  private:

    const owner_class & owner;

  public:

    explicit readonly_property(const owner_class & owner)
      : owner(owner)
    {}

    operator value_type() const
    {
      return (owner.*getter)();
    }

    void operator = (const value_type &) = delete;
  };
}