FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.2.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(simplevec_test SimpleVecTests.cpp)
target_include_directories(simplevec_test PRIVATE ../src/containers)
target_compile_features(simplevec_test PRIVATE cxx_std_17)
target_link_libraries(simplevec_test PRIVATE Catch2::Catch2WithMain)
# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME SimpleVec COMMAND simplevec_test) # Command can be a target

add_executable(binarytree_test BinaryTreeTest.cpp)
target_include_directories(binarytree_test PRIVATE ../src/containers)
target_compile_features(binarytree_test PRIVATE cxx_std_17)
target_link_libraries(binarytree_test PRIVATE Catch2::Catch2WithMain)
add_test(NAME BinaryTree COMMAND binarytree_test) # Command can be a target

add_executable(sorts_test SortsTest.cpp)
target_include_directories(sorts_test PRIVATE ../src/algos)
target_compile_features(sorts_test PRIVATE cxx_std_17)
target_link_libraries(sorts_test PRIVATE Catch2::Catch2WithMain)
add_test(NAME Sorts COMMAND sorts_test) # Command can be a target

# enable UBSan and Asan for all the tests in debug mode
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_options(simplevec_test PUBLIC -fsanitize=address -fsanitize=undefined)
    target_link_options(binarytree_test PUBLIC -fsanitize=address -fsanitize=undefined)
    target_link_options(sorts_test PUBLIC -fsanitize=address -fsanitize=undefined)
endif()