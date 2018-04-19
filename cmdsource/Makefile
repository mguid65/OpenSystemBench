CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT 
CXXFLAGS      = -pipe -fopenmp -O2 -Wall -W -D_REENTRANT
LFLAGS        = -Wl,-O1
all:
	g++ -Wall -o OpenSystemBenchCLI main.cpp ~/OpenSystemBench/Algorithms/headers/*.h ~/OpenSystemBench/Algorithms/*.cpp ../client/src/*.* --std=c++14 -lpthread -lgmpxx -lgmp -lgomp -fopenmp $(LFLAGS) $(CFLAGS) $(CXXFLAGS)
