CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT
CXXFLAGS      = -pipe -fopenmp -O2 -Wall -W -D_REENTRANT
Conf = osbcli.h
Sys = ../sysinfo/cpuinfo.h
Sub = ../headers/submit.h
all:
	g++ -Wall -o ../bin/OpenSystemBenchCLI main.cpp $(Conf) $(Sys) $(Sub) -g \
	../algorithms/*.cpp ../algorithms/headers/* \
	--std=c++14 -lpthread -lgomp -fopenmp -lcurl $(LFLAGS) $(CFLAGS) $(CXXFLAGS)
