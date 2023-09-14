#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "../containers/SimpleMat.hpp"

template <typename T>
float generate_number(T const start, T const end) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<T> uniform(start, end);
    return uniform(rng);
}

std::chrono::nanoseconds time_matmul(
        size_t dim, void (*matmul_fn)(folio::SimpleMat<float> const&,
                            folio::SimpleMat<float> const&, folio::SimpleMat<float>&)) {
    auto generator = []() { return generate_number<float>(0.0, 1.0); };
    folio::SimpleMat<float> a{dim, dim, generator};
    folio::SimpleMat<float> b{dim, dim, generator};
    folio::SimpleMat<float> c{dim, dim, 0.0};
    auto start = std::chrono::high_resolution_clock::now();
    matmul_fn(a, b, c);
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start);
}

void compare_naive_to_tiled() {
    std::vector<std::tuple<size_t, std::string, std::chrono::nanoseconds>> results{};
    for (size_t i = 0; i < 10; i++) {
        std::cerr << "Progress: " << i * 10 << "%\r";
        for (size_t dim : {128, 256, 512, 1024, 2048}) {
            results.emplace_back(
                    dim, "tiled", time_matmul(dim, folio::matmul_tiled<float, 64>));
            results.emplace_back(
                    dim, "naive", time_matmul(dim, folio::naive_matmul<float>));
        }
    }
    std::cout << "name,dim,ns\n";
    for (auto [dim, name, ns] : results) {
        std::cout << name << ',' << dim << "," << ns.count() << '\n';
    }
}

void compare_tile_sizes() {
    std::vector<std::tuple<size_t, size_t, std::string, std::chrono::nanoseconds>>
            results{};
    for (size_t i = 0; i < 10; i++) {
        std::cerr << "Progress: " << i * 10 << "%\r";
        for (size_t dim : {128, 256, 512, 1024, 2048}) {
            results.emplace_back(
                    dim, 2, "tiled", time_matmul(dim, folio::matmul_tiled<float, 2>));
            results.emplace_back(
                    dim, 4, "tiled", time_matmul(dim, folio::matmul_tiled<float, 4>));
            results.emplace_back(
                    dim, 8, "tiled", time_matmul(dim, folio::matmul_tiled<float, 8>));
            results.emplace_back(
                    dim, 16, "tiled", time_matmul(dim, folio::matmul_tiled<float, 16>));
            results.emplace_back(
                    dim, 32, "tiled", time_matmul(dim, folio::matmul_tiled<float, 32>));
            results.emplace_back(
                    dim, 64, "tiled", time_matmul(dim, folio::matmul_tiled<float, 64>));
        }
    }

    std::cout << "dim,tile,ns\n";
    for (auto [dim, tile, _, ns] : results) {
        std::cout << dim << "," << tile << "," << ns.count() << '\n';
    }
}

int main() { compare_tile_sizes(); }
