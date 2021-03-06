#ifndef GTK_FUNCTIONS
#define GTK_FUNCTIONS

#include <gtk/gtk.h>
#include <SDL.h>
#include "../decoupage/decoupage.h"

char FILE_NAME[PATH_MAX];
GtkBuilder *BUILDER;
GtkWidget *PRINT_IMAGE;
GObject *FRAME;
SDL_Surface *IMAGE;
float rotate_angle;

void on_window_main_destroy();
void binarize_button();
void draw_lines_button();
void grayscale_button();
void rotate_button();
void smoothy_button();
void start_OCR();
void save_txt();

void select_file(GObject *bouton);
void open_image_test();
void reload_image(int assertion);

#endif
