mkdir ./buildComponents
cd ./buildComponents && cmake ../ -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCOMPILING_COMPONENTS=ON -G "Unix Makefiles" && make -j3 && mv libcomponents.so .. && cd ..
