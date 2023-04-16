#ifndef __GRID_HPP__
#define __GRID_HPP__

#include <cstdint>

namespace snake_game {
class Grid {
 public:
  Grid(uint16_t cell_size) : cell_size_{cell_size} {}
  uint16_t cell_size() const { return cell_size_; }
  int32_t position_to_pixel(int32_t pos) const { return pos * cell_size_; }

 private:
  const uint16_t cell_size_;
};
}  // namespace snake_game

#endif