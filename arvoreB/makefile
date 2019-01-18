siguel: ../ArqBin/ArqBin.o main.o ../Lista/lista.o arvoreB.o
	gcc ../ArqBin/ArqBin.o main.o ../Lista/lista.o arvoreB.o -lm -o siguel -g -pedantic -fstack-protector-all -std=c99

ArqBin.o:../ArqBin/ArqBin.c ../ArqBin/ArqBin.h
	gcc -c ../ArqBin/ArqBin.c -lm -o ../ArqBin/ArqBin.o -g -pedantic -fstack-protector-all -std=c99

arvoreB.o:../arvoreB/arvoreB.c ../arvoreB/arvoreB.h
	gcc -c ../arvoreB/arvoreB.c -lm -o ../arvoreB/arvoreB.o -g -pedantic -fstack-protector-all -std=c99


../Lista/lista.o:../Lista/lista.c ../Lista/lista.h
	gcc -c ../Lista/lista.c -lm -o ../Lista/lista.o -g -pedantic -fstack-protector-all -std=c99

main.o:main.c
	gcc -c main.c -lm -o main.o -g -pedantic -fstack-protector-all -std=c99

clean:
	rm main.o ../ArqBin/ArqBin.o siguel ../Lista/lista.o ../arvoreB/arvoreB.o
