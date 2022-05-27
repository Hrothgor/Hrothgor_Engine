git submodule update --init --recursive
mkdir ./build
cd ./build && cmake ../ -DCMAKE_POSITION_INDEPENDENT_CODE=ON -G "Unix Makefiles" && make -j3 && mv physics_engine libphysics_engine_lib.so .. && cd ..
