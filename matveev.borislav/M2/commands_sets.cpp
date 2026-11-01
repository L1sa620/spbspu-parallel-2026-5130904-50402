#include "commands.hpp"
#include <ostream>
#include <stdexcept>

bool matveev::executeSet(const Tokens &tokens, Catalog &catalog, std::ostream &out)
{
  constexpr std::size_t nameIndex = 1;
  constexpr std::size_t sizeIndex = 2;
  constexpr std::size_t argumentCount2 = 2;
  if (tokens.front() == "set")
  {
    constexpr std::size_t headerSize = 3;
    if (tokens.size() < headerSize)
    {
      throw std::invalid_argument("Incomplete set");
    }
    const std::uint64_t count = parseUnsigned(tokens[sizeIndex]);
    if ((count == 0) || (count != tokens.size() - headerSize))
    {
      throw std::invalid_argument("Invalid set size");
    }
    const std::vector< std::string > names(tokens.begin() + headerSize, tokens.end());
    catalog.addSet(tokens[nameIndex], names);
  }
  else if (tokens.front() == "showset")
  {
    requireCount(tokens, argumentCount2);
    for (const shape_t &shape: catalog.getSet(tokens[nameIndex]))
    {
      printShape(out, shape);
    }
  }
  else
  {
    return false;
  }
  return true;
}
