# Modulo_kernel
Módulo do kernel linux desenvolvido na disciplina de Sistemas Operacionais 1.

EXECUÇÃO DO PROGRAMA:
- É aconselhável abrir três janelas do terminal para acompanhar a execução do servidor, do módulo kernel ( cliente ) e a saída dos módulos em execução.
- Para observar a saída dos módulos, é necessário inserir o seguinte comando no terminal: "sudo dmesg -w".
- Para o servidor, é necessário compilar com o comando "gcc -o server server.c" e executá-lo com o comando "./server".
- Já para o módulo, é necessário inserir o comando "make" para criá-lo, o qual executa um dos atalhos do Makefile disponibilizado. Em seguida, é 
necessário utilizar o comando "sudo insmod client.ko" para iniciar o funcionamento do módulo kernel.
- Já com o módulo funcionando, na aba do servidor, para cada tecla que for pressionada, o programa irá imprimir o caracter, assim como no terminal de mensagens dos módulos. O programa irá interromper a execução quando 1000 caracteres forem pressionados.
- Caso queira, para interromper a execução do módulo, é só inserir o comando "sudo insmod client.ko".

