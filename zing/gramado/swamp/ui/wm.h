
// wm.h

#ifndef ____WM_H
#define ____WM_H    1


// Layouts examples
// tiled, monocle and floating layouts
// Used in WindowManager.mode

#define WM_MODE_TILED       1
#define WM_MODE_OVERLAPPED  2
#define WM_MODE_MONO        3
// ...

struct taskbar_d
{
    int initialized;

    unsigned long left;
    unsigned long top;
    unsigned long height;
    unsigned long width;

    int is_super;  // Higher
    // ...
};
extern struct taskbar_d  TaskBar;

// Start menu
struct start_menu_d
{
    int initialized;
    int wid;
    int is_created;
    int is_selected;   // Focus
    int is_visible;  // Pressed
};
extern struct start_menu_d StartMenu;

// Quick launch area
// default left position.
#define QUICK_LAUNCH_AREA_PADDING  80
#define QL_BUTTON_MAX  4
struct quick_launch_d
{
    int initialized;
// Número de botões efetivamente criados.
    int buttons_count;
// List of buttons. (wid)
    int buttons[QL_BUTTON_MAX];
};
extern struct quick_launch_d QuickLaunch;


// ===============================================================
// #todo
// All the application windows
// are gonna have a offscreen surface,
// and then the compositor is gonna
// copy them all into the backbuffer.

struct desktop_composition_d
{
    int initialized;
    int is_enabled;
// Transparent window frames.
    int use_transparence;
// 2D visual effects associated with the composition method.
    int use_visual_effects;
    // ...
};

struct gws_container_d
{
    unsigned long left;
    unsigned long top;
    unsigned long width;
    unsigned long height;
};


// The window manager global structure.
struct gws_windowmanager_d
{
    int initialized;

// The window manager mode:
// 1: tiling.
// 2: overlapped.
// ...
    int mode;

// Tiling orientation.
// 1=vertical 0=horizontal
    int vertical;

// #todo
// Maybe we can create more containers,
// and shrink the body container 'wa'.
    //struct gws_container_d icon_area;

    unsigned long frame_counter;
    //unsigned long jiffies;
    int fps;

// Background
    unsigned int default_background_color;
    unsigned int custom_background_color;
    int has_custom_background_color;

// Wallpaper
// #todo: Create a wallpaper structure?
    int has_wallpaper;

// Window stack
// Quando uma janela foi invalidada, significa que ela foi pintada e que
// precisa receber o refesh, mas também pode significar
// que outras janelas foram afetadas pelo pintura da janela.
// Nesse caso precisado repintar a janelas.
// Se tiver uma janela em fullscreen então pintamos, invalidamos
// seu retângulo e validamos todos os outros.

// Windows

    struct gws_window_d *root;
    struct gws_window_d *taskbar;
    struct gws_window_d *fullscreen_window;
    // ...

    //int is_super_taskbar;

// A area de cliente de uma janela sera mostrada
// na tela toda e essa flag sera acionada.
// Com essa flag acionada a barra de tarefas nao sera exibida.
// fullscreen_window sera a janela usada.
// #todo: Create a structure for fullscreen support?
    int is_fullscreen;

// The 'Working Area'.
// The screen size, less the taskbar.
    struct gws_container_d  wa;

// Theme support
// TRUE = Using a loadable theme.
// FALSE = We are not using any theme at all.
// #todo: Create a theme structure?
    int has_theme;
    // ...

// #todo
// All the application windows
// are gonna have a offscreen surface,
// and then the compositor is gonna
// copy them all into the backbuffer.
    struct desktop_composition_d comp;
};

// Global main structure.
// Not a pointer.
extern struct gws_windowmanager_d  WindowManager;



// =========================================


//
// Taskbar
//

void create_taskbar(int issuper, int show);


//
// Input support
//

int xxGetAndProcessSystemEvents(void);
int wmInputReader(void);
int wmInputReader2(void);
int wmSTDINInputReader(void);


void wmInitializeGlobals(void);
unsigned long wmGetLastInputJiffie(int update);
void wm_Update_TaskBar( char *string, int flush );

// Associa a estrutura de janela
// com uma estrutura de cliente. 
// see: wm.c
int wmBindWindowToClient(struct gws_window_d *w);

void wm_update_desktop(int tile, int show);
void 
wm_update_desktop2(
    struct gws_window_d *last_window,
    int tile );
void wm_update_desktop3(struct gws_window_d *new_top_window);

// Update window.
void wm_update_window_by_id(int wid);
void wm_update_active_window(void);

// Fullscreen mode.
void wm_enter_fullscreen_mode(void);
void wm_exit_fullscreen_mode(int tile);

// list support
// not tested yet
void wm_add_window_into_the_list(struct gws_window_d *window);
void wm_rebuild_list(void);

void wm_remove_window_from_list_and_kill(struct gws_window_d *window);


#endif   


