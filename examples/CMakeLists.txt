add_executable(rix_basic
  basic.cpp
)

target_link_libraries(rix_basic
  PRIVATE
    rix::rix
)

add_executable(rix_csv_example
  csv.cpp
)

target_link_libraries(rix_csv_example
  PRIVATE
    rix::rix
)

add_executable(rix_debug_example
  debug.cpp
)

target_link_libraries(rix_debug_example
  PRIVATE
    rix::rix
)
