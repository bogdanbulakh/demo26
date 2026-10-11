export module property:setter;

export namespace util
{
  template
  <
    typename owner_class,
    typename value_type
  >
  using setter_method = void(owner_class::*)(const value_type &);

  template
  <
    typename owner_class,
    typename value_type,
    typename index_type
  >
  using indexed_setter_method = void(owner_class::*)(index_type, const value_type &);
}
