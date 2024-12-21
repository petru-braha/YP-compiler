#!/bin/bash

echo "to setup our project we need to check bison and flex installation on your machine"
sudo apt-get update

# install bison
dpkg -s bison &> /dev/null
if [ $? -eq 0 ]
then
    echo "bison is already installed"
else
    echo "installing bison"
    sudo apt-get install bison
fi

# install flex
dpkg -s flex &> /dev/null
if [ $? -eq 0 ]
then
    echo "flex is already installed"
else
    echo "installing flex"
    sudo apt-get install flex
fi

chmod +x src/discard.sh
chmod +x compile.sh
./compile.sh
