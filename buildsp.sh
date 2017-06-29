file="$1"
truncate -s 0 demo.cpp
cat $file >> demo.cpp
mkdir build 
cd build 
cmake ..
make
cd
mv build/demo demo
rm -rf build
