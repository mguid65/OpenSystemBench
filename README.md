# OpenSystemBench
A cross platform pc benchmarking application.

Supports Linux & ~~Windows(For now)~~*.

*Windows support requires more time than available for project. Will be implemented at a future time.

This application uses statically compiled Qt libraries.
There is now a Linux CLI version.

# Available Tests
* NBody Simulation
* PiDigits 
* Mandelbrot
* Spectral Norm
* Binary Trees

# Download
Get a stable version from https://opensystembench.com 
Tested on Ubuntu 17.10
Works in Ubuntu virtual machines with workaround:
- ##to use in vm
- > sudo -H ./OpenSystemBench
- ##An error will be shown and nothing will happen, then run application as normal and it should work
- > ./OpenSystemBench

# Build from Source
The release version has statically linked qt libraries.
It can be run with shared libs also.

Get build tools.
## Ubuntu/Debian
- sudo apt-get install build-essential perl python git libgmp-dev

Clone qtbase and build static libraries.
- >git clone https://github.com/mguid65/qt5.git
- >cd qt5
- >./init-repository
- >./configure -static -prefix ./   ## select o and accept agreements
- >make                             ## building qtbase takes a long time, use -j if available

Clone OpenSystemBench and Build
- >git clone https://github.com/mguid65/OpenSystemBench.git
- >cd OpenSystemBench
- >PATH=/path/to/qt/bin:$PATH
- >export PATH
- >qmake -config release 
- >make

# To Run
- >./OpenSystemBench

# Todo
* ~~Create GUI~~
  * ~~Config Window~~
    * ~~Standard Check~~
    * ~~Custom Check~~
      * ~~CPU Check~~
      * ~~IO Check~~
    * ~~Overclocked Check~~
    * ~~Run Button~~
    * ~~Quit Button~~
  *~~Running Window~~
    * ~~Running Status View~~
    * ~~Quit Button~~
* ~~Create Algorithm Strategy~~
* Add Algorithms
  * ~~CPU Single Core~~
    * ~~NBody~~
    * ~~PiDigits~~
  * ~~CPU Multi Core~~
    * ~~MandelBrot Calculation~~
    * ~~Spectral Norm~~
  * ~~IO~~
    * ~~Binary Trees~~
  * ~~Create Multicore Section~~
* ~~Test Algorithm Strategy~~
* ~~Create Save Functionality to CSV~~
* ~~Submission Functionality~~

# Disclaimer
We are not responsible if you or your computer explode. In the event that you explode, seek professional medical help immediately.
