#include <iostream>
#include "vector.h"

int main()
{
  geometry::vector v;
  v[0] = 1.;
  v[1] = 1.;
  std::cout << "v.length() = " << v.length() << "\n";
}
