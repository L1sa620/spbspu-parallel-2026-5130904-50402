#include "manager.hpp"
#include <stdexcept>
#include <utility>
#include "parse.hpp"

void matveev::Manager::spawn(const std::string &name, const std::uint64_t seed)
{
  requireName(name);
  if (workers_.count(name) != 0)
  {
    throw std::invalid_argument("Process already exists");
  }
  std::vector< int > inherited = {};
  for (const auto &entry: workers_)
  {
    inherited.push_back(entry.second.process->getDescriptor());
  }
  std::unique_ptr< Process > process = std::make_unique< Process >(seed, inherited);
  workers_[name].process = std::move(process);
}

void matveev::Manager::submit(const std::string &process, const std::string &name,
    const std::vector< shape_t > &shapes, const std::uint64_t threads, const std::uint64_t tries)
{
  requireName(name);
  worker_t &worker = workers_.at(process);
  if (worker.stopping || (calculations_.count(name) != 0))
  {
    throw std::invalid_argument("Cannot submit calculation");
  }
  task_t task = {name, makeRequest(shapes, threads, tries)};
  const calculation_t calculation = {process, State::pending, {}};
  calculations_.emplace(name, calculation);
  try
  {
    worker.queue.push_back(std::move(task));
  }
  catch (const std::exception &)
  {
    calculations_.erase(name);
    throw;
  }
  startNext(worker);
}

void matveev::Manager::startNext(worker_t &worker)
{
  if (!worker.current.empty())
  {
    return;
  }
  if (worker.stopping)
  {
    worker.process->stop(false);
  }
  else if (!worker.queue.empty())
  {
    worker.current.swap(worker.queue.front().name);
    worker.process->start(worker.queue.front().bytes);
    worker.queue.pop_front();
  }
}

void matveev::Manager::cancelQueued(worker_t &worker)
{
  for (const task_t &task: worker.queue)
  {
    calculations_.at(task.name).state = State::canceled;
  }
  worker.queue.clear();
}

void matveev::Manager::disconnect(worker_t &worker)
{
  worker.stopping = true;
  if (!worker.current.empty())
  {
    calculations_.at(worker.current).state = State::canceled;
    worker.current.clear();
  }
  cancelQueued(worker);
  worker.process->stop(true);
}
