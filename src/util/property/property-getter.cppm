export module property:getter;

export namespace util
{
  template
  <
    typename owner_class,
    typename value_type
  >
  using getter_method = value_type(owner_class::*)() const;

  template
  <
    typename owner_class,
    typename value_type,
    typename index_type
  >
  using indexed_getter_method = value_type(owner_class::*)(index_type) const;
}
