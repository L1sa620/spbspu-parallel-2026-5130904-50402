#include <iostream>
#include <exception>
#include "console.hpp"

int main(const int argc, char *[])
{
  constexpr int expectedArguments = 1;
  constexpr int argumentError = 1;
  constexpr int internalError = 2;
  if (argc != expectedArguments)
  {
    std::cerr << "Usage: lab\n";
    return argumentError;
  }
  try
  {
    matveev::runConsole();
  }
  catch (const std::exception &error)
  {
    std::cerr << error.what() << "\n";
    return internalError;
  }
  return 0;
}
