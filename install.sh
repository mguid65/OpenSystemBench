#!/bin/bash

# OpenSystemBench Installer Script for Ubuntu-like systems
# Matthew Guidry Oct 2018
# Run at your own risk

if [[ $EUID -ne 0 ]]; then
  echo "Script must be run as root"
  exit 1
fi

printf "OpenSystemBench Bash Installer\nMatthew Guidry 2018\n\n"

read -p "Install OpenSystemBench(y/n)? " reply

case $reply in
  [Yy]* )

  printf "\nInstalling:\n\n"

  sudo apt install libcurl4-openssl-dev qt5-default qt5-qmake libgl1-mesa-dev libgomp1

  printf "\nBuilding Binary Package:\n\n"
  qmake -config release

  cd cmdsource
 
  make
  
  cd ../

  make

  read -p "Install Location [default:/usr/bin]: " install_path
  install_path=${install_path:=/usr/bin}

  printf "\nInstalling:\n"

  sudo cp ./bin/OpenSystemBench "$install_path"/OpenSystemBench 
  sudo cp ./bin/OpenSystemBenchCLI "$install_path"/OpenSystemBenchCLI
  sudo cp ./icon/OSBLogo_25_round.png /usr/share/icons/OSBLogo_25_round.png
  sudo cp ./desktop/OpenSystemBench.desktop /usr/share/applications/OpenSystemBench.desktop

  printf "\ndone\n"

esac

