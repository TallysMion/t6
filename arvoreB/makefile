siguel: ArqBin.o main.o ../Lista/lista.o arvoreB.o
	gcc ArqBin.o main.o ../Lista/lista.o arvoreB.o -lm -o siguel -g -pedantic -fstack-protector-all -std=c99

ArqBin.o:ArqBin.c ArqBin.h
	gcc -c ArqBin.c -lm -o ArqBin.o -g -pedantic -fstack-protector-all -std=c99

arvoreB.o:arvoreB.c arvoreB.h
	gcc -c arvoreB.c -lm -o arvoreB.o -g -pedantic -fstack-protector-all -std=c99


../Lista/lista.o:../Lista/lista.c ../Lista/lista.h
	gcc -c ../Lista/lista.c -lm -o ../Lista/lista.o -g -pedantic -fstack-protector-all -std=c99

main.o:main.c
	gcc -c main.c -lm -o main.o -g -pedantic -fstack-protector-all -std=c99

clean:
	rm main.o ArqBin.o siguel Lista/lista.o arvoreB.o
