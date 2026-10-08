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
  bool isInside(const figure_t& figure, long double x, long double y);
}

#endif
