

#ifndef ____WM_H
#define ____WM_H    1

//
// Input support
//

int wmInputReader(void);
int wmInputReader2(void);
int wmSTDINInputReader(void);
unsigned long wmGetLastInputJiffie(int update);

void wmInitializeGlobals(void);

unsigned long 
wmProcedure(
    struct gws_window_d *window,
    int msg,
    unsigned long long1,
    unsigned long long2 );

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
void wm_update_desktop3(struct gws_window_d *top_window);

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


