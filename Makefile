hepsi: program calistir

program: Gen.o Kromozom.o main.o 
		g++ ./lib/main.o ./lib/Gen.o ./lib/Kromozom.o -o ./bin/program.exe
Gen.o:
		g++ -I ./include/ -c ./src/Gen.cpp -o ./lib/Gen.o
Kromozom.o:
		g++ -I ./include/ -c ./src/Kromozom.cpp -o ./lib/Kromozom.o
main.o:
		g++ -I ./include/ -c ./src/main.cpp -o ./lib/main.o

calistir:
		 ./bin/program.exe