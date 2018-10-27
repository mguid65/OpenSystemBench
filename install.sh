#!/bin/bash

# OpenSystemBench Installer Script for Ubuntu-like systems
# Matthew Guidry Oct 2018
# Run at your own risk

printf "OpenSystemBench Bash Installer\nMatthew Guidry 2018\n\n"

read -p "Install OpenSystemBench? " -n 1 -r

if [[ $REPLY =~ ^[Yy]$ ]]
then
  printf "\nInstalling:\n\n"
  apt install libcurl4-openssl-dev qt5-default qt5-qmake libgl1-mesa-dev libgomp1

  printf "\nBuilding Binary Package:\n\n"
  qmake -config release

  make

  read -p "Install Location [default:/usr/bin]: " install_path
  install_path=${install_path:~/usr/bin}

  printf "\nInstalling:\n\n"

  cp ./bin/OpenSystemBench $install_path/OpenSystemBench
  cp ./icon/OSBLogo.svg /usr/share/icons/OSBLogo.svg
  cp ./desktop/OpenSystemBench.desktop /usr/share/applications/OpenSystemBench.desktop

  printf "\ndone\n"

fi
