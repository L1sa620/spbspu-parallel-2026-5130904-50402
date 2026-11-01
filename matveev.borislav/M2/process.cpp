#include "process.hpp"
#include <stdexcept>
#include <cerrno>
#include <csignal>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>

matveev::Process::Process(const std::uint64_t seed, const std::vector< int > &inherited)
{
  constexpr std::size_t channelEnds = 2;
  constexpr std::size_t childEnd = 1;
  int sockets[channelEnds] = {invalidDescriptor, invalidDescriptor};
  if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0)
  {
    throw std::runtime_error("Cannot create channel");
  }
  Descriptor parent(sockets[0]);
  Descriptor child(sockets[childEnd]);
  makeNonblocking(parent.get());
  const pid_t pid = ::fork();
  if (pid < 0)
  {
    throw std::runtime_error("Cannot create process");
  }
  if (pid == 0)
  {
    parent.reset();
    for (const int descriptor: inherited)
    {
      if (descriptor >= 0)
      {
        ::close(descriptor);
      }
    }
    ::close(STDIN_FILENO);
    ::close(STDOUT_FILENO);
    const int status = runWorker(child.get(), seed);
    child.reset();
    ::_exit(status);
  }
  pid_ = pid;
  channel_.reset(parent.release());
}

matveev::Process::~Process()
{
  stop(true);
}

int matveev::Process::getDescriptor() const noexcept
{
  return channel_.get();
}

void matveev::Process::stop(const bool force) noexcept
{
  channel_.reset();
  if (pid_ > 0)
  {
    if (force)
    {
      ::kill(pid_, SIGKILL);
    }
    while ((::waitpid(pid_, nullptr, 0) < 0) && (errno == EINTR))
    {}
    pid_ = 0;
  }
}
