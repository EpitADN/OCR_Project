#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "UI.h"


/*

Pour compiler sur les nucs :

gcc main_UI.c -o UI `pkg-config --cflags --libs gtk+-2.0`


*/


char *filename  = "OCR_Project/Images/Epitadn.png";

void XOR(GtkWidget *widget,gpointer data )
{
    GtkWidget *label = (GtkWidget *) data;
    char *texte2 = malloc(500*sizeof(int));
    Create_Xor(texte2);
    gtk_label_set_text(GTK_LABEL(label),texte2);
    free(texte2);
}

void Open_file(GtkWidget *widget,gpointer data)
{

    GtkWidget *dialog;


    dialog = gtk_file_chooser_dialog_new ("Open File",
                                          NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);

    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {


        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        //printf("%s",filename);
        GtkWidget *label = (GtkWidget *) data;
        gtk_label_set_text(GTK_LABEL(label),filename);
    }

    gtk_widget_destroy (dialog);
}

void ChangeImage(GtkWidget *widget,gpointer data)
{
    gtk_image_set_from_file(widget,filename);
}

int main (int argc, char **argv)
{
    //Widgets Delcaration
    GtkWidget *window;
    GtkWidget *hbox_Main;
    GtkWidget *vbox_button;
    GtkWidget *button_Xor;
    GtkWidget *button_Open_File;
    GtkWidget *label;
    GtkWidget *image;



    //GTK+ initialising

    gtk_init(&argc, &argv);

    //widgets initialising

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),1200,800);
    hbox_Main = gtk_hbox_new(FALSE,10);
    vbox_button = gtk_vbox_new(FALSE,10);
    button_Xor = gtk_button_new_with_label("Xor");
    button_Open_File = gtk_button_new_with_label("Open File");
    label = gtk_label_new("Resultat");
    image =  gtk_image_new_from_file(filename);



    //Into the box

    gtk_container_add(GTK_CONTAINER(window), hbox_Main);
    gtk_box_pack_start(GTK_BOX(hbox_Main),vbox_button,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox_button),button_Xor,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox_button),button_Open_File,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox_Main),label,TRUE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox_Main),image,TRUE,FALSE,0);





    //Clicking buttons


    g_signal_connect(button_Xor,"clicked",G_CALLBACK(XOR),label);


    g_signal_connect(button_Open_File,"clicked",G_CALLBACK(Open_file),label);
    g_signal_connect_swapped (button_Open_File, "clicked", G_CALLBACK (ChangeImage),image);

    //Window destroy

    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);

    //Show window

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
