#include "commands.hpp"

bool matveev::executeFrame(const Tokens &tokens, const Catalog &catalog, std::ostream &out)
{
  constexpr std::size_t nameIndex = 1;
  constexpr std::size_t argumentCount2 = 2;
  if (tokens.front() == "frame")
  {
    requireCount(tokens, argumentCount2);
    printFrame(out, getFrame(catalog.getShape(tokens[nameIndex])));
  }
  else if (tokens.front() == "frameset")
  {
    requireCount(tokens, argumentCount2);
    printFrame(out, getFrame(catalog.getSet(tokens[nameIndex])));
  }
  else
  {
    return false;
  }
  return true;
}
