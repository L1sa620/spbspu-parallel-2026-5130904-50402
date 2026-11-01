#include "catalog.hpp"
#include <stdexcept>
#include <cmath>
#include "parse.hpp"

void matveev::Catalog::addShape(const std::string &name, const shape_t &shape)
{
  requireName(name);
  if ((shape.radiusX <= 0) || (shape.radiusY <= 0) || !std::isfinite(shape.angle))
  {
    throw std::invalid_argument("Invalid shape");
  }
  if (!shapes_.emplace(name, shape).second)
  {
    throw std::invalid_argument("Shape already exists");
  }
}

const matveev::shape_t &matveev::Catalog::getShape(const std::string &name) const
{
  return shapes_.at(name);
}
