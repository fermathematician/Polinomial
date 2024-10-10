projeto: polinomio.c projeto.c
	gcc -o projeto polinomio.c projeto.c

run: projeto
	./projeto

clean:
	rm -f projeto
