
// user.c

#include <kernel.h>

struct desktop_d  *CurrentDesktop;

int current_usersession=0;
int current_desktop=0;

//============================

// init_desktop_list:
// Inicializa o array de ponteiros de desktop.
void init_desktop_list(void)
{
    register int i=0;
    while (i<DESKTOP_COUNT_MAX){
        desktopList[i] = 0;
        i++; 
    };
}

/*
 * init_desktop:
 *     Inicializa o desktop 0.
 *     int ?
 */
void init_desktop(void)
{
    register int i=0;

    debug_print ("init_desktop:\n");
    //printf("init_desktop: Initializing..\n");

    desktops_count = 0;
// List
    init_desktop_list();

//
// Struct
//

    struct desktop_d  *desktop0;

// Creating the desktop0. 
    desktop0 = (void *) kmalloc( sizeof(struct desktop_d) );
    if ((void *) desktop0 == NULL){
        panic ("init_desktop: desktop0\n");
    }
    desktop0->id = 0;
    desktop0->used = TRUE;
    desktop0->magic = 1234;

    //todo: object

    desktops_count = 1;

    desktop0->lTail = 0;
    desktop0->lHead = 0;
    for (i=0; i<8; i++){
        desktop0->list[i] = 0;
    };

    desktop0->__init_process_pid   = (pid_t) -1;
    desktop0->__display_server_pid = (pid_t) -1;
    desktop0->__network_server_pid = (pid_t) -1;

    if ((void*) InitProcess != NULL)
    {
        if (InitProcess->magic == 1234)
            desktop0->__init_process_pid = (pid_t) InitProcess->pid;            
    }

// Registrando na lista
    desktopList[0] = (unsigned long) desktop0;

// RegisterDesktop (desktop0); 
    set_current_desktop(desktop0);  
}

void set_current_desktop (struct desktop_d *desktop)
{
    if ( (void *) desktop == NULL ){ 
        return; 
    }

    current_desktop = (int) desktop->id;
    CurrentDesktop = desktop;
}

void *get_current_desktop (void)
{

// Check limits.
    if ( current_desktop < 0 || current_desktop >= DESKTOP_COUNT_MAX )
    {
        return NULL;
    }

    return (void *) desktopList[current_desktop];
}

int get_current_desktop_id (void)
{
    return (int) current_desktop;
}

/*
 * RegisterDesktop:
 *     Registrando um desktop numa lista de desktops.
 *     @todo: Mudar para desktopRegisterDesktop(.). 
 */

int RegisterDesktop (struct desktop_d *d)
{
    int Offset = 0;

    if ( (void *) d == NULL ){
        debug_print ("RegisterDesktop: [FAIL] d\n");
        return (int) 1;  
    }

// #bugbug: 
// Pode aparacer um loop infinito aqui.
// #todo: usar for.

    while ( Offset < DESKTOP_COUNT_MAX )
    {
        if ( (void *) desktopList[Offset] == NULL )
        {
            desktopList[Offset] = (unsigned long) d;
            d->id = Offset;
            return 0;
        }
       Offset++;
    };

// Fail
    return (int) 1;
}

/*
 * CreateDesktop:
 *     Cria um desktop em uma window station.
 */
void *CreateDesktop (void)
{
    struct desktop_d *Current;
    struct desktop_d *Empty;
    int i=0;
    //... 

// #todo: 
// O usuário precisa de permissão pra criar desktops.
    Current = (void *) kmalloc( sizeof(struct desktop_d) );
    if ( (void *) Current == NULL ){
        panic ("CreateDesktop: Current\n");
    } else {

        memset( Current, 0, sizeof(struct desktop_d) );
        //continua...
    };

    while ( i < DESKTOP_COUNT_MAX )
    {
        Empty = (void *) desktopList[i];

        if ( (void *) Empty == NULL )
        {
            desktopList[i] = (unsigned long) Current;
            Current->id = i;
            return (void *) Current;
        }
        i++;
    };

    return NULL;
}



//==================================

// User Environment Manager (UEM)
// Segue uma lista de operações que poderão ser realizadas para configuração
// do ambiente gráfico do usuário. Obs: Nesse módulo, apenas chamaremos
// algumas funções primitivas. Todo o trabalho maior deve ficar para os
// servidores em user mode.

#define UEM_NULL 0
#define UEM_CHANGE_BACKGROUND  1
#define UEM_CHANGE_LOGO        2
#define UEM_CHANGE_COLORS      3
// ...

// Se há um usuário configurado 
// conforme registrado em arquivo de configuração.
// int userconfig_Status;


// see: user.h
struct user_info_d *RootUser;       // Super user
struct user_info_d *CurrentUser;    // Current user

// see: user.c
// user list:
// root user is the user '0'.
unsigned long userList[USER_COUNT_MAX];


int GetCurrentGroupId (void)
{
    return (int) current_group;
}

uid_t GetCurrentUserId(void)
{
    return (uid_t) current_user;
}

void SetCurrentUserId(uid_t user_id)
{
    if ( user_id < 0 || user_id >= USER_COUNT_MAX )
    {
        printf ("SetCurrentUserId: [FAIL]\n");
        return;
    }

    current_user = (uid_t) user_id;
}

int is_superuser(void)
{
    uid_t uid = -1;
    uid = (uid_t) GetCurrentUserId();
    if (uid == 0){
        return TRUE;
    }
    return FALSE;
}

int __getusername(char *buffer)
{
    char *login_buffer = (char *) buffer;

    if ( (void*) buffer == NULL ){
        debug_print ("__getusername: [FAIL] buffer\n");
        goto fail;
    }

// Estrutura default para informações sobre o host.
// 64 bytes
// host.h
    if ( (void *) CurrentUser != NULL )
    {
        strcpy( 
            login_buffer, 
            (const char *) CurrentUser->__username );
       
        return (int) CurrentUser->userName_len;
    }

fail:
    return (int) -1;
}

// __setusername:
// O novo nome está no buffer passado via argumento.
// Ele tem o limite de 64 bytes.
// Vamos colocar ele na estrutura de usuário.

int __setusername(const char *new_username)
{
    if ( (void*) new_username == NULL ){
        debug_print ("__setusername: [FAIL] new_username\n");
        goto fail;
    }

// Estrutura de usuário.
// #todo
// Where is this structure defined?
// 64 bytes

    if ( (void *) CurrentUser != NULL )
    {
        CurrentUser->userName_len = 
            (size_t) (strlen(new_username) + 1);
        strcpy( 
            CurrentUser->__username, 
            (const char *) new_username );
        return 0;
    }

fail:
    return (int) -1;
}


/*
 * CreateUser:
 *     Cria um usuário do computador.
 *     #importante: Quando criar um usuário tem que 
 * montar uma pasta para ele em /root/user/(name)
 * Se utilizar um usuário válido é só pegar os arquivos de 
 * configuração dentro da pasta.
 */

struct user_info_d *CreateUser(char *name, int type)
{
    struct user_info_d *New;
    int Index = 0;
    register int i=0;

// #bugbug
// We don't wanna kill the initialization 
// only for a wrong name.

    // #alert
    if ((void*) name == NULL){
        debug_print ("CreateUser: [FAIL] name\n");
        panic ("CreateUser: [FIXME] name is not valid\n");
    }

    // #alert
    if (*name == 0){
        debug_print ("CreateUser: [FAIL] *name\n");
        panic ("CreateUser: [FIXME] *name is not valid\n");
    }

// #todo
// We need to check the limits for the name size.
// Maybe copy the name into a local buffer.
// strlen(name);

// Structure.
    New = (void *) kmalloc( sizeof(struct user_info_d) ); 
    if ((void *) New == NULL){
        panic("CreateUser: New\n");
    }

    New->initialized = FALSE;

    New->used = TRUE;
    New->magic = 1234;
    New->userType = type; 
    New->path = NULL;

// Clear the name
    for (i=0; i<64; i++){
        New->__username[i]=0;
    };


// The name.
// The name size.
    if ((void*) name != NULL)
    {
        strcpy( New->__username, (const char *) name);
        New->userName_len = strlen(name);
            
            // #todo
            // Check limits for this size.
            // There is a standard definition for that size.
            //if ( New->userName_len >= ???? ){}
    }
 
//Session.
//Desktop.

    New->usessionId = current_usersession;
    New->desktopId  = current_desktop;
    
// Inicializando a lista de objetos permitidos.
// Proibindo tudo.
    for (i=0; i<128; i++){
        New->permissions[i]=0;
    };

    //Inicializa tokens. (rever)
    //New->k_token = KERNEL_TOKEN_NULL;
    //New->e_token = EXECUTIVE_TOKEN_NULL;
    //New->m_token = MICROKERNEL_TOKEN_NULL;
    //New->h_token = HAL_TOKEN_NULL;
    //...

// Procurando uma entrada livre na lista.
    Index=0;
    while ( Index < USER_COUNT_MAX )
    {
        if ((void *) userList[Index] == NULL)
        {
            // User Id. 
            New->userId = (uid_t) Index;
            userList[Index] = (unsigned long) New;
            // printf("CreateUser: Done.\n");
            New->initialized = TRUE;
            return (struct user_info_d *) New;
        }

        Index++;
    };

//Fail: 
//Fim do loop. 
//Não encontramos uma entrada livre.

fail:
    return NULL;
}


// Called by I_kmain() in kmain.c.
int userCreateRootUser(void)
{
    // Nothing yet!
    RootUser = NULL;
    CurrentUser = NULL;

// Ok, let's create the user structure for the root user.
// USER_NAME_ROOT
    RootUser = 
        (struct user_info_d *) CreateUser("root",USER_TYPE_INTERACTIVE);

    if ((void*) RootUser == NULL){
        printf("userCreateRootUser: RootUser\n");
    }
    if (RootUser->magic != 1234){
        printf("userCreateRootUser: RootUser validation\n");
    }

// User ID.
    if (RootUser->userId != 0){
        panic("userCreateRootUser: root is not 0\n");
    }


// #debug
// Print the username.
    printf("Username: {%s}\n",RootUser->__username);
    //refresh_screen();
    //while(1){}

// Lets associate the user structure and the fg console.
// #todo: We need a method for this routine.

    if (fg_console < 0 || fg_console > 3){
        panic("userCreateRootUser: Invalid fg_console\n");
    }
    if (CONSOLE_TTYS[fg_console].initialized != TRUE){
        panic("userCreateRootUser: fg_console not initialized\n");
    }
    CONSOLE_TTYS[fg_console].user_info = 
        (struct user_info_d *) RootUser;

// Set the current user.
// We need a method for this.
    CurrentUser = (struct user_info_d *) RootUser;

// Set the current user ID.
    SetCurrentUserId(CurrentUser->userId);

    int isSuper = is_superuser();
    if ( isSuper != TRUE )
        panic("userCreateRootUser: Not super user\n");

// Done
    return TRUE;
fail:
    refresh_screen();
    return FALSE;
}

int User_initialize(void)
{
    debug_print("User_initialize:\n");

    current_user = 0;

// User session,  desktop, 
    current_usersession  = 0;
    current_desktop      = 0;

// Initialize user info structure
    printf ("User_initialize: init_user_info\n");
    //init_user_info ();   

//
// Security
//

// Initialize User Session, and Desktop.
// user section
    //printf ("User_initialize: initializing user session\n");
    //init_user_session();

    // desktop
    printf ("User_initialize: initializing desktop\n");   
    init_desktop();

    //debug_print("User_initialize: done\n");
    return 0;
}

int init_logon_manager (void)
{
// #todo
// #bugbug

    debug_print("init_logon_manager: [TODO FIXME]\n");

// #bugbug
// Is it the first time? Or not?

    gui = (void *) kmalloc( sizeof(struct gui_d) );
    if ((void *) gui == NULL){
        panic("init_logon_manager: [FAIL] gui\n");
    }

//
// TTY
//

// tty support.
// As mensagens do kernel precisam usar esses parametros.
// o kernel usa a tty0.

     // Limpa a lista
     printf ("init_logon_manager: Initializing tty module\n");
     //tty_init_module();

     // Limpa a lista de terminais virtuais tamb�m.
     printf ("init_logon_manager: Initializing vt module\n");
     //vt_init_module();

// See: userenv.c
    User_initialize();

// See: ws.h
// hostname:Displaynumber.Screennumber
// gramado:0.0

// display and screen
    current_display = 0;
    current_screen  = 0;

// #test
// Mostrando as mensagens antes de pintarmos a primeira janela.

    //#debug
    //breakpoint
    //refresh_screen();
    //while(1){}

    // ...

    return 0;
}

//-------------

int init_logoff (int mode)
{
    return 0;
}

// See: gpid.h
int register_logoff_process (pid_t pid)
{
    if (pid<0 || pid >= PROCESS_COUNT_MAX ){
        debug_print("register_logoff_process: pid fail\n");
        return -1;
    }
// ??
// Global variable.
    if (__gpidLogoff != 0){
        debug_print("register_logoff_process:\n");
        return -1;
    }

    __gpidLogoff = (pid_t) pid;

    return 0;
}









