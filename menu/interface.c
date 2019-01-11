#include <gtk/gtk.h>

//COMPILE: gcc `pkg-config --cflags gtk+-3.0` -o interface interface.c `pkg-config --libs gtk+-3.0`

static gboolean
       button_press_callback (GtkWidget      *event_box,
                              GdkEventButton *event,
                              gpointer        data)
       {
  
         return TRUE;
       }


int main(int argc, char *argv[]) {

  GtkWidget *window;
  GtkWidget *vbox;

  GtkWidget *menubar;
  GtkWidget *fileMenu;
  GtkWidget *fileMi;
  GtkWidget *quitMi;
  GtkWidget *imgMi;

  GtkWidget *event_box;

  GtkWidget *image;
  image = gtk_image_new_from_file ("../c2-todos.svg");

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 1000, 500);
  gtk_window_set_title(GTK_WINDOW(window), "Siguel");

  vbox = gtk_box_new(TRUE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  menubar = gtk_menu_bar_new();
  fileMenu = gtk_menu_new();

  fileMi = gtk_menu_item_new_with_label("Mapas");
  quitMi = gtk_menu_item_new_with_label("Quit");
  imgMi = gtk_menu_item_new_with_label("c1");

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), imgMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), quitMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

  

  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);


        g_signal_connect(G_OBJECT(imgMi), "button_press_event",
             G_CALLBACK(button_press_callback), image);

  g_signal_connect(G_OBJECT(quitMi), "activate",
        G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}

