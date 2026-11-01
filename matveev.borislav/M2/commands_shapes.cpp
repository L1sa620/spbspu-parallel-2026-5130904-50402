#include "commands.hpp"

bool matveev::executeShape(const Tokens &tokens, Catalog &catalog, std::ostream &out)
{
  constexpr std::size_t nameIndex = 1;
  constexpr std::size_t radiusIndex = 2;
  constexpr std::size_t xIndex = 3;
  constexpr std::size_t yIndex = 4;
  constexpr std::size_t argumentCount2 = 2;
  constexpr std::size_t argumentCount5 = 5;
  if (tokens.front() == "circle")
  {
    requireCount(tokens, argumentCount5);
    const long long radius = parseInteger(tokens[radiusIndex]);
    const shape_t shape = {radius, radius, parseInteger(tokens[xIndex]), parseInteger(tokens[yIndex]), 0.0, false};
    catalog.addShape(tokens[nameIndex], shape);
  }
  else if (tokens.front() == "show")
  {
    requireCount(tokens, argumentCount2);
    printShape(out, catalog.getShape(tokens[nameIndex]));
  }
  else
  {
    return false;
  }
  return true;
}
