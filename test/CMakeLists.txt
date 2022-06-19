# SPDX-FileCopyrightText: 2022 Carson Black <uhhadd@gmail.com>
#
# SPDX-License-Identifier: LicenseRef-KDE-Accepted-GPL

find_package(Qt5Test REQUIRED)

add_executable(testNGLib
    test.cpp
)
add_test(testNGLib testNGLib)

target_link_libraries(
    testNGLib
        Qt5::Test NGLib
)
