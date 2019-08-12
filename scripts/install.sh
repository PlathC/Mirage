sudo apt-get install libpng-dev
sudo apt-get install zlib1g-dev

ccmake . -G %1 -BUILD_EXAMPLES=ON -BUILD_VIEWER=OFF
make