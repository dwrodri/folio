#include <iostream>
#include <limits>
#include <queue>
#include <vector>

class Solution {
    struct GraphNode {
        int row = 0;
        int col = 0;
        int cumulative_distance = std::numeric_limits<int>::max();

        bool operator<(GraphNode const& other) const {
            return this->cumulative_distance > other.cumulative_distance;
        }
    };

  public:
    int minPathSum(std::vector<std::vector<int>>& grid) {
        size_t destination_row = grid.size() - 1;
        size_t destination_col = grid.back().size() - 1;
        std::priority_queue<GraphNode> unvisited{std::less<GraphNode>{},
                std::vector<GraphNode>{destination_row * destination_col}};
        unvisited.push(GraphNode{0, 0, grid[0][0]});
        GraphNode current = unvisited.top();
        for (; current.row != destination_row || current.col != destination_col;
                current = unvisited.top()) {
            std::cout << '[' << current.row << ',' << current.col << ']' << ' '
                      << current.cumulative_distance << std::endl;
            unvisited.pop();
            if (current.row < destination_row) {
                unvisited.push(GraphNode{current.row + 1, current.col,
                        current.cumulative_distance +
                                grid[current.row + 1][current.col]});
            }
            if (current.col < destination_col) {
                unvisited.push(GraphNode{current.row, current.col + 1,
                        current.cumulative_distance +
                                grid[current.row][current.col + 1]});
            }
        }
        return current.cumulative_distance;
    }
};

int main() {
    std::vector<std::vector<int>> grid = {
            {0, 7, 7, 8, 1, 2, 4, 3, 0, 0, 5, 9, 8, 3, 6, 5, 1, 0},
            {2, 1, 1, 0, 8, 1, 3, 3, 9, 9, 5, 8, 7, 5, 7, 5, 5, 8},
            {9, 2, 3, 1, 2, 8, 1, 2, 3, 7, 9, 7, 9, 3, 0, 0, 3, 8},
            {3, 9, 3, 4, 8, 1, 2, 6, 8, 9, 3, 4, 9, 4, 8, 3, 6, 2},
            {3, 7, 4, 7, 6, 5, 6, 5, 8, 6, 7, 3, 6, 2, 2, 9, 9, 3},
            {2, 3, 1, 1, 5, 4, 7, 4, 0, 7, 7, 6, 9, 1, 5, 5, 0, 3},
            {0, 8, 8, 8, 4, 7, 1, 0, 2, 6, 1, 1, 1, 6, 4, 2, 7, 9},
            {8, 6, 6, 8, 3, 3, 5, 4, 6, 2, 9, 8, 6, 9, 6, 6, 9, 2},
            {6, 2, 2, 8, 0, 6, 1, 1, 4, 5, 3, 1, 7, 3, 9, 3, 2, 2},
            {8, 9, 8, 5, 3, 7, 5, 9, 8, 2, 8, 7, 4, 4, 1, 9, 2, 2},
            {7, 3, 3, 1, 0, 9, 4, 7, 2, 3, 2, 6, 7, 1, 7, 7, 8, 1},
            {4, 3, 2, 2, 7, 0, 1, 4, 4, 4, 3, 8, 6, 2, 1, 2, 5, 4},
            {1, 9, 3, 5, 4, 6, 4, 3, 7, 1, 0, 7, 2, 4, 0, 7, 8, 0},
            {7, 1, 4, 2, 5, 9, 0, 4, 1, 4, 6, 6, 8, 9, 7, 1, 4, 3},
            {9, 8, 6, 8, 2, 6, 5, 6, 2, 8, 3, 2, 8, 1, 5, 4, 5, 2},
            {3, 7, 8, 6, 3, 4, 2, 3, 5, 1, 7, 2, 4, 6, 0, 2, 5, 4},
            {8, 2, 1, 2, 2, 6, 6, 0, 7, 3, 6, 4, 5, 9, 4, 4, 5, 7}};
    int solved = Solution().minPathSum(grid);
    std::cout << solved << std::endl;
}