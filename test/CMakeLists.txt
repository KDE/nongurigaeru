find_package(Qt5Test REQUIRED)

add_executable(testNGLib
    test.cpp
)
add_test(testNGLib testNGLib)

target_link_libraries(
    testNGLib
        Qt5::Test NGLib
)
