#include <exception>
#include <iostream>
#include <stdexcept>
#include "options.hpp"

int main(const int argc, char** const argv)
{
  constexpr int invalidInput = 1;
  constexpr int internalError = 2;
  try
  {
    matveev::parseArguments(argc, argv);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return invalidInput;
  }
  catch (const std::out_of_range& error)
  {
    std::cerr << error.what() << "\n";
    return invalidInput;
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what() << "\n";
    return internalError;
  }
  return 0;
}
