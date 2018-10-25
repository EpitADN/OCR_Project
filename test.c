/*
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
    sizeLayers = parser(nbLayers,entre2);


    T_Network* network = CreateNetwork_Auto(nbLayers,sizeLayers);


    //PrintAllNetworkInfos(network);


    char *texte2 = "appeler fonction ";
    gtk_label_set_text(GTK_LABEL(label),texte2);
}



int main (int argc, char **argv)
{
    //On declare nos widget
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *resultat;
    GtkWidget *NbLayers;
    GtkWidget *Nbnoeuds;




    // Initialisation de GTK+

    gtk_init(&argc, &argv);

    //on initialise les widgets

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),1200,800);
    grid = gtk_grid_new();
    button = gtk_button_new_with_label("Train");

    resultat = gtk_label_new("Resultat");
    NbLayers = gtk_label_new("Nobres de couches");
    Nbnoeuds = gtk_label_new("Nombres de noeuds par couches");

    NbLayersEntry = gtk_entry_new();
    NbnoeudsEntry = gtk_entry_new();



    //dans la grid
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_attach(GTK_GRID(grid),NbLayers,0,0,1,1);
    gtk_grid_attach(GTK_GRID(grid),NbLayersEntry,1,0,1,1);
    gtk_grid_attach(GTK_GRID(grid),Nbnoeuds,0,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),NbnoeudsEntry,1,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),button,0,2,1,1);
    gtk_grid_attach(GTK_GRID(grid),resultat,1,2,1,1);






    g_signal_connect(button,"clicked",G_CALLBACK(XOR3),resultat);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy),button);

    //Destruction de la fenetre quand on clique sur la croix rouge ou sur quitter

    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;


}
*/