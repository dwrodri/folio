#include <iostream>

void print_rotation_schedule(int rows, int columns) {
    for (int i = 0; i <= rows / 2; i++) {
        for (int j = 0; j <= columns / 2; j++) {
            std::cout << '(' << i << ',' << j << ')' << " -> " << '(' << j << ","
                      << rows - (i + 1) << ')' << '\n';
        }
    }
}

int main(void) { print_rotation_schedule(4, 4); }