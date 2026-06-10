add_executable(rix_pdf_01_basic
  01_basic.cpp
)

target_link_libraries(rix_pdf_01_basic
  PRIVATE
    rix::rix
)

add_executable(rix_pdf_02_text
  02_text.cpp
)

target_link_libraries(rix_pdf_02_text
  PRIVATE
    rix::rix
)

add_executable(rix_pdf_03_table
  03_table.cpp
)

target_link_libraries(rix_pdf_03_table
  PRIVATE
    rix::rix
)

add_executable(rix_pdf_04_drawing
  04_drawing.cpp
)

target_link_libraries(rix_pdf_04_drawing
  PRIVATE
    rix::rix
)

add_executable(rix_pdf_05_metadata
  05_metadata.cpp
)

target_link_libraries(rix_pdf_05_metadata
  PRIVATE
    rix::rix
)

add_executable(rix_pdf_06_make_text
  06_make_text.cpp
)

target_link_libraries(rix_pdf_06_make_text
  PRIVATE
    rix::rix
)

add_executable(rix_pdf_07_error_handling
  07_error_handling.cpp
)

target_link_libraries(rix_pdf_07_error_handling
  PRIVATE
    rix::rix
)
