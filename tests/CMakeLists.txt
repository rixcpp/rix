add_executable(rix_tests
  rix_tests.cpp
)

target_link_libraries(rix_tests
  PRIVATE
    rix::rix
)

add_test(
  NAME rix_tests
  COMMAND rix_tests
)
