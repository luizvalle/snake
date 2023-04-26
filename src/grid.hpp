#ifndef __GRID_HPP__
#define __GRID_HPP__

#include <cstdint>

namespace snake_game {
    class Grid {
    public:
        Grid(uint16_t cell_size, uint16_t num_rows, uint16_t num_cols)
            : cell_size_{cell_size}, num_rows_{num_rows}, num_cols_{num_cols} {}
        uint16_t cell_size() const { return cell_size_; }
        uint16_t num_rows() const { return num_rows_; }
        uint16_t num_cols() const { return num_cols_; }
        int32_t position_to_pixel(int32_t pos) const { return pos * cell_size_; }

    private:
        const uint16_t cell_size_, num_rows_, num_cols_;
    };
} // namespace snake_game

#endif