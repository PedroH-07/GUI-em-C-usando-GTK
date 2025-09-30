#include <gtk/gtk.h>

// Função chamada ao clicar no botão
static void on_button_clicked(GtkWidget *widget, gpointer data) {
    g_print("Botão clicado! Você pode chamar funções aqui.\n");
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Janela com Botão");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    button = gtk_button_new_with_label("Clique aqui");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    gtk_container_add(GTK_CONTAINER(window), button);
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}