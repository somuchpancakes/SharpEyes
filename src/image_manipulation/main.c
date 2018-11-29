#include <gtk/gtk.h>
#include <stdio.h>
#include <SDL.h>

#include "GTK_functions.h"
#include "to_binarize.h"
#include "open_image.h"
#include "SDL_functions.h"

/* 
    Compiler GTK + SDL: 
        gcc -o gladewin main.c open_image.c GTK_functions.c SDL_functions.c to_binarize.c ../pixel/pixel_operations.c ../decoupage/decoupage.h
        -Wall $(sdl2-config --cflags --libs) `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
    Compiler SDL : 
        gcc test.c -o exec $(sdl2-config --cflags --libs)
*/


int main(int argc, char *argv[])
{
	//GtkBuilder  *builder;
	GtkWidget   *window;

	gtk_init(&argc, &argv);
 
    //builder = gtk_builder_new();
    BUILDER = gtk_builder_new();
    gtk_builder_add_from_file (BUILDER, "window_main.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(BUILDER, "window_main"));
    gtk_builder_connect_signals(BUILDER, NULL);

    gtk_window_set_title(GTK_WINDOW(window), "Sharp Eyes");

    //---------- FONCTION SUR LES BOUTONS ----------//

    //Association fonction quitter a la fenetre
    GObject *quit_button = gtk_builder_get_object(BUILDER, "quit");
    g_signal_connect (quit_button, "select", G_CALLBACK (on_window_main_destroy), NULL);

    //Choix fichier et affichage image
    GObject *select_image = gtk_builder_get_object(BUILDER, "open");
    g_signal_connect (select_image, "activate", G_CALLBACK (select_file), NULL);

    //Ouvrir image
    /*GObject *open_button = gtk_builder_get_object(BUILDER, "save");
    g_signal_connect (open_button, "activate", G_CALLBACK (open_image), NULL);*/

    //binarisation
    GObject *bin_button = gtk_builder_get_object(BUILDER, "binariser");
    g_signal_connect (bin_button, "activate", G_CALLBACK (binarize_button), NULL);

    //Grayscale
    GObject *gray_button = gtk_builder_get_object(BUILDER, "gris");
    g_signal_connect (gray_button, "activate", G_CALLBACK (grayscale_button), NULL);

    //Rotation
    GObject *rotat_button = gtk_builder_get_object(BUILDER, "rotation");
    g_signal_connect (rotat_button, "activate", G_CALLBACK (rotate_button), NULL);

    //Lissage
    GObject *smooth_button = gtk_builder_get_object(BUILDER, "lissage");
    g_signal_connect (smooth_button, "activate", G_CALLBACK (smoothy_button), NULL);

    //---------- FIN FONCTION SUR LES BOUTONS ----------//
    //g_object_unref(BUILDER);
 
    gtk_widget_show_all(window);                
    gtk_main();
 
    return 0;
}