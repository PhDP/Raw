#!/bin/bash

export CORES=`nproc`

rm -rf tmp_install && mkdir tmp_install && cd $_
cmake .. -DCMAKE_BUILD_TYPE=RELEASE -DBuildTests=OFF
make -j${CORES}
sudo make install

cd .. && rm -rf tmp_install
