#!/bin/bash
set -x

version=$(lsb_release -r | awk '{ print $2 }')
yrelease=$( echo "$version" | cut -d. -f1 )

# BUILD TOOLS
sudo apt-get install -y -qq cmake

sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test 
sudo apt-get update -y && sudo apt-get install -y -qq g++-7 g++-6

# EIGEN
sudo apt-get install -y -qq libeigen3-dev 

# BOOST
sudo apt-get install -y -qq libboost-all-dev

# GNUPLOT
if [ "$yrelease" -eq "16" ]; then
    sudo apt-get install -y -qq gnuplot5
else 
    if [ "$yrelease" -eq "14" ]; then
        cd $RAI_ROOT/dependencies
        # plotting dependencies
        sudo apt-get install -y -qq libqt4-dev
        sudo apt-get install -y -qq libcairo2-dev
        sudo apt-get install -y -qq libpango1.0-dev
        wget https://downloads.sourceforge.net/project/gnuplot/gnuplot/5.0.5/gnuplot-5.0.5.tar.gz
        tar -xvzf gnuplot-5.0.5.tar.gz
        rm gnuplot-5.0.5.tar.gz
        cd gnuplot-5.0.5/
        ./configure --prefix=/usr --disable-wxwidgets && sudo make all -j && sudo make install
        cd $RAI_ROOT
    fi
fi

sudo rm -rf build
mkdir build
cd build
cmake ..
sudo make install -j
sudo rm -rf build 
cd ..

