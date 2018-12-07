#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "UI.h"


/*

Pour compiler sur les nucs :

gcc mainUI.c -o test_UI `pkg-config --cflags --libs gtk+-2.0`


*/


char *filename  = "Images/Epitadn.png";



void Open_file(GtkWidget *widget,gpointer data)
{

    GtkWidget *dialog;


    dialog = gtk_file_chooser_dialog_new ("Open File",
                                          NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);

    if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {

        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);


        GtkWidget *label = (GtkWidget *) data;
        gtk_label_set_text(label,filename);
    }

    gtk_widget_destroy (dialog);
}

void ChangeImage(GtkWidget *widget,gpointer data)
{
    GdkPixbuf *pixbuf;
    GtkWidget *tmp;
    GError *error = NULL; 
    GdkPixbuf *pixbuf_mini = NULL; 
    
    pixbuf = gdk_pixbuf_new_from_file (filename, &error); 
    if (!error) 
    { 
        pixbuf_mini = gdk_pixbuf_scale_simple (pixbuf, 400,(gdk_pixbuf_get_height(pixbuf)*400)/gdk_pixbuf_get_width(pixbuf),GDK_INTERP_HYPER); 
        gtk_image_set_from_pixbuf(widget,pixbuf_mini);
    } 
    else 
    { 
        g_critical (error->message); 
    }
    
}

void Set_path(GtkWidget *widget,gpointer data)
{
    GtkEntry *tmp = (GtkWidget *) data;
    gtk_entry_set_text(GTK_ENTRY(tmp),filename);
}

void Entry_use(GtkWidget *widget,gpointer data)
{
    filename = gtk_entry_get_text((GtkWidget *) data);
}

void Set_result(GtkWidget *widget,gpointer data)
{
    char* ret;

    Result(ret,filename);
    GtkWidget *label = (GtkWidget *) data;
    gtk_label_set_text(label,ret);

}


int main (int argc, char **argv)
{
    //Widgets Delcaration
    GtkWidget *window;
    GtkWidget *hbox_Main;
    GtkWidget *vbox_button;
    GtkWidget *button_Open_File;
    GtkWidget *label;
    GtkWidget *image;
    GtkWidget *icon_button_open;
    GtkWidget *hbox_open;
    GtkWidget *entry;
    


    //GTK+ initialising

    gtk_init(&argc, &argv);

    //widgets initialising

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),700,400);
    gtk_window_set_title(GTK_WINDOW(window),"Epitadn OCR");
    hbox_Main = gtk_hbox_new(TRUE,10);
    vbox_button = gtk_vbox_new(FALSE,10);
    button_Open_File = gtk_button_new();
    label = gtk_label_new("Resultat");
    image =  gtk_image_new_from_file(filename);
    icon_button_open = gtk_image_new_from_stock(GTK_STOCK_FILE,GTK_ICON_SIZE_DIALOG);
    entry = gtk_entry_new();
    hbox_open = gtk_hbox_new(FALSE,10);
    gtk_entry_set_text(entry,filename);
    

    

    //Into the box

    gtk_container_add(GTK_CONTAINER(window), hbox_Main);
    gtk_box_pack_start(GTK_BOX(hbox_Main),vbox_button,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox_button),image,TRUE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox_button),hbox_open,TRUE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox_open),entry,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox_open),button_Open_File,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox_Main),label,TRUE,TRUE,0);
    gtk_container_add(GTK_CONTAINER(button_Open_File), icon_button_open);





    //Clicking buttons

    g_signal_connect(button_Open_File,"clicked",G_CALLBACK(Open_file),label);
    g_signal_connect_swapped (button_Open_File, "clicked", G_CALLBACK(ChangeImage),image);
    g_signal_connect_swapped (button_Open_File, "clicked", G_CALLBACK(Set_path),entry);
    g_signal_connect_swapped (button_Open_File, "clicked", G_CALLBACK(Set_result),label);

    //Pasting Entry
    g_signal_connect(entry,"activate",G_CALLBACK(Entry_use),entry);
    g_signal_connect_swapped (entry, "activate", G_CALLBACK(ChangeImage),image);
    g_signal_connect_swapped (entry, "activate", G_CALLBACK(Set_result),label);

    //Window destroy

    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);


    //Show window

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
