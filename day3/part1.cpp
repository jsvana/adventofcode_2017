#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

const std::tuple<int, int> nearest_odd_square(const int number) {
  int prev_square = 1;
  int i = 1;
  while (true) {
    i += 2;
    int next_square = i * i;
    if (number < next_square && number >= prev_square) {
      return std::make_tuple(i - 2, prev_square);
    }
    prev_square = next_square;
  }
}

const std::array<int, 4> corners_from_square(
    const std::tuple<int, int>& square_info) {
  std::array<int, 4> corners;
  corners[3] = std::get<1>(square_info);
  const auto delta = std::get<0>(square_info) - 1;
  for (int i = 3; i > 0; i--) {
    corners[i - 1] = corners[i] - delta;
  }
  return corners;
}

const int distance_to_nearest_middle(const std::array<int, 4>& corners,
                                     const std::tuple<int, int>& square_info,
                                     const int number) {
  int nearest = -1;
  int distance = (std::get<0>(square_info) - 1) / 2;
  for (int i = 1; i < 4; i++) {
    std::cout << "c[i]: " << corners[i] << ", c[i-1]: " << corners[i - 1]
              << std::endl;
    if (number <= corners[i] && number >= corners[i - 1]) {
      if (corners[i] - number < number - corners[i - 1]) {
        std::cout << "c[i]: " << corners[i] << ", dist: " << distance
                  << std::endl;
        nearest = corners[i] - distance;
      } else {
        std::cout << "c[i-1]: " << corners[i] << ", dist: " << distance
                  << std::endl;
        nearest = corners[i - 1] + distance;
      }
      break;
    }
  }
  if (nearest < 0) {
    throw std::runtime_error("nearest not set");
  }
  std::cout << "nearest: " << nearest << std::endl;
  std::cout << "diff: " << (number - nearest) << std::endl;
  return abs(number - nearest);
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input>" << std::endl;
    return 1;
  }

  const auto tile = std::atoi(argv[1]);
  const auto parts = nearest_odd_square(tile);
  const auto square = std::get<0>(parts);
  const auto next_parts =
      std::make_tuple(square + 1, (square + 1) * (square + 1));
  std::cout << std::get<0>(parts) << std::endl;
  std::cout << std::get<1>(parts) << std::endl;

  const auto corners = corners_from_square(next_parts);
  std::cout << "dist to middle: "
            << distance_to_nearest_middle(corners, next_parts, tile)
            << std::endl;
  const auto distance = distance_to_nearest_middle(corners, next_parts, tile) +
                        (std::get<0>(parts) - 1) / 2;
  if (distance > std::get<0>(parts)) {
    std::cerr << "Value is too high" << std::endl;
  }
  // wrong
  std::cout << distance << std::endl;
}
