.PHONY : all test clean
CXX = g++
CXXFLAGS = -O2
CPP_FILES = $(wildcard *.cpp)
OBJECTS = $(CPP_FILES:.cpp=.o)
RUNABLE = server
all: test $(RUNABLE)
$(RUNABLE) : $(OBJECTS)
	$(CXX) $^ -o $@ -lpthread -lwiringPi
test:	
	cd test/APDS9960 && $(CXX) *.cpp -o test_APDS9960 -lwiringPi && cd -
	cd test/L293D && $(CXX) *.cpp -o test_L293D -lwiringPi && cd -
	cd test/opt3001 && $(CXX) *.cpp -o test_opt3001 -lwiringPi && cd -
	cd test/udp && $(CXX) -DONLY_TEST_UDP *.cpp -o test_udp && cd -
clean:	
	$(RM) $(OBJECTS) $(RUNABLE)
	for i in test/*; do $(RM) $i/test_*; done 
