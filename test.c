#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "Network.h"
#include "UI.h"


static  GtkWidget *NbLayersEntry;
static GtkWidget *NbnoeudsEntry;

void XOR3(GtkWidget *widget,gpointer data )
{

    GtkWidget *label = (GtkWidget *) data;

    char* entre1 = (char *)(gtk_entry_get_text(GTK_ENTRY(NbLayersEntry)));
    char* entre2 = (char *)(gtk_entry_get_text(GTK_ENTRY(NbnoeudsEntry)));

    int* nbLayers = malloc(sizeof(int));
    *nbLayers = (int)entre1;

    int** sizeLayers;
    //sizeLayers = parser(nbLayers,entre2);


    //T_Network* network = CreateNetwork_Auto(nbLayers,sizeLayers);


    //PrintAllNetworkInfos(network);


    char *texte2 = "appeler fonction ";
    gtk_label_set_text(GTK_LABEL(label),texte2);
}



int main (int argc, char **argv)
{
    //Widgets Delcaration
    GtkWidget *window;

    GtkWidget *button;
    GtkWidget *resultat;
    GtkWidget *NbLayers;
    GtkWidget *Nbnoeuds;

    GtkWidget *Vbox1;
    GtkWidget *Hbox1;
    GtkWidget *Hbox2;
    GtkWidget *Hbox3;



    // GTK+ initialising

    gtk_init(&argc, &argv);

    //widgets initialising

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),1200,800);
    Vbox1 = gtk_vbox_new(TRUE,10);
    Hbox1 = gtk_hbox_new(TRUE,10);
    Hbox2 = gtk_hbox_new(TRUE,10);
    Hbox3 = gtk_hbox_new(TRUE,10);
    button = gtk_button_new_with_label("Train");

    resultat = gtk_label_new("Resultat");
    NbLayers = gtk_label_new("Nobres de couches");
    Nbnoeuds = gtk_label_new("Nombres de noeuds par couches");

    NbLayersEntry = gtk_entry_new();
    NbnoeudsEntry = gtk_entry_new();



    //Into the box
    gtk_container_add(GTK_CONTAINER(window), Vbox1);
    gtk_box_pack_start(Vbox1,Hbox1,TRUE,TRUE,NULL);
    gtk_box_pack_start(Vbox1,Hbox2,TRUE,TRUE,NULL);
    gtk_box_pack_start(Vbox1,Hbox3,TRUE,TRUE,NULL);
    gtk_box_pack_start(Hbox1,NbLayers,TRUE,TRUE,NULL);
    gtk_box_pack_start(Hbox1,NbLayersEntry,TRUE,TRUE,NULL);
    gtk_box_pack_start(Hbox2,Nbnoeuds,TRUE,TRUE,NULL);
    gtk_box_pack_start(Hbox2,NbnoeudsEntry,TRUE,TRUE,NULL);
    gtk_box_pack_start(Hbox3,button,TRUE,TRUE,NULL);
    gtk_box_pack_start(Hbox3,resultat,TRUE,TRUE,NULL);







    g_signal_connect(button,"clicked",G_CALLBACK(XOR3),resultat);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy),button);

    //Window destroy

    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);

    //show window

    gtk_widget_show_all(window);

    gtk_main();

    return 0;


}
