set(RIX_AUTH_EXAMPLES
  01_memory_register_login
  02_password_hash
  03_session_refresh_logout
  04_token_issue
)

foreach(example_name IN LISTS RIX_AUTH_EXAMPLES)
  add_executable(rix_example_auth_${example_name}
    ${example_name}.cpp
  )

  target_compile_features(rix_example_auth_${example_name}
    PRIVATE
      cxx_std_20
  )

  target_link_libraries(rix_example_auth_${example_name}
    PRIVATE
      rix::rix
  )

  if(NOT MSVC)
    target_compile_options(rix_example_auth_${example_name}
      PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
  endif()
endforeach()
