#ifndef MATVEEV_COMMANDS_HPP
#define MATVEEV_COMMANDS_HPP

#include <iosfwd>
#include "parse.hpp"
#include "catalog.hpp"

namespace matveev
{
  class Manager;
  bool executeShape(const Tokens &tokens, Catalog &catalog, std::ostream &out);
  bool executeSet(const Tokens &tokens, Catalog &catalog, std::ostream &out);
  bool executeFrame(const Tokens &tokens, const Catalog &catalog, std::ostream &out);
  bool executeSubmit(const Tokens &tokens, const Catalog &catalog, Manager &manager);
  bool executeStatus(const Tokens &tokens, Manager &manager, std::ostream &out);
  bool executeExtra(const Tokens &tokens, Catalog &catalog, Manager &manager, std::ostream &out);
  void executeLine(const std::string &line, Catalog &catalog, std::ostream &out);
}

#endif
