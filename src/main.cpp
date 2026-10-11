import enums;
import vector;
import std;

int main()
{
  math::vector<float, 3, util::range_checking_mode::enabled, util::caching_mode::enabled> v;
  v.x = 1;
  v.components[math::y_idx] = 2;
  v[math::z_idx] = 3;

  std::cout << "v.magnitude = " << v.magnitude << "\n";
  std::cout << "v.magnitude_squared = " << v.magnitude_squared << "\n";
}
