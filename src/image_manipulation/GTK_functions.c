#include <gtk/gtk.h>
#include <SDL.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "open_image.h"
#include "to_binarize.h"
#include "GTK_functions.h"
#include "SDL_functions.h"

void on_window_main_destroy(GObject *object, gpointer user_data)
{
	g_object_unref(BUILDER);
	SDL_FreeSurface(IMAGE);
    gtk_main_quit();
}

void binarize_button(GObject *object, gpointer user_data)
{
    otsu(IMAGE);
    realpath("../temp/binarized.bmp", FILE_NAME);
    reload_image(0);
}

void grayscale_button(GObject *object, gpointer user_data)
{
    printf("Niveau de gris tmtc\n");
}

void rotate_button(GObject *object, gpointer user_data)
{
    printf("Rotation en loosdé\n");
}

void smoothy_button(GObject *object, gpointer user_data)
{
    printf("Le beau lissage Starfoulaye\n");
}

void select_file(GObject *bouton)
{
	gint res;
	GtkWidget *topparent = gtk_widget_get_toplevel(GTK_WIDGET(bouton));
	GtkWidget *dialogue = gtk_file_chooser_dialog_new("Select Image", 
														GTK_WINDOW (topparent), 
														GTK_FILE_CHOOSER_ACTION_OPEN,
														"Ouvrir", GTK_RESPONSE_ACCEPT,
														"Annuler", GTK_RESPONSE_CANCEL,
														NULL);

	res = gtk_dialog_run(GTK_DIALOG(dialogue));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		char *filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialogue));
		strncpy(FILE_NAME, filename, 256);
		printf("%s\n", FILE_NAME);
		/*GtkWidget *image = gtk_image_new_from_file(filename);
		open_image(filename, GTK_IMAGE(image));*/
		//printf("%s\n%s\n", filename, FILE_NAME);
		g_free(filename);
	}
	gtk_widget_destroy(dialogue);
	open_image_test();
}

void open_image_test()
{
	//Partie SDL
    SDL_Surface *image = SDL_LoadBMP(FILE_NAME);

	if(image->w > 720 && image->h > 480)
	{
		SDL_Surface *new_image = Resize(image, 720, 480);
		SDL_SaveBMP(new_image,"../temp/new_image_resized.bmp");
		realpath("../temp/new_image_resized.bmp", FILE_NAME);
		//strncpy(FILE_NAME, "new_image_resized", 256);
		SDL_FreeSurface(new_image);
	}

	IMAGE = SDL_LoadBMP(FILE_NAME);
	SDL_FreeSurface(image);
	//Affichage fenentre dans GTK
	if (PRINT_IMAGE)
		reload_image(0);
	else
		reload_image(1);
	/*GObject *frame = gtk_builder_get_object(BUILDER, "frame");

	GtkWidget *img;
	img = gtk_image_new_from_file(FILE_NAME);

	gtk_container_add(GTK_CONTAINER(frame), img);
    gtk_widget_show(img);*/
}

void reload_image(int assertion)
{
	//GObject *frame = gtk_builder_get_object(BUILDER, "frame");
	if (assertion == 1)
	{
		FRAME = gtk_builder_get_object(BUILDER, "frame");
		PRINT_IMAGE = gtk_image_new_from_file(FILE_NAME);
		gtk_container_add(GTK_CONTAINER(FRAME), PRINT_IMAGE);
    	gtk_widget_show(PRINT_IMAGE);
	}
	if (assertion == 0)
	{
		printf("%s\n", FILE_NAME);
		//GtkWidget *print_img_temp = g_object_ref(PRINT_IMAGE);
		GtkWidget *print_img_temp = gtk_image_new_from_file(FILE_NAME);
		gtk_container_remove(GTK_CONTAINER(FRAME), PRINT_IMAGE);
		gtk_container_add(GTK_CONTAINER(FRAME), print_img_temp);
    	gtk_widget_show(print_img_temp);
		//PRINT_IMAGE = print_img_temp;
		//FRAME = gtk_builder_get_object(BUILDER, "frame");
		//PRINT_IMAGE = gtk_image_new_from_file(FILE_NAME);
		//reload_image(1);
	}

	//GtkWidget *img;
	//PRINT_IMAGE = gtk_image_new_from_file(FILE_NAME);

	//gtk_container_add(GTK_CONTAINER(FRAME), PRINT_IMAGE);
    //gtk_widget_show(PRINT_IMAGE);
    //gtk_container_remove(GTK_CONTAINER(FRAME), PRINT_IMAGE);
}

/*SDL_Surface* resize_image(SDL_Surface *img, int w, int h)
{
	SDL_Surface *dest = SDL_CreateRGBSurface(SDL_SWSURFACE,
												w, h, 
												img->format->BitsPerPixel, 0,0,0,0);
	SDL_SoftStretch(img, NULL, dest, NULL);
	return dest;
}*/
