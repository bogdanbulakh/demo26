import vector;
import std;

int main()
{
  geom::vector v{};
  v[geom::coord_x] = 1.;
  v[geom::coord_y] = 1.;
  std::cout << "v.magnitude() = " << v.magnitude() << "\n";
}
