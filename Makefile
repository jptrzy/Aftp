TARGET =

CPP ?= gpp

build:
	$(CPP) -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) $(TARGET).cpp -o $(TARGET)$(python3-config --extension-suffix)
