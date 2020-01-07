CXXFLAGS=--std=c++17

plot: proc
	./proc > t
	./myplot.sh t
