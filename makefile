siguel: Anotacao/anotacao.o Circulo/circulo.o Config/config.o Estabelecimento/estabelecimento.o Fila/fila.o HashTable/hashtable.o Hidrante/hidrante.o Item/item.o KDTREE/kdtree.o Lista/lista.o Main/main.o Pessoa/pessoa.o Quadra/quadra.o Radio-Base/radio-base.o Retangulo/retangulo.o Semaforo/semaforo.o Comands/Geo/executeGeo.o Comands/Qry/executeQry.o Comands/Ec/executeEc.o Comands/Pm/executePm.o Comands/Geo/comandsGeo.o Comands/Ec/comandsEc.o Comands/Pm/comandsPm.o Comands/Qry/comandsQry.o Grafos/GrafoD.o Comands/Via/executeVia.o Comands/Via/comandsVia.o Registrador/registrador.o Carro/carro.o
	gcc Anotacao/anotacao.o Circulo/circulo.o Config/config.o Estabelecimento/estabelecimento.o Fila/fila.o HashTable/hashtable.o Hidrante/hidrante.o Item/item.o KDTREE/kdtree.o Lista/lista.o Main/main.o Pessoa/pessoa.o Quadra/quadra.o Radio-Base/radio-base.o Retangulo/retangulo.o Semaforo/semaforo.o Comands/Geo/executeGeo.o Comands/Qry/executeQry.o Comands/Ec/executeEc.o Comands/Pm/executePm.o Comands/Geo/comandsGeo.o Comands/Ec/comandsEc.o Comands/Pm/comandsPm.o Comands/Qry/comandsQry.o Grafos/GrafoD.o Comands/Via/executeVia.o Comands/Via/comandsVia.o Registrador/registrador.o Carro/carro.o -lm -o siguel -g -pedantic -fstack-protector-all -std=c99

Anotacao/anotacao.o:Anotacao/anotacao.c Anotacao/anotacao.h
	gcc -c Anotacao/anotacao.c -lm -o Anotacao/anotacao.o -g -pedantic -fstack-protector-all -std=c99

Circulo/circulo.o:Circulo/circulo.c Circulo/circulo.h
	gcc -c Circulo/circulo.c -lm -o Circulo/circulo.o -g -pedantic -fstack-protector-all -std=c99

Config/config.o:Config/config.c Config/config.h
	gcc -c Config/config.c -lm -o Config/config.o -g -pedantic -fstack-protector-all -std=c99

Estabelecimento/estabelecimento.o:Estabelecimento/estabelecimento.c Estabelecimento/estabelecimento.h
	gcc -c Estabelecimento/estabelecimento.c -lm -o Estabelecimento/estabelecimento.o -g -pedantic -fstack-protector-all -std=c99

Fila/fila.o:Fila/fila.c Fila/fila.h
	gcc -c Fila/fila.c -lm -o Fila/fila.o -g -pedantic -fstack-protector-all -std=c99

HashTable/hashtable.o:HashTable/hashtable.c HashTable/hashtable.h
	gcc -c HashTable/hashtable.c -lm -o HashTable/hashtable.o -g -pedantic -fstack-protector-all -std=c99

Hidrante/hidrante.o:Hidrante/hidrante.c Hidrante/hidrante.h
	gcc -c Hidrante/hidrante.c -lm -o Hidrante/hidrante.o -g -pedantic -fstack-protector-all -std=c99

Item/item.o:Item/item.c Item/item.h
	gcc -c Item/item.c -lm -o Item/item.o -g -pedantic -fstack-protector-all -std=c99

KDTREE/kdtree.o:KDTREE/kdtree.c KDTREE/kdtree.h
	gcc -c KDTREE/kdtree.c -lm -o KDTREE/kdtree.o -g -pedantic -fstack-protector-all -std=c99

Lista/lista.o:Lista/lista.c Lista/lista.h
	gcc -c Lista/lista.c -lm -o Lista/lista.o -g -pedantic -fstack-protector-all -std=c99

Main/main.o:Main/main.c
	gcc -c Main/main.c -lm -o Main/main.o -g -pedantic -fstack-protector-all -std=c99

Pessoa/pessoa.o:Pessoa/pessoa.c Pessoa/pessoa.h
	gcc -c Pessoa/pessoa.c -lm -o Pessoa/pessoa.o -g -pedantic -fstack-protector-all -std=c99

Quadra/quadra.o:Quadra/quadra.c Quadra/quadra.h
	gcc -c Quadra/quadra.c -lm -o Quadra/quadra.o -g -pedantic -fstack-protector-all -std=c99

Radio-Base/radio-base.o:Radio-Base/radio-base.c Radio-Base/radio-base.h
	gcc -c Radio-Base/radio-base.c -lm -o Radio-Base/radio-base.o -g -pedantic -fstack-protector-all -std=c99

Retangulo/retangulo.o:Retangulo/retangulo.c Retangulo/retangulo.h
	gcc -c Retangulo/retangulo.c -lm -o Retangulo/retangulo.o -g -pedantic -fstack-protector-all -std=c99

Semaforo/semaforo.o:Semaforo/semaforo.c Semaforo/semaforo.h
	gcc -c Semaforo/semaforo.c -lm -o Semaforo/semaforo.o -g -pedantic -fstack-protector-all -std=c99

Sort/sorts.o: Sort/sorts.c Sort/sorts.h
	gcc -c Sort/sorts.c -lm -o Sort/sorts.o -g -pedantic -fstack-protector-all -std=c99

Comands/Geo/executeGeo.o: Comands/Geo/executeGeo.c Comands/Geo/executeGeo.h
	gcc -c Comands/Geo/executeGeo.c -lm -o Comands/Geo/executeGeo.o -g -pedantic -fstack-protector-all -std=c99

Comands/Geo/comandsGeo.o: Comands/Geo/comandsGeo.c Comands/Geo/comandsGeo.h
	gcc -c Comands/Geo/comandsGeo.c -lm -o Comands/Geo/comandsGeo.o -g -pedantic -fstack-protector-all -std=c99

Comands/Qry/executeQry.o: Comands/Qry/executeQry.c Comands/Qry/executeQry.h
	gcc -c Comands/Qry/executeQry.c -lm -o Comands/Qry/executeQry.o -g -pedantic -fstack-protector-all -std=c99

Comands/Qry/comandsQry.o: Comands/Qry/comandsQry.c Comands/Qry/comandsQry.h
	gcc -c Comands/Qry/comandsQry.c -lm -o Comands/Qry/comandsQry.o -g -pedantic -fstack-protector-all -std=c99

Comands/Ec/executeEc.o: Comands/Ec/executeEc.c Comands/Ec/executeEc.h
	gcc -c Comands/Ec/executeEc.c -lm -o Comands/Ec/executeEc.o -g -pedantic -fstack-protector-all -std=c99

Comands/Ec/comandsEc.o: Comands/Ec/comandsEc.c Comands/Ec/comandsEc.h
	gcc -c Comands/Ec/comandsEc.c -lm -o Comands/Ec/comandsEc.o -g -pedantic -fstack-protector-all -std=c99

Comands/Pm/executePm.o: Comands/Pm/executePm.c Comands/Pm/executePm.h
	gcc -c Comands/Pm/executePm.c -lm -o Comands/Pm/executePm.o -g -pedantic -fstack-protector-all -std=c99

Comands/Pm/comandsPm.o: Comands/Pm/comandsPm.c Comands/Pm/comandsPm.h
	gcc -c Comands/Pm/comandsPm.c -lm -o Comands/Pm/comandsPm.o -g -pedantic -fstack-protector-all -std=c99

Comands/Via/executeVia.o: Comands/Via/executeVia.c Comands/Via/executeVia.h
	gcc -c Comands/Via/executeVia.c -lm -o Comands/Via/executeVia.o -g -pedantic -fstack-protector-all -std=c99

Comands/Via/comandsVia.o: Comands/Via/comandsVia.c Comands/Via/comandsVia.h
	gcc -c Comands/Via/comandsVia.c -lm -o Comands/Via/comandsVia.o -g -pedantic -fstack-protector-all -std=c99

Grafos/GrafoD.o: Grafos/GrafoD.c Grafos/GrafoD.h
	gcc -c Grafos/GrafoD.c -lm -o Grafos/GrafoD.o -g -pedantic -fstack-protector-all -std=c99

Registrador/registrador.o: Registrador/registrador.c Registrador/registrador.h
	gcc -c Registrador/registrador.c -lm -o Registrador/registrador.o -g -pedantic -fstack-protector-all -std=c99

Carro/carro.o: Carro/carro.c Carro/carro.h
	gcc -c Carro/carro.c -lm -o Carro/carro.o -g -pedantic -fstack-protector-all -std=c99

clean:
	rm Anotacao/anotacao.o Circulo/circulo.o Config/config.o Estabelecimento/estabelecimento.o Fila/fila.o HashTable/hashtable.o Hidrante/hidrante.o Item/item.o KDTREE/kdtree.o Lista/lista.o Main/main.o Pessoa/pessoa.o Quadra/quadra.o Radio-Base/radio-base.o Retangulo/retangulo.o Semaforo/semaforo.o Comands/Geo/executeGeo.o Comands/Qry/executeQry.o Comands/Ec/executeEc.o Comands/Pm/executePm.o Comands/Geo/comandsGeo.o Comands/Ec/comandsEc.o Comands/Pm/comandsPm.o Comands/Qry/comandsQry.o Grafos/GrafoD.o Comands/Via/executeVia.o Comands/Via/comandsVia.o Registrador/registrador.o Carro/carro.o siguel
	