add_executable(tests
    main.cpp
)
target_link_libraries(tests glvis)
target_include_directories(tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
