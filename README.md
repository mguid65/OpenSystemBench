# OpenSystemBench
A cross platform pc benchmarking application.

Supports Linux & Windows(For now).

This application uses Qt and compiled Qt static libraries.

# Available Tests(W.I.P)
* NBody Simulation
* PiDigits 

# Download
Get a stable version from release. 

# Build from Source
This project requires qt core and gui libraries to be statically linked.

Get build tools.
## Ubuntu/Debian
- sudo apt-get install build-essential perl python git libgmp-dev

Clone qtbase and build static libraries.
- >git clone https://github.com/mguid65/qtbase.git
- >cd qtbase 
- >./configure -static -prefix ./   ## select o and accept agreements
- >make                             ## building qtbase takes a long time, use -j if available

Clone OpenSystemBench and Build
- >git clone https://github.com/mguid65/OpenSystemBench.git
- >cd OpenSystemBench
- >PATH=/path/to/qtbase/bin:$PATH
- >export PATH
- >qmake -config release 
- >make

# To Run
- >./OpenSystemBench

# Todo
* Create GUI
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
  * IO
    * Find good IO bound Algorithms
  * Create Multicore Section
* ~~Test Algorithm Strategy~~


# Disclaimer
We are not responsible if you or your computer explode.
