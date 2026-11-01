#include "commands.hpp"
#include <exception>
#include <ostream>

void matveev::executeLine(const std::string &line, Catalog &catalog, std::ostream &out)
{
  try
  {
    const Tokens tokens = splitLine(line);
    if (tokens.empty())
    {
      return;
    }
    const bool known = executeShape(tokens, catalog, out)
        || executeSet(tokens, catalog, out)
        || executeFrame(tokens, catalog, out);
    if (!known)
    {
      out << "<UNKNOWN COMMAND>\n";
    }
  }
  catch (const std::exception &)
  {
    out << "<INVALID COMMAND>\n";
  }
  out.flush();
}
