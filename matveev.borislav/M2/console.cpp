#include "console.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include "parse.hpp"

void matveev::runConsole()
{
  std::string line = {};
  while (std::getline(std::cin, line))
  {
    if (!splitLine(line).empty())
    {
      std::cout << "<UNKNOWN COMMAND>\n";
      std::cout.flush();
    }
  }
  if (!std::cin.eof() || std::cin.bad() || !std::cout)
  {
    throw std::runtime_error("Console input/output failed");
  }
}
