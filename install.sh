#!/bin/bash

sudo apt-get install libeigen3-dev


# GNUPLOT
if [ "$yrelease" -eq "16" ]; then
    sudo apt-get install $APT_GET_FLAGS gnuplot5
else 
    if [ "$yrelease" -eq "14" ]; then
     cd $RAI_ROOT/dependencies
     # plotting dependencies
     sudo apt-get install $APT_GET_FLAGS libqt4-dev
     sudo apt-get install $APT_GET_FLAGS libcairo2-dev
     sudo apt-get install $APT_GET_FLAGS libpango1.0-dev
     wget https://downloads.sourceforge.net/project/gnuplot/gnuplot/5.0.5/gnuplot-5.0.5.tar.gz
     tar -xvzf gnuplot-5.0.5.tar.gz
     rm gnuplot-5.0.5.tar.gz
     cd gnuplot-5.0.5/
     ./configure --prefix=/usr --disable-wxwidgets && sudo make all -j && sudo make install
     cd $RAI_ROOT
    fi
fi

