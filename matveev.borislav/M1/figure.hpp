#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <iosfwd>
#include <vector>

namespace matveev
{
  struct figure_t
  {
    long double horizontalRadius;
    long double verticalRadius;
    long double centerX;
    long double centerY;
  };

  std::vector< figure_t > readFigures(std::istream& input);
}

#endif
