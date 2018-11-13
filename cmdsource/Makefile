CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT
CXXFLAGS      = -pipe -fopenmp -O2 -Wall -W -D_REENTRANT
H = osbcli.h
all:
	g++ -Wall -o OpenSystemBenchCLI main.cpp $(H) -g \
	../algorithms/*.cpp ../algorithms/headers/* \
	--std=c++14 -lpthread -lgomp -fopenmp $(LFLAGS) $(CFLAGS) $(CXXFLAGS)
