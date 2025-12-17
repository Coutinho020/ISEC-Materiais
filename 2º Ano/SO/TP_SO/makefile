CC = gcc

all: controlador veiculo cliente

controlador: controlador.c
	$(CC) controlador.c -o controlador

veiculo: veiculo.c
	$(CC) veiculo.c -o veiculo

cliente: cliente.c
	$(CC) cliente.c -o cliente

clean:
	rm -f controlador veiculo cliente *.o