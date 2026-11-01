#include "protocol.hpp"
#include <cstring>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <cstddef>

std::vector< char > matveev::makeRequest(const std::vector< shape_t > &shapes,
    const std::uint64_t threads, const std::uint64_t tries)
{
  static_assert(std::is_trivially_copyable< shape_t >::value, "Shapes must support binary copying");
  static_assert(std::is_standard_layout< shape_t >::value, "Shape fields must have known offsets");
  constexpr std::size_t headerFields = 3;
  static_assert(sizeof(request_t) == headerFields * sizeof(std::uint64_t), "Unexpected request padding");
  const std::size_t maximum = (std::numeric_limits< std::size_t >::max() - sizeof(request_t)) / sizeof(shape_t);
  if (shapes.empty() || (shapes.size() > maximum) || (tries == 0))
  {
    throw std::invalid_argument("Invalid request");
  }
  const request_t header = {threads, tries, shapes.size()};
  std::vector< char > bytes(sizeof(header) + shapes.size() * sizeof(shape_t));
  std::memcpy(bytes.data(), &header, sizeof(header));
  for (std::size_t i = 0; i < shapes.size(); ++i)
  {
    const shape_t &shape = shapes[i];
    char *const target = bytes.data() + sizeof(header) + i * sizeof(shape_t);
    std::memcpy(target + offsetof(shape_t, radiusX), &shape.radiusX, sizeof(shape.radiusX));
    std::memcpy(target + offsetof(shape_t, radiusY), &shape.radiusY, sizeof(shape.radiusY));
    std::memcpy(target + offsetof(shape_t, x), &shape.x, sizeof(shape.x));
    std::memcpy(target + offsetof(shape_t, y), &shape.y, sizeof(shape.y));
    std::memcpy(target + offsetof(shape_t, angle), &shape.angle, sizeof(shape.angle));
    std::memcpy(target + offsetof(shape_t, ellipse), &shape.ellipse, sizeof(shape.ellipse));
  }
  return bytes;
}
