CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT 
CXXFLAGS      = -pipe -fopenmp -O2 -Wall -W -D_REENTRANT
all:
	g++ -Wall -o OpenSystemBenchCLI main.cpp -g \
	../Algorithms/*.cpp \
	../client/src/*.* --std=c++14 -lpthread -lgomp -fopenmp $(LFLAGS) $(CFLAGS) $(CXXFLAGS)
