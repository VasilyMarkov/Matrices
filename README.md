# Matrices determinant compute

## Install
    $git clone git@github.com:VasilyMarkov/Matrices.git
## Build
### Manual Build
    $cmake -S . -B release -DCMAKE_BUILD_TYPE=Release && cmake --build release
### Auto Build
    $./bld 
### Auto Build with tests
    $./bld TEST

## Run
### App
    $./matrices < data_file
### Tests
    $./run_tests unit 
Tests results in tests/result.log
