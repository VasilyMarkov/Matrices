message("Matrices building...")

add_executable(matrices 
    main.cpp
)

target_include_directories(matrices 
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)


