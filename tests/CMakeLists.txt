FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.2.0
)

FetchContent_MakeAvailable(Catch2)

#SimpleVec
add_executable(simplevec_test SimpleVecTests.cpp)
target_include_directories(simplevec_test PRIVATE ../src/containers>)
target_compile_features(simplevec_test PRIVATE cxx_std_17)
target_link_libraries(simplevec_test PRIVATE Catch2::Catch2WithMain)

# SimpleMat
add_executable(simplemat_test SimpleMatTests.cpp)
target_include_directories(simplevec_test PRIVATE ../src/containers>)
target_compile_features(simplemat_test PRIVATE cxx_std_17)
target_link_libraries(simplemat_test PRIVATE Catch2::Catch2WithMain)


# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME SimpleVec COMMAND simplevec_test) # Command can be a target
add_test(NAME SimpleMat COMMAND simplemat_test) # Command can be a target
