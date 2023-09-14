# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
add_executable(matmul_benchmark matmul_benchmark.cpp)
target_include_directories(matmul_benchmark PRIVATE ../src/containers)
target_compile_features(matmul_benchmark PRIVATE cxx_std_17)