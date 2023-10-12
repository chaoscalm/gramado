
#include "../gwsint.h"

struct taskbar_d  TaskBar;

struct start_menu_d StartMenu;
struct quick_launch_d QuickLaunch;


const char *startmenu_label = "Gramado";


// Taskbar
#define TB_BUTTON_PADDING  2
// 36
//#define TB_HEIGHT  40
#define TB_HEIGHT  (24+TB_BUTTON_PADDING+TB_BUTTON_PADDING)
//#define TB_BUTTON_PADDING  4
#define TB_BUTTON_HEIGHT  (TB_HEIGHT - (TB_BUTTON_PADDING*2))
#define TB_BUTTON_WIDTH  TB_BUTTON_HEIGHT
// #define TB_BUTTONS_MAX  8


//--------------

void __create_start_menu(void);
// Launch area
void __create_quick_launch_area(void);


//-----------------------------------------


void __create_start_menu(void)
{
// Colors for the taskbar and for the buttons.
    //unsigned int bg_color     = (unsigned int) get_color(csiTaskBar);
    unsigned int frame_color  = (unsigned int) get_color(csiTaskBar);
    unsigned int client_color = (unsigned int) get_color(csiTaskBar);

// ========================================
// Quick launch area buttons

    if ( (void*) taskbar_window == NULL ){
        printf("__create_start_menu: taskbar_window\n");
        exit(0);
    }
    if (taskbar_window->magic != 1234){
        printf("__create_start_menu: taskbar_window validation\n");
        exit(0);
    }

// ========================================
// Start menu button

    unsigned long sm_left= TB_BUTTON_PADDING;
    unsigned long sm_top = TB_BUTTON_PADDING;
    unsigned long sm_width = 
      ( QUICK_LAUNCH_AREA_PADDING -
        TB_BUTTON_PADDING -
        TB_BUTTON_PADDING );
    unsigned long sm_height = (taskbar_window->height -
        TB_BUTTON_PADDING -
        TB_BUTTON_PADDING );
    struct gws_window_d *sm_window;

    sm_window = 
        (struct gws_window_d *) CreateWindow ( 
            WT_BUTTON, 0, 1, 1, 
            startmenu_label,
            sm_left, sm_top, sm_width, sm_height,   
            taskbar_window, 
            0, 
            frame_color,     // frame color 
            client_color );  // client window color

    if ( (void *) sm_window == NULL ){
        gwssrv_debug_print ("__create_start_menu: sm_window\n"); 
        printf             ("__create_start_menu: sm_window\n");
        exit(1);
    }
    if ( sm_window->used != TRUE || sm_window->magic != 1234 ){
        gwssrv_debug_print ("__create_start_menu: sm_window validation\n"); 
        printf             ("__create_start_menu: sm_window validation\n");
        exit(1);
    }

// Register the button.
    StartMenu.wid = RegisterWindow(sm_window);
    if (StartMenu.wid<0){
        gwssrv_debug_print ("__create_start_menu: Couldn't register sm_window\n");
        printf             ("__create_start_menu: Couldn't register sm_window\n");
        exit(1);
    }

// Save
    taskbar_startmenu_button_window = sm_window;

    StartMenu.initialized = TRUE;
}


void __create_quick_launch_area(void)
{

// Colors for the taskbar and for the buttons.
    //unsigned int bg_color     = (unsigned int) get_color(csiTaskBar);
    unsigned int frame_color  = (unsigned int) get_color(csiTaskBar);
    unsigned int client_color = (unsigned int) get_color(csiTaskBar);
// ========================================
// Quick launch area buttons

    if ( (void*) taskbar_window == NULL ){
        printf("__create_quick_launch_area: taskbar_window\n");
        exit(0);
    }
    if (taskbar_window->magic != 1234){
        printf("__create_quick_launch_area: taskbar_window validation\n");
        exit(0);
    }

// ===================================
// button box:
// ===================================
// Clean the button list and the pid list.
    register int b=0;
    for (b=0; b<QL_BUTTON_MAX; b++)
    {
        QuickLaunch.buttons[b]=0;
        // ...
    };
    QuickLaunch.buttons_count=0;

    //unsigned long Space = TB_BUTTON_PADDING;   //4;
    //unsigned long b_width  = TB_BUTTON_WIDTH;    //(8*10);
    //unsigned long b_height = TB_BUTTON_HEIGHT;   //40-(Space*2);
    //unsigned long b_left   = TB_BUTTON_PADDING;  //Space;
    //unsigned long b_top    = TB_BUTTON_PADDING;  //Space;

    unsigned long b_left   = 0; 
    unsigned long b_top    = TB_BUTTON_PADDING;

    //unsigned long b_width  = TB_BUTTON_WIDTH;
    //unsigned long b_height = TB_BUTTON_HEIGHT;
    //unsigned long b_width  = (unsigned long)(tb_height -8);
    //unsigned long b_height = (unsigned long)(tb_height -8);
    unsigned long b_width  = (unsigned long)(taskbar_window->height -
        TB_BUTTON_PADDING -
        TB_BUTTON_PADDING );
    unsigned long b_height = (unsigned long)(taskbar_window->height -
        TB_BUTTON_PADDING -
        TB_BUTTON_PADDING );

    register int i=0;         //iterator
    int nbuttons=4;  //quantidade de botões na lista    
    struct gws_window_d *tmp_button;
    int tmp_wid=-1;
    char button_label[32];

// -----------------------------
// Quick launch area.
// Creating n buttons in the taskbar.
// #todo: We can make this options configurable.

    for (i=0; i<nbuttons; i++){

    b_left = 
        QUICK_LAUNCH_AREA_PADDING +
        TB_BUTTON_PADDING + ( (TB_BUTTON_PADDING*i) + (b_width*i) );

    itoa(i,button_label);
    button_label[2] = 0;
    
    tmp_button = 
        (struct gws_window_d *) CreateWindow ( 
            WT_BUTTON, 0, 1, 1, 
            button_label,  //string  
            b_left, b_top, b_width, b_height,   
            taskbar_window, 0, 
            frame_color,     // frame color 
            client_color );  // client window color

    if ( (void *) tmp_button == NULL ){
        gwssrv_debug_print ("__create_quick_launch_area: tmp_button\n"); 
        printf             ("__create_quick_launch_area: tmp_button\n");
        exit(1);
    }
    if ( tmp_button->used != TRUE || tmp_button->magic != 1234 ){
        gwssrv_debug_print ("__create_quick_launch_area: tmp_button validation\n"); 
        printf             ("__create_quick_launch_area: tmp_button validation\n");
        exit(1);
    }

// Register the button.
    tmp_wid = RegisterWindow(tmp_button);
    if (tmp_wid<0){
        gwssrv_debug_print ("__create_quick_launch_area: Couldn't register button\n");
        printf             ("__create_quick_launch_area: Couldn't register button\n");
        exit(1);
    }

/*
    if (i==0){
        taskbar_startmenu_button_window = tmp_button;
    }
*/

//save
    // id de janelas.
    QuickLaunch.buttons[i] = (int) tmp_wid;
    // ponteiros de estruturas de janelas do tipo botão.
    //tb_windows[i] = (unsigned long) tmp_button;

    // Número de botões criados.
    QuickLaunch.buttons_count++;
    };

    QuickLaunch.initialized = TRUE;
}



// Taskbar
// Display server's widget.
// Cria a barra na parte de baixo da tela.
// com 4 tags.
// os aplicativos podem ser agrupados por tag.
// quando uma tag eh acionada, o wm exibe 
// todos os aplicativos que usam essa tag.
void create_taskbar(int issuper, int show)
{
// Called by initGUI() in main.c

    unsigned long w = gws_get_device_width();
    unsigned long h = gws_get_device_height();
    int wid = -1;
// Colors for the taskbar and for the buttons.
    unsigned int bg_color     = (unsigned int) get_color(csiTaskBar);
    //unsigned int frame_color  = (unsigned int) get_color(csiTaskBar);
    //unsigned int client_color = (unsigned int) get_color(csiTaskBar);

    unsigned long tb_height = METRICS_TASKBAR_DEFAULT_HEIGHT;

    if (w==0 || h==0){
        gwssrv_debug_print ("create_taskbar: w h\n");
        printf             ("create_taskbar: w h\n");
        exit(1);
    }

    TaskBar.initialized = FALSE;
    //TaskBar.is_super = FALSE;
    //TaskBar.is_super = TRUE;
    TaskBar.is_super = (int) issuper;
    if (TaskBar.is_super != TRUE && TaskBar.is_super != FALSE)
    {
        TaskBar.is_super = FALSE;
    }

// Taskbar.
// Create  window.

    tb_height = METRICS_TASKBAR_DEFAULT_HEIGHT;
    if (TaskBar.is_super == TRUE){
        tb_height = METRICS_SUPERTITLEBAR_DEFAULT_HEIGHT;
    }

    //if (tb_height<40)
    if (tb_height<24){
        tb_height = 24;
    }
    if(tb_height >= h){
        tb_height = h-40;
    }

    unsigned long wLeft   = (unsigned long) 0;
    unsigned long wTop    = (unsigned long) (h-tb_height);
    unsigned long wWidth  = (unsigned long) w;
    unsigned long wHeight = (unsigned long) tb_height;  //40;

    TaskBar.left   = (unsigned long) wLeft;
    TaskBar.top    = (unsigned long) wTop;
    TaskBar.width  = (unsigned long) wWidth;
    TaskBar.height = (unsigned long) wHeight;

    taskbar_window = 
        (struct gws_window_d *) CreateWindow ( 
                                    WT_SIMPLE, 
                                    0, //style
                                    1, //status 
                                    1, //view
                                    "TaskBar",  
                                    wLeft, wTop, wWidth, wHeight,   
                                    gui->screen_window, 0, 
                                    bg_color, 
                                    bg_color );



// Struture validation
    if ( (void *) taskbar_window == NULL ){
        gwssrv_debug_print ("create_taskbar: taskbar_window\n"); 
        printf             ("create_taskbar: taskbar_window\n");
        exit(1);
    }
    if ( taskbar_window->used != TRUE || taskbar_window->magic != 1234 ){
        gwssrv_debug_print ("create_background: taskbar_window validation\n"); 
        printf             ("create_background: taskbar_window validation\n");
        exit(1);
    }

// Register the window.
    wid = (int) RegisterWindow(taskbar_window);
    if (wid<0){
        gwssrv_debug_print ("create_taskbar: Couldn't register window\n");
        printf             ("create_taskbar: Couldn't register window\n");
        exit(1);
    }

// wid
    taskbar_window->id = wid;
// Setup Window manager.
    WindowManager.taskbar = (struct gws_window_d *) taskbar_window;
// Show
    //flush_window(taskbar_window);

    TaskBar.initialized = TRUE;

// #debug

    //printf ("bar: %d %d %d %d\n",
    //    taskbar_window->left,
    //    taskbar_window->top,
    //    taskbar_window->width,
    //    taskbar_window->height );
    //refresh_screen();
    //while(1){}
    

//
// Start menu.
//

// Start menu.
    __create_start_menu();

//
// Quick launch area.
//

// Quick launch area.
    __create_quick_launch_area();

// Show
    if (show)
        flush_window_by_id(wid);
}


// Teremos mais argumentos
void wm_Update_TaskBar(char *string, int flush)
{
    if ( WindowManager.is_fullscreen == TRUE ){
        return;
    }
    if ( (void*) string == NULL ){
        return;
    }
    if (*string == 0){
        return;
    }
// TaskBar
    if (TaskBar.initialized != TRUE)
        return;
// Window
    if ( (void*) taskbar_window == NULL ){
        return;
    }
    if (taskbar_window->magic!=1234){
        return;
    }

// Redraw the bar.
// Redraw the buttons.
    //redraw_window_by_id(taskbar_window->id,TRUE);
    redraw_window_by_id(taskbar_window->id,FALSE);

    //redraw_window_by_id(
    //    __taskbar_startmenu_button_window->id,TRUE);
    //redraw_window(taskbar_window,TRUE);
    //redraw_window(__taskbar_startmenu_button_window,TRUE);

    //redraw_window_by_id(StartMenu.wid,TRUE);
    redraw_window_by_id(StartMenu.wid,FALSE);
    
// Redraw, all the valid buttons in the list.
    register int i=0;
    int wid=0;
    for (i=0; i<QL_BUTTON_MAX; i++)
    {
        if (QuickLaunch.buttons[i] != 0)
        {
            wid = (int) QuickLaunch.buttons[i];
            redraw_window_by_id(wid,FALSE);
            //__draw_button_mark_by_wid(wid,i);
        }
    };

//
// Strings
//

// String info

    // fg color
    unsigned int string_color = 
        (unsigned int) get_color(csiTaskBarTextColor);

    // String 1 left (Text)
    unsigned long string1_left = 
        (unsigned long) (taskbar_window->width - 100);

    // String 2 left (Separator)
    unsigned long string2_left = 
        (unsigned long) (string1_left - (8*2));

    // String top
    unsigned long string_top = 
        ((taskbar_window->height-8) >> 1);  //8 

    // String size
    size_t string_size = (size_t) strlen(string);

// ----------------------------
// String 2: The separator '|'.
    dtextDrawText(
        taskbar_window, 
        string2_left, 
        string_top, 
        string_color, 
        "|" );

// ----------------------------
// String 1: Draw the text.
// Less than 10 chars. (8*10)=80, the left is -100.
    if (string_size <= 10)
    {
        // String 1
        dtextDrawText(
            taskbar_window,
            string1_left, string_top, string_color, string );
    }

// Show the window
    if (flush == TRUE){
        flush_window(taskbar_window);
    }
}

void swamp_update_taskbar(char *string, int flush)
{
    if ((void*) string == NULL)
        return;
    wm_Update_TaskBar(string,flush);
}







