#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>


/*

Pour compiler sur les nucs :

gcc test_UI.c -o test_UI `pkg-config --cflags --libs gtk+-2.0`


*/


char *filename  = "OCR_Project/Images/Epitadn.png";

void XOR(GtkWidget *widget,gpointer data )
{
    GtkWidget *label = (GtkWidget *) data;

    char *texte2 = "Test";
    gtk_label_set_text(GTK_LABEL(label),texte2);
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
   


    //test
    GtkWidget* hbox_button_xor;
    GtkWidget* hbox_button_open;
    GtkWidget *icon_button_xor;
    GtkWidget *icon_button_open;
    GtkWidget* label_xor;
    GtkWidget* label_open;


    //GTK+ initialising

    gtk_init(&argc, &argv);

    //widgets initialising

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),1200,800);
    gtk_window_set_title(GTK_WINDOW(window),"Epitadn OCR");
    hbox_Main = gtk_hbox_new(TRUE,10);
    vbox_button = gtk_vbox_new(TRUE,10);
    button_Xor = gtk_button_new();
    button_Open_File = gtk_button_new();
    label = gtk_label_new("Resultat");
    image =  gtk_image_new_from_file(filename);
    
    //test
    hbox_button_xor = gtk_hbox_new(FALSE,0);
    hbox_button_open= gtk_hbox_new(FALSE,0);
    label_xor = gtk_label_new("XOR");
    label_open = gtk_label_new("Open File");
    icon_button_open = gtk_image_new_from_stock(GTK_STOCK_FILE,GTK_ICON_SIZE_DIALOG);
    icon_button_xor = gtk_image_new_from_stock(GTK_STOCK_FLOPPY,GTK_ICON_SIZE_DIALOG);

    

    //Into the box

    gtk_container_add(GTK_CONTAINER(window), hbox_Main);
    

    //test
    gtk_container_add(GTK_CONTAINER(button_Open_File),hbox_button_open);
    gtk_container_add(GTK_CONTAINER(button_Xor),hbox_button_xor);
    gtk_box_pack_start(GTK_BOX(hbox_button_xor),icon_button_xor,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox_button_xor),label_xor,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox_button_open),icon_button_open,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox_button_open),label_open,TRUE,TRUE,0);

    gtk_box_pack_start(GTK_BOX(hbox_Main),vbox_button,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox_button),button_Xor,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox_button),button_Open_File,TRUE,TRUE,0);
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
