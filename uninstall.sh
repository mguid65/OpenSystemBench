#!/bin/bash

printf "\nOpenSystemBench Bash Uninstaller\n\nMatthew Guidry 2018\n\nUninstalling:\n\n"

sudo rm /usr/bin/OpenSystemBench
sudo rm /usr/share/icons/OSBLogo*
sudo rm /usr/share/applications/OpenSystemBench.desktop

echo
echo 'done'
