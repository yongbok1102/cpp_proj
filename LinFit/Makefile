LinFit : LinFit.o LinFitRoutine.o
	g++ -o LinFit LinFit.o LinFitRoutine.o

LinFit.o : LinFit.cpp LinFitRoutine.h
	g++ -c LinFit.cpp

LinFitRoutine.o : LinFitRoutine.cpp
	g++ -c LinFitRoutine.cpp

clean : 
	rm -f LinFit.o LinFitRoutine.o LinFit
