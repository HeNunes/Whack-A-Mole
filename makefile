flags:= -pthread

all: WhackAMole.o globais.o tela.o Toupeira.o Jogador.o
	g++ $(flags) -o all globais.o Toupeira.o Jogador.o tela.o WhackAMole.o  main.cpp

main.o: main.cpp
	g++ $(flags) -c main.cpp

WhackAMole.o: WhackAMole.cpp WhackAMole.h
	g++ $(flags) -c WhackAMole.cpp

tela.o: tela.cpp tela.h
	g++ $(flags) -c tela.cpp

Toupeira.o: Toupeira.cpp Toupeira.h
	g++ $(flags) -c Toupeira.cpp

Jogador.o: Jogador.cpp Jogador.h
	g++ $(flags) -c Jogador.cpp 

globais.o: globais.cpp globais.h
	g++ $(flags) -c globais.cpp

clean:
	rm *.o all exec
	
run:
	./all