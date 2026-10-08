#include "figure.hpp"
#include <algorithm>
#include <cstddef>
#include <istream>
#include <stdexcept>
#include <string>

namespace
{
  static long long parseInteger(const std::string& token)
  {
    std::size_t position = 0;
    const long long value = std::stoll(token, &position);
    if (position != token.size())
    {
      throw std::invalid_argument("Invalid figure parameter");
    }
    return value;
  }

  static long long readInteger(std::istream& input)
  {
    std::string token{};
    if (!(input >> token))
    {
      throw std::invalid_argument("Cannot read a complete figure");
    }
    return parseInteger(token);
  }
}

std::vector< matveev::figure_t > matveev::readFigures(std::istream& input)
{
  std::vector< figure_t > figures{};
  std::string token{};
  while (input >> token)
  {
    const long long first = parseInteger(token);
    readInteger(input);
    const long long x = readInteger(input);
    const long long y = readInteger(input);
    if (first <= 0)
    {
      throw std::invalid_argument("The radius must be positive");
    }
    const long double horizontal = static_cast< long double >(first);
    const long double vertical = horizontal;
    figures.push_back({horizontal, vertical, static_cast< long double >(x), static_cast< long double >(y)});
  }
  if (input.bad() || !input.eof())
  {
    throw std::runtime_error("Failed to read figures");
  }
  return figures;
}

bool matveev::isInside(const figure_t& figure, const long double x, const long double y)
{
  const long double dx = (x - figure.centerX) / figure.horizontalRadius;
  const long double dy = (y - figure.centerY) / figure.verticalRadius;
  constexpr long double unitRadiusSquared = 1.0L;
  return ((dx * dx) + (dy * dy)) <= unitRadiusSquared;
}

matveev::bounds_t matveev::findBounds(const std::vector< figure_t >& figures)
{
  if (figures.empty())
  {
    throw std::invalid_argument("Cannot find bounds of an empty set of figures");
  }
  const figure_t& first = figures.front();
  bounds_t bounds{first.centerX - first.horizontalRadius, first.centerX + first.horizontalRadius,
      first.centerY - first.verticalRadius, first.centerY + first.verticalRadius};
  for (const figure_t& figure: figures)
  {
    bounds.minX = std::min(bounds.minX, figure.centerX - figure.horizontalRadius);
    bounds.maxX = std::max(bounds.maxX, figure.centerX + figure.horizontalRadius);
    bounds.minY = std::min(bounds.minY, figure.centerY - figure.verticalRadius);
    bounds.maxY = std::max(bounds.maxY, figure.centerY + figure.verticalRadius);
  }
  return bounds;
}
