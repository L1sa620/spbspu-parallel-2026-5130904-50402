#include "console.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include "commands.hpp"

void matveev::runConsole()
{
  Catalog catalog = {};
  std::string line = {};
  while (std::getline(std::cin, line))
  {
    executeLine(line, catalog, std::cout);
  }
  if (!std::cin.eof() || std::cin.bad() || !std::cout)
  {
    throw std::runtime_error("Console input/output failed");
  }
}
