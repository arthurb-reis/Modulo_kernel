# Modulo_kernel
Módulo do kernel linux desenvolvido na disciplina de Sistemas Operacionais 1.

-É aconselhável abrir três janelas do terminal para acompanhar a execução do servidor, do módulo kernel ( cliente ) e a saída do módulo criado.
-Para observar a saída do módulo, é necessário inserir o seguinte comando no terminal : " sudo dmesg -w "
-Para o servidor, é necessário compilar pelo comando gcc -o server server.c e executá-lo com o comando ./server
-Já para o módulo, é necessário inserir o comando make para criá-lo, o qual executa um dos atalhos do Makefile disponibilizado. Em seguida, é 
necessário utilizar o comando sudo insmod server.ko para iniciar o funcionamento do módulo kernel. Caso 

