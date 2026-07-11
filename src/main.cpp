#include <cstdint>
#include <iostream>

enum class TrafficLight : std::uint8_t { Red, Yellow, Green };

auto operator++(TrafficLight &tl) -> TrafficLight & {
  switch (tl) {
  case TrafficLight::Red:
    return tl = TrafficLight::Green;
  case TrafficLight::Yellow:
    return tl = TrafficLight::Red;
  case TrafficLight::Green:
    return tl = TrafficLight::Yellow;
  }
}

auto main() -> int {
  auto tl = TrafficLight::Green;
  ++tl;
  ++tl;

  if (tl == TrafficLight::Red) {
    std::cout << "Yes, it's red!\n";
  } else {
    std::cout << "Some other color!\n";
  }

  return 0;
}