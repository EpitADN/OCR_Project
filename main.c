#include <stdlib.h>
#include <gtk/gtk.h>


int main(int argc, char **argv)

{

    /* Variables */

    GtkWidget * MainWindow = NULL;
    GtkWidget * Label1;
    gchar* Text1;
    const gchar* title;


    /* Initialisation de GTK+ */

    gtk_init(&argc, &argv);


    /* Création de la fenêtre */

    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    /* Paramètre de la fenetre */

    gtk_window_set_title(GTK_WINDOW(MainWindow), "EpitADN OCR");

    title = gtk_window_get_title(GTK_WINDOW(MainWindow));

    gtk_window_set_default_size(GTK_WINDOW(MainWindow),1200,800);

    gtk_window_set_position(GTK_WINDOW(MainWindow),GTK_WIN_POS_CENTER);

    /* Gestion des labels */

    Text1 = "XOR";

    Label1 = gtk_label_new(Text1);

    gtk_container_add(GTK_CONTAINER(MainWindow),Label1);




    /* Affichage et boucle évènementielle */

    gtk_widget_show(MainWindow);

    gtk_widget_show_all(Label1);

    gtk_main();


    /* On quitte.. */

    return EXIT_SUCCESS;

}

