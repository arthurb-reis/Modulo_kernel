#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

//Define a porta e o tamanho do buffer
#define SERVER_PORT 9999
#define BUFFER_SIZE 1024

//Função principal
int main() {
    //Declara variáveis
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE];

    //Inicia servidor
    printf("Iniciando o servidor...\n");

    // Criação do socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){ //Socket não criado
        perror("Erro ao criar o socket");
        exit(1);
    }

    // Configuração do endereço do servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Associação do socket com o endereço do servidor
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("Erro ao fazer a associação");
        exit(1);
    }

    // Aguardando conexões
    if (listen(sockfd, 5) < 0){
        perror("Erro ao aguardar conexões");
        exit(1);
    }

    printf("Aguardando conexões...\n");
    
    // Aceitando uma nova conexão
    client_len = sizeof(client_addr);
    int client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
    if (client_sockfd < 0){
        perror("Erro ao aceitar conexão");
        exit(1);
    }

    printf("Cliente conectado\n");

    // Loop principal do servidor
    int i = 0;
    while (i!=1000){  //recebe 1000 caracteres do cliente

        // Recebendo a mensagem do cliente
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t ret = recv(client_sockfd, buffer, BUFFER_SIZE - 1, 0);
        if (ret < 0)
        {
            perror("Erro ao receber mensagem do cliente");
            exit(1);
        }

        printf("Mensagem recebida do cliente: %s\n", buffer);
      
        i++;
    }
    
    // Fechando o socket do cliente
    close(client_sockfd);

    // Fechando o socket do servidor
    close(sockfd);

    return 0;
}

