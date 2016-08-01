#!/bin/bash

export CORES=`nproc`

rm -rf build && mkdir build && cd $_

cmake .. -DCMAKE_BUILD_TYPE=DEBUG
make -j${CORES}
make test
cd ..
