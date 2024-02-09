# Matrices determinant compute

## Install
    $git clone git@github.com:VasilyMarkov/Matrices.git
## Manual Build
    $cmake -S . -B release -DCMAKE_BUILD_TYPE=Release && cmake --build release
## Auto Build
    $./bld 
## Auto Build with tests
    $./bld TEST

## Run
    $./matrices < data_file
## Run tests
    $./run_tests unit 
    Tests results in tests/result.log
