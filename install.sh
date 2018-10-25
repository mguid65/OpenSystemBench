#!/bin/bash

sudo apt install libcurl4-openssl-dev qt5-default qt5-qmake libgl1-mesa-dev libgomp1

qmake -config release

make

sudo cp ./bin/OpenSystemBench /usr/bin/OpenSystemBench
sudo cp ./icon/OSBLogo.svg /usr/share/icons/OSBLogo.svg
sudo cp ./desktop/OpenSystemBench.desktop /usr/share/applications/OpenSystemBench.desktop

echo 'done'
