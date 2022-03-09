git submodule update --init --recursive
mkdir ./build
cd ./build && cmake ../ -G "Unix Makefiles" && cmake --build . -- -j 3 && make -j3 && mv physics_engine .. && cd ..