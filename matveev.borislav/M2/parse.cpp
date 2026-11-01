#include "parse.hpp"
#include <stdexcept>
#include <cmath>

matveev::Tokens matveev::splitLine(const std::string &line)
{
  Tokens tokens = {};
  std::size_t begin = line.find_first_not_of(" \t\r\n\v\f");
  while (begin != std::string::npos)
  {
    const std::size_t end = line.find_first_of(" \t\r\n\v\f", begin);
    tokens.push_back(line.substr(begin, end - begin));
    begin = line.find_first_not_of(" \t\r\n\v\f", end);
  }
  return tokens;
}
