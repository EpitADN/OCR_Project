//
// Created by corentin on 23/10/18.
//

#include <stdlib.h>
#include <gtk/gtk.h>




void XOR3(GtkWidget *widget,gpointer data )
{

    GtkWidget *label = (GtkWidget *) data;
    gchar *texte2 = "Test";
    gtk_label_set_text(label,texte2);
}

int main (int argc, char **argv)
{
    //On declare nos widget
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *button;
    GtkWidget *quit;
    GtkWidget *label;
    gchar* text = "Resultat";


    /* Initialisation de GTK+ */

    gtk_init(&argc, &argv);

    /*on initialise les widgets*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),1200,800);
    vbox = gtk_vbox_new(TRUE,10);
    button = gtk_button_new_with_label("Xor");
    quit = gtk_button_new_with_label("Quitter");
    label = gtk_label_new(text);



    /* dans la box*/
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_box_pack_start(GTK_BOX(vbox),label,TRUE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),button,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),quit,FALSE,FALSE,0);






    g_signal_connect(button,"clicked",G_CALLBACK(XOR3),label);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy),button);

    /*Destruction de la fenetre quand on clique sur la croix rouge ou sur quitter*/

    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(G_OBJECT(quit),"clicked",G_CALLBACK(gtk_main_quit),window);



    gtk_widget_show_all(window);

    gtk_main();

    return 0;


}
