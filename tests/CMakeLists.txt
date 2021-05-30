add_executable(test mainTests.cpp speedTests.cpp positionTests.cpp rotationTests.cpp mathTests.cpp)
target_link_libraries(test GTest::gtest racer racerController mechanicalValues math)
add_test(tests test)
