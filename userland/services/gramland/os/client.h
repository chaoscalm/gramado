
// client.h

#ifndef ____CLIENT_H
#define ____CLIENT_H    1

// Nesse arquivo fica a estrutura de cliente.
// Essa estrutura vai conter as informações
// e características dos clientes.

//
// Current
//

// Mandaremos as mensages para a fila de mensagens do cliente atual
// para isso o window server precisa constantemente ler sua fila de
// mensagens.
// O kernel alimenta a fila de mensagens do ws qunado tem um ws
// instalado.

// See: ____saved_current_client_fd in main.c
// int current_client;

struct gws_client_d
{
    int used;
    int magic;

    int id;
    char name[128];

// The overlapped window for this client.
    int window;
// A area ocupada pela janela
// pode ser do tamanho da janela ou ainda maior.
    int l;
    int t;
    int w;
    int h;

// Quando uma tag foi acionada
// e esse cliente foi exibido na tela.
    int is_visible;

// As 4 tags possivies
// TRUE = estamos nessa tad
// FALSE = nao estamos nessa tag.
    int tags[4];

// #todo
    unsigned long flags;

// Para qual versão do Gramado esse aplicativo foi feito.
// ex: 0x0101  (1.1)
    unsigned short gramado_version;

// Flags para gerenciamento de compatibilidade entre
// versões
    unsigned long compat_flags;

// maybe
// The main window of this client.
// We can send messages to this window.
    //struct gws_window_d *main_window;

    int is_connected;

    // host, display, screen
    struct gws_host_d     host;
    struct gws_display_d  display;
    struct gws_screen_d   screen;

    // Socket for this client.
    int fd;

// Client's PID and GID.
    pid_t pid;
    gid_t gid;

    int tid;

// Spin
// Lets count how many times this client
// is looking for the next event.
// It can be useful for changing the client's priority.

    unsigned long spin;

    // ...

// Um loop vai circular os clientes.
// se ele fizer parte de uma tag, entao ele sera exibido.
    struct gws_client_d *next;
};

// #todo: 
// Declare it in another place.
// Use external reference here.
struct gws_client_d  *serverClient;
struct gws_client_d  *currentClient;
// ...

// #todo: 
// Declare it in another place.
// Use external reference here.
// list
struct gws_client_d  *first_client;

// #todo: 
// Declare it in another place.
// Use external reference here.
#define SERVER_CLIENT_INDEX 0
#define CLIENT_COUNT_MAX 32
unsigned long connections[CLIENT_COUNT_MAX];

//
// == prototypes =============================
//

#endif    



