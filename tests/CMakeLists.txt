project(Template_List CXX)

FILE(GLOB_RECURSE TESTS_LIST ${PROJECT_SOURCE_DIR}/*.hpp ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${TESTS_LIST})
target_link_libraries(${PROJECT_NAME} gtest_main)

add_test(
        NAME unit
        COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)