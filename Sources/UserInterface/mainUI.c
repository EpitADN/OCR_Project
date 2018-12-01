#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

#include "UI.h"


void XOR(GtkWidget *widget,gpointer data )
{
    GtkWidget *label = (GtkWidget *) data;
    char *texte2 = resultat(CreateTrainerXOR());
    gtk_label_set_text(GTK_LABEL(label),texte2);
}

int main (int argc, char **argv)
{
    //Widgets Delcaration
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *button;
    GtkWidget *label;



    //GTK+ initialising

    gtk_init(&argc, &argv);

    //widgets initialising

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),1200,800);
    vbox = gtk_vbox_new(TRUE,10);
    button = gtk_button_new_with_label("Xor");
    label = gtk_label_new("Resultat");



    //Into the box

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_box_pack_start(GTK_BOX(vbox),button,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),label,TRUE,FALSE,0);








    g_signal_connect(button,"clicked",G_CALLBACK(XOR),label);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy),button);

    //Window destroy

    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);

    //Show window

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
