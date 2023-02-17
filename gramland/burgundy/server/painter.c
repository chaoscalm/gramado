

#include "gwsint.h"

static void __draw_button_mark_by_wid( int wid, int button_number );
//
//===================================================================
//

// Here we're gonna redraw the given window
// and invalidate it.
int 
update_window ( 
    struct gws_window_d *window, 
    unsigned long flags )
{
    if ( (void*) window == NULL )
        return -1;

    return (int) redraw_window(window,flags);
}


// Clear the window
// Repaint it using the default background color.
// Only valid for WT_SIMPLE.
// #todo
// A transparent window inherits its parent's background 
// for this operation.
int clear_window_by_id(int wid, unsigned long flags)
{
    struct gws_window_d *w;

// wid
    if (wid<0 || wid>=WINDOW_COUNT_MAX)
        return -1;
// structure validation
    w = (void*) windowList[wid];
    if( (void*) w == NULL )
        return -1;
    if(w->magic!=1234)
        return -1;

    if (w->type != WT_SIMPLE)
        return -1;

    redraw_window(w,flags);
    return 0;
}




// pinta um retangulo no botao
// indicando que o app esta rodando.
static void __draw_button_mark_by_wid( int wid, int button_number )
{
    struct gws_window_d *w;
    
//#todo: max limit
    if (wid<0){
        return;
    }
    if ( button_number<0 || button_number>3 ){
        return;
    }
// Window
    w = (struct  gws_window_d *) windowList[wid];
    if ( (void*) w == NULL ){
        return;
    }
    if (w->magic!=1234){
        return;
    }

    rectBackbufferDrawRectangle ( 
        (w->left +3), 
        (w->top +4), 
        (w->width -8), 
        2, 
        COLOR_RED, 
        FALSE,  //refresh
        0 );    //rop_flags
}


// WORKER
// Paint button borders.
// Called by doCreateWindow
// >>> No checks
// IN: window, color, color, color, color.
// color1: left,top
// color2: right, bottom
// #check
// This routine is calling the kernel to paint the rectangle.
void 
__draw_button_borders(
    struct gws_window_d *w,
    unsigned int color1,
    unsigned int color2,
    unsigned int color2_light,
    unsigned int outer_color )
{
// #test
// Size in pizels de apenas 1/3 de todo o size.
    unsigned long BorderSize = 1;
// Isso deve ser o total.
    //window->border_size = ?

    //debug_print("__draw_button_borders:\n");

// This is the window for relative positions.
    if ( (void*) w == NULL ){
        return;
    }
    if (w->magic!=1234){
        return;
    }

//  ____
// |
//
// board1, borda de cima e esquerda.

// Cima
// top, top+1, top+2
    rectBackbufferDrawRectangle ( 
        w->left+1, 
        w->top, 
        w->width-2,
        BorderSize, 
        outer_color, TRUE,0 );
    rectBackbufferDrawRectangle ( 
        w->left+1, 
        w->top+1, 
        w->width-2, 
        BorderSize, 
        color1, TRUE,0 );
    rectBackbufferDrawRectangle ( 
        w->left+1+1, 
        w->top+1+1,
        w->width-4, 
        BorderSize, 
        color1, TRUE,0 );

// Esq
// left, left+1, left+2
    rectBackbufferDrawRectangle ( 
        w->left, 
        w->top+1, 
        BorderSize, 
        w->height-2,
        outer_color, TRUE,0 );
    rectBackbufferDrawRectangle ( 
        w->left+1, 
        w->top+1, 
        BorderSize, 
        w->height-2,
        color1, TRUE,0 );
    rectBackbufferDrawRectangle ( 
        w->left+1+1, 
        w->top+1+1, 
        BorderSize, 
        w->height-4,
        color1, TRUE,0 );

//  
//  ____|
//
// board2, borda direita e baixo.

// Dir
// right-3, right-2, right-1
    rectBackbufferDrawRectangle ( 
        ((w->left) + (w->width) -1), 
        w->top+1, 
        BorderSize, 
        w->height-2, 
        outer_color, TRUE, 0 );
    rectBackbufferDrawRectangle ( 
        ((w->left) + (w->width) -1 -1), 
        w->top+1, 
        BorderSize, 
        w->height-2, 
        color2, TRUE, 0 );
    rectBackbufferDrawRectangle ( 
        ((w->left) + (w->width) -1 -1 -1), 
        w->top+1+1, 
        BorderSize, 
        w->height-4, 
        color2_light, TRUE, 0 );


// Baixo
// bottom-1, bottom-2, bottom-3
    rectBackbufferDrawRectangle ( 
        w->left+1, 
        ( (w->top) + (w->height) -1 ),  
        w->width-2, 
        BorderSize, 
        outer_color, TRUE, 0 );
    rectBackbufferDrawRectangle ( 
        w->left+1, 
        ( (w->top) + (w->height) -1 -1),  
        w->width-2, 
        BorderSize, 
        color2, TRUE, 0 );
    rectBackbufferDrawRectangle ( 
        w->left+1+1, 
        ( (w->top) + (w->height) -1 -1 -1),  
        w->width-4, 
        BorderSize, 
        color2_light, TRUE, 0 );
}

// worker:
// Draw the border of edit box and overlapped windows.
// >> no checks
// #check
// This routine is calling the kernel to paint the rectangle.
void 
__draw_window_border( 
    struct gws_window_d *parent, 
    struct gws_window_d *window )
{

    if ( (void*) parent == NULL ){
        return;
    }
    if ( (void*) window == NULL ){
        return;
    }

// #todo
// Is it possitle to test the validation here?

// --------------------

    if (window->active == TRUE){
        window->border_size = 2;
    }
    if (window->active != TRUE){
        window->border_size = 1;
    }


// Editbox
    if ( window->type == WT_EDITBOX || 
         window->type == WT_EDITBOX_MULTIPLE_LINES )
    {
        // border size:
        // #todo: it can't be hardcoded,
        // We're gonna have themes.
        if (window->focus == TRUE)
        {
            window->border_size=2;
            //window->border_color1 = COLOR_BLACK;
        }
        if (window->focus == FALSE)
        {
            window->border_size=1;
            //window->border_color1 = 0;
        }

        // top
        rectBackbufferDrawRectangle( 
            window->left, 
            window->top, 
            window->width, 
            window->border_size, 
            window->border_color1, 
            TRUE, 
            0 );
        // left
        rectBackbufferDrawRectangle( 
            window->left, 
            window->top, 
            window->border_size, 
            window->height, 
            window->border_color1, 
            TRUE, 
            0 );
        // right
        rectBackbufferDrawRectangle( 
            (window->left + window->width - window->border_size), 
            window->top,  
            window->border_size, 
            window->height, 
            window->border_color2, 
            TRUE, 
            0 );
        // bottom
        rectBackbufferDrawRectangle ( 
            window->left, 
            (window->top + window->height - window->border_size), 
            window->width, 
            window->border_size, 
            window->border_color2, 
            TRUE, 
            0 );
        
        // #test
        // Subtract border size.
        //window->left   += window->border_size;
        //window->top    += window->border_size;
        //window->right  -= window->border_size;
        //window->bottom -= window->border_size;
    }

// Overlapped
    if (window->type == WT_OVERLAPPED)
    {

        if (window->active == TRUE)
            window->border_size=2;
        if (window->active == FALSE)
            window->border_size=1;

        // top
        rectBackbufferDrawRectangle( 
            parent->left + window->left, 
            parent->top  + window->top, 
            window->width, 
            window->border_size, 
            window->border_color1, 
            TRUE, 
            0 );
        // left
        rectBackbufferDrawRectangle( 
            parent->left + window->left, 
            parent->top + window->top, 
            window->border_size, window->height, 
            window->border_color1, 
            TRUE,
            0 );
        // right
        rectBackbufferDrawRectangle( 
            (parent->left + window->left + window->width - window->border_size), 
            (parent->top + window->top), 
            window->border_size, 
            window->height, 
            window->border_color2, 
            TRUE,
            0 );
        // bottom
        rectBackbufferDrawRectangle ( 
            (parent->left + window->left), 
            (parent->top + window->top + window->height - window->border_size), 
            window->width, 
            window->border_size, 
            window->border_color2, 
            TRUE,
            0 );
    
        // #test
        // Subtract border size.
        //window->left   += window->border_size;
        //window->top    += window->border_size;
        //window->right  -= window->border_size;
        //window->bottom -= window->border_size;
    }
}



// redraw_window:
// Let's redraw the window.
// Called by serviceRedrawWindow().
// #todo
// devemos repintar as janelas filhas, caso existam.
// IN: 
// window pointer, show or not.

int 
redraw_window ( 
    struct gws_window_d *window, 
    unsigned long flags )
{

// #todo
// When redrawing an WT_OVERLAPPED window,
// we can't redraw the frame if the window is in fullscreen mode.
// In this case, we just redraw the client area.

    unsigned int __tmp_color = COLOR_WINDOW;

    //#debug
    //gwssrv_debug_print ("redraw_window:\n");

// Structure validation.
    if ( (void *) window == NULL ){
        goto fail;
        //return -1;
    }
    if (window->used!=TRUE || window->magic!=1234){
        goto fail;
        //return -1;
    }

// =======================
// shadowUsed
// A sombra pertence à janela e ao frame.
// A sombra é maior que a própria janela.
// ?? Se estivermos em full screen não tem sombra ??
//CurrentColorScheme->elements[??]
//@todo: 
// ?? Se tiver barra de rolagem a largura da 
// sombra deve ser maior. ?? Não ...
//if()
// @todo: Adicionar a largura das bordas verticais 
// e barra de rolagem se tiver.
// @todo: Adicionar as larguras das 
// bordas horizontais e da barra de títulos.
// Cinza escuro.  CurrentColorScheme->elements[??] 
// @TODO: criar elemento sombra no esquema. 
// ??
// E os outros tipos, não tem sombra ??
// Os outros tipos devem ter escolha para sombra ou não ??
// Flat design pode usar sombra para definir se o botão 
// foi pressionado ou não.

// shadow: Not used for now.
    if (window->shadowUsed == TRUE)
    {
        if ( (unsigned long) window->type == WT_OVERLAPPED )
        {
            if (window->focus == 1){ __tmp_color = xCOLOR_GRAY1; }
            if (window->focus == 0){ __tmp_color = xCOLOR_GRAY2; }

            // Shadow rectangle.
            rectBackbufferDrawRectangle ( 
                (window->left +1), 
                (window->top +1), 
                (window->width +1 +1), 
                (window->height +1 +1), 
                __tmp_color, 
                TRUE,     // fill?
                (unsigned long) window->rop );  // #todo: rop operations for this window.
        }
    }

// =======================
// backgroundUsed
// ## Background ##
// Background para todo o espaço ocupado pela janela e pelo seu frame.
// O posicionamento do background depende do tipo de janela.
// Um controlador ou um editbox deve ter um posicionamento relativo
// à sua janela mãe. Já uma overlapped pode ser relativo a janela 
// gui->main ou relativo à janela mãe.

// background rectangle.
    if (window->backgroundUsed == TRUE)
    {
        // redraw the background rectandle.
        rectBackbufferDrawRectangle ( 
                window->left, 
                window->top, 
                window->width, 
                window->height, 
                window->bg_color, 
                TRUE, 
                (unsigned long) window->rop );   // ROP for this window.

        // All done for WT_SIMPLE type.
        if( window->type == WT_SIMPLE ){
            goto done;
        }
    }

//
// botao ==========================================
//

// =======================
// WT_BUTTON

    //Termina de desenhar o botão, mas não é frame
    //é só o botão...
    //caso o botão tenha algum frame, será alguma borda extra.
    int Focus=0;    //(precisa de borda)
    int Selected=0;
    unsigned int border1=0;
    unsigned int border2=0;

    if (window->type == WT_BUTTON)
    {
        //if ( (void*) window->parent == NULL )
            //printf("redraw_window: [FAIL] window->parent\n");

        // Atualiza algumas características da janela.
        switch (window->status)
        {
            case BS_FOCUS:
                border1 = COLOR_BLUE;
                border2 = COLOR_BLUE;
                break;

            //case BS_PRESS:
            case BS_PRESSED:
                Selected = 1;
                border1 = xCOLOR_GRAY1;  //GWS_COLOR_BUTTONSHADOW3;
                border2 = COLOR_WHITE;   //GWS_COLOR_BUTTONHIGHLIGHT3;
                break;

            case BS_HOVER:
                //border1 = COLOR_YELLOW;  //#test
                //border2 = COLOR_YELLOW;  //#test
                border1 = COLOR_WHITE;    //GWS_COLOR_BUTTONHIGHLIGHT3;
                border2 = xCOLOR_GRAY1;   //GWS_COLOR_BUTTONSHADOW3;
                break;

            case BS_DISABLED:
                border1 = COLOR_GRAY;
                border2 = COLOR_GRAY;
                break;

            //?
            case BS_PROGRESS:
                break;

            case BS_DEFAULT:
            default: 
                Selected = 0;
                border1 = COLOR_WHITE;    //GWS_COLOR_BUTTONHIGHLIGHT3;
                border2 = xCOLOR_GRAY1;   //GWS_COLOR_BUTTONSHADOW3;
                break;
        };

        // name support.
        size_t tmp_size = (size_t) strlen ( (const char *) window->name );
        if (tmp_size>64){
            tmp_size=64;
        }
        unsigned long offset = 
        ( ( (unsigned long) window->width - ( (unsigned long) tmp_size * (unsigned long) gcharWidth) ) / 2 );

        // redraw the button border.
        // #todo:
        // as cores vao depender do etado do botao.
        // #todo: veja como foi feito na hora da criaçao do botao.
        __draw_button_borders(
            (struct gws_window_d *) window,
            (unsigned int) border1,        //buttonBorderColor1,
            (unsigned int) border2,        //buttonBorderColor2,
            (unsigned int) xCOLOR_GRAY5,   //buttonBorderColor2_light,
            (unsigned int) COLOR_BLACK );  //buttonBorder_outercolor );
             
        // Button label
        //gwssrv_debug_print ("redraw_window: [FIXME] Button label\n"); 

        if (Selected == TRUE){
            grDrawString ( 
                (window->left) +offset, 
                (window->top)  +8, 
                COLOR_WHITE, window->name );
        }

        if (Selected == FALSE){
            grDrawString ( 
                (window->left) +offset, 
                (window->top)  +8, 
                COLOR_BLACK, window->name );
        }

        // ok, repintamos o botao que eh um caso especial
        // nao precisamos das rotinas abaixo,
        // elas serao par aos outros tipos de janela.
        goto done;
    }

// =======================================
// redraw_frame:
// only the boards
// redraw the frame para alguns tipos menos para botao.
// O bg ja fi feito logo acima.
// Remember:
// We can't recreate the windows, just redraw'em.
// #todo
// Precisamos de uma rotina que redesenhe o frame,
// sem alocar criar objetos novos.

// ----------------------------------------
// + Redraws the title bar for WT_OVERLAPPED.
// + Redraws the borders for overlapped and editbox.

    if ( window->type == WT_OVERLAPPED || 
         window->type == WT_EDITBOX_SINGLE_LINE || 
         window->type == WT_EDITBOX_MULTIPLE_LINES )
    {
        // Invalid window
        if ( (void*) window == NULL )
            goto fail;
        if (window->magic != 1234)
            goto fail;

        // Invalid parent window
        // # root has no parent, but its type is WT_SIMPLE.
        if ( (void*) window->parent == NULL )
            goto fail;
        if (window->parent->magic != 1234)
            goto fail;

        // Title bar
        // Redraw titlebar for overlapped windows.
        // #todo: Not if the window is in fullscreen mode.
        if (window->type == WT_OVERLAPPED)
        {
            // Valid titlebar.
            if ( (void*) window->titlebar != NULL )
            {
                if (window->titlebar->magic == 1234 )
                {
                    // Se a janela overlapped é uma janela ativa.
                    // #bugbug Isso funciona para a janela mãe apenas.
                    if (window->active == TRUE)
                    {
                        window->titlebar->bg_color = 
                            (unsigned int) get_color(csiTaskBar);
                        window->titlebar_color = 
                            (unsigned int) get_color(csiTaskBar);
                        window->titlebar_ornament_color = xCOLOR_BLACK;
                    }
                    // Se a janela overlapped não é uma janela ativa.
                    // #bugbug Isso funciona para a janela mãe apenas.
                    if (window->active == FALSE)
                    {
                        window->titlebar->bg_color = 
                            (unsigned int) get_color(csiTaskBar);
                        window->titlebar_color = 
                            (unsigned int) get_color(csiTaskBar);
                        window->titlebar_ornament_color = xCOLOR_GRAY2;
                    }

                    //bg
                    rectBackbufferDrawRectangle ( 
                        window->titlebar->left, 
                        window->titlebar->top, 
                        window->titlebar->width, 
                        window->titlebar->height, 
                        window->titlebar->bg_color, 
                        TRUE,   // fill
                        (unsigned long) window->rop );  // rop for this window

                    // ornament
                    rectBackbufferDrawRectangle ( 
                        window->titlebar->left, 
                        ( (window->titlebar->top) + (window->titlebar->height) - METRICS_TITLEBAR_ORNAMENT_SIZE ),  
                        window->titlebar->width, 
                        METRICS_TITLEBAR_ORNAMENT_SIZE, 
                        window->titlebar_ornament_color, 
                        TRUE,  // fill
                        (unsigned long) window->rop );  // rop_flags

                    // redraw controls.
                    // recursive
                    // #bugbug
                    // Recursive is dangerous and
                    // it is painting in the wrong place.
                    //redraw_window(window->titlebar->Controls.minimize,FALSE);
                    //redraw_window(window->titlebar->Controls.maximize,FALSE);
                    //redraw_window(window->titlebar->Controls.close,FALSE);
                }
            }
        }

        // Borders: 
        // Let's repaint the borders for some types.
        if ( window->type == WT_OVERLAPPED ||
             window->type == WT_EDITBOX_SINGLE_LINE ||
             window->type == WT_EDITBOX_MULTIPLE_LINES )
        {
            __draw_window_border(window->parent, window);
        }
        
        //...
    }

    // ...

done:
    if (flags == TRUE){
        gws_show_window_rect(window);
    }
    return 0;
fail:
    return -1;
}

int redraw_window_by_id(int wid, unsigned long flags)
{
    struct gws_window_d *w;

// wid
    if (wid<0 || wid>=WINDOW_COUNT_MAX)
        return -1;
// structure validation
    w = (void*) windowList[wid];
    if( (void*) w == NULL )
        return -1;
    if(w->magic!=1234)
        return -1;
    
    redraw_window(w,flags);
    return 0;
}

// validate
void validate_window (struct gws_window_d *window)
{
    if ( (void*) window != NULL )
    {
        if ( window->used == TRUE && window->magic == 1234 )
        {
            window->dirty = FALSE;
        }
    }
}

void invalidate_window_by_id( int wid )
{
    struct gws_window_d *w;

// #todo: 
// Chamar o metodo de validação de janela.

// wid
    if (wid<0)
        return;
    if (wid>=WINDOW_COUNT_MAX)
        return;
// Window structure
    w = (struct gws_window_d *)windowList[wid];
    if((void*)w==NULL){
        return;
    }
    if (w->used!=TRUE) { return; }
    if (w->magic!=1234){ return; }

    invalidate_window(w);    
}


// Invalidate
void invalidate_window (struct gws_window_d *window)
{
    if ( (void*) window != NULL )
    {
        if ( window->used == TRUE && window->magic == 1234 )
        {
            window->dirty = TRUE;
        }
    }
}


void invalidate_root_window(void)
{
    invalidate_window ( (struct gws_window_d *) __root_window );
}

void invalidate_taskbar_window(void)
{
    invalidate_window ( (struct gws_window_d *) taskbar_window );
}


void wm_flush_rectangle(struct gws_rect_d *rect)
{
    if ( (void*) rect == NULL ){
        return;
    }
    if (rect->magic!=1234){
        return;
    }
    gwssrv_refresh_this_rect(rect);
}


void wm_flush_screen(void)
{
    gwssrv_show_backbuffer();
}


void wm_flush_window(struct gws_window_d *window)
{
    if( (void*) window == NULL ){
        return;
    }
    if(window->used != TRUE) { return; }
    if(window->magic != 1234){ return; }
    gws_show_window_rect(window);
}


void begin_paint(struct gws_window_d *window)
{
    if( (void*) window == NULL )
        return;

    validate_window(window);
}

void end_paint(struct gws_window_d *window)
{
    if( (void*) window == NULL )
        return;

    invalidate_window(window);
}





