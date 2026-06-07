add_executable(rix_basic
  basic.cpp
)

target_link_libraries(rix_basic
  PRIVATE
    rix::rix
)
