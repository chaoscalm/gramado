/*
 * File: main.c
 *     Simple virtual terminal.
 *     2021 - Created by Fred Nora.
 */
// #test
// For now it has a small embedded command line interpreter.
// The POSIX terminal interface.
// Raw or Canonical?
// See:
// https://www.gnu.org/software/libc/manual/html_node/Canonical-or-Not.html
// https://en.wikipedia.org/wiki/POSIX_terminal_interface
// https://en.wikipedia.org/wiki/Computer_terminal
// ...
// Connecting via AF_INET.
// tutorial example taken from. 
// https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
/*
    To make a process a TCP server, 
    you need to follow the steps given below −
    Create a socket with the socket() system call.
    Bind the socket to an address using the bind() system call. 
    For a server socket on the Internet, an address consists of a 
    port number on the host machine.
    Listen for connections with the listen() system call.
    Accept a connection with the accept() system call. 
    This call typically blocks until a client connects with the server.
    Send and receive data using the read() and write() system calls.
*/ 
// See:
// https://wiki.osdev.org/Message_Passing_Tutorial
// https://wiki.osdev.org/Synchronization_Primitives
// https://devblogs.microsoft.com/commandline/
// /windows-command-line-introducing-the-windows-pseudo-console-conpty/
// ...

#include <types.h>
//#include <sys/types.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/term0.h"


// see: terminal.c and term0.h.
extern struct terminal_d  Terminal;

int main(int argc, char *argv[])
{ 
    int Status = -1;

    debug_print ("terminal.bin:\n");

//
// #todo: Parse parameters.
//

    if (argc<1){
    }

// Initializing the structure.
    Terminal.initialized = FALSE;
    Terminal.pid = getpid();
    Terminal.uid = getuid();
    Terminal.gid = getgid();
    Terminal.esc = 0;
    Terminal.client_fd = 0;
    Terminal.main_window_id = 0;
    Terminal.client_window_id = 0;
    Terminal.left = 0;
    Terminal.top  = 0;
    Terminal.width = 50;
    Terminal.height = 50;
    Terminal.width_in_chars = 0;
    Terminal.height_in_chars = 0;
    // ...


    Status = (int) terminal_init();
    if (Status != 0)
        printf("main: Something is wrong\n");

    return 0;
}

