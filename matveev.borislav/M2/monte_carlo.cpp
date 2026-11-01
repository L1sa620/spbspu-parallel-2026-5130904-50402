#include "monte_carlo.hpp"
#include <random>
#include <stdexcept>

std::uint64_t matveev::countHits(const std::vector< shape_t > &shapes, const frame_t &frame,
    const std::uint64_t tries, const std::uint64_t seed)
{
  std::mt19937_64 generator(seed);
  std::uniform_real_distribution< double > horizontal(frame.left, frame.right);
  std::uniform_real_distribution< double > vertical(frame.bottom, frame.top);
  std::uint64_t hits = 0;
  for (std::uint64_t i = 0; i < tries; ++i)
  {
    const double x = horizontal(generator);
    const double y = vertical(generator);
    for (const shape_t &shape: shapes)
    {
      if (contains(shape, x, y))
      {
        ++hits;
        break;
      }
    }
  }
  return hits;
}

double matveev::calculateArea(const std::vector< shape_t > &shapes, std::uint64_t,
    const std::uint64_t tries, const std::uint64_t seed)
{
  if (tries == 0)
  {
    throw std::invalid_argument("Zero tries");
  }
  const std::vector< shape_t > localShapes = translateShapes(shapes);
  const frame_t frame = getFrame(localShapes);
  const std::uint64_t hits = countHits(localShapes, frame, tries, seed);
  const double rectangle = (frame.right - frame.left) * (frame.top - frame.bottom);
  return rectangle * (static_cast< double >(hits) / tries);
}
