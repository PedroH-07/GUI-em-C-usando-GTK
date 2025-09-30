#include <gtk/gtk.h>
#include <string.h>

// Estrutura para armazenar os alunos
#define MAX_ALUNOS 100
#define MAX_NOME 50

static char lista_alunos[MAX_ALUNOS][MAX_NOME];
static int total_alunos = 0;

// Função para adicionar aluno (nome fixo para demonstração)
static void adicionar_aluno(GtkWidget *widget, gpointer data) {
    if (total_alunos < MAX_ALUNOS) {
        // Para demonstração, vamos adicionar nomes fixos
        char nomes_exemplo[][MAX_NOME] = {
            "João Silva",
            "Maria Santos", 
            "Pedro Oliveira",
            "Ana Costa",
            "Carlos Pereira",
            "Julia Ferreira",
            "Rafael Lima",
            "Fernanda Rocha"
        };
        
        if (total_alunos < 8) {
            strcpy(lista_alunos[total_alunos], nomes_exemplo[total_alunos]);
        } else {
            sprintf(lista_alunos[total_alunos], "Aluno %d", total_alunos + 1);
        }
        
        total_alunos++;
        g_print("Aluno adicionado: %s\n", lista_alunos[total_alunos - 1]);
        g_print("Total de alunos: %d\n\n", total_alunos);
    } else {
        g_print("Lista cheia! Máximo de %d alunos.\n", MAX_ALUNOS);
    }
}

// Função para listar todos os alunos
static void listar_alunos(GtkWidget *widget, gpointer data) {
    g_print("=== LISTA DE ALUNOS ===\n");
    
    if (total_alunos == 0) {
        g_print("Nenhum aluno cadastrado.\n");
    } else {
        for (int i = 0; i < total_alunos; i++) {
            g_print("%d. %s\n", i + 1, lista_alunos[i]);
        }
    }
    g_print("Total: %d aluno(s)\n", total_alunos);
    g_print("=====================\n\n");
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *button_adicionar;
    GtkWidget *button_listar;

    gtk_init(&argc, &argv);

    // Criar janela principal
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sistema de Alunos - FIAP");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Criar container vertical para organizar os botões
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);

    // Criar botão "Adicionar Aluno"
    button_adicionar = gtk_button_new_with_label("Adicionar Aluno");
    gtk_widget_set_size_request(button_adicionar, -1, 50);
    g_signal_connect(button_adicionar, "clicked", G_CALLBACK(adicionar_aluno), NULL);

    // Criar botão "Listar Alunos"
    button_listar = gtk_button_new_with_label("Listar Alunos");
    gtk_widget_set_size_request(button_listar, -1, 50);
    g_signal_connect(button_listar, "clicked", G_CALLBACK(listar_alunos), NULL);

    // Adicionar botões ao container
    gtk_box_pack_start(GTK_BOX(vbox), button_adicionar, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_listar, TRUE, TRUE, 0);

    // Adicionar container à janela
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Mostrar todos os elementos
    gtk_widget_show_all(window);

    g_print("=== SISTEMA DE ALUNOS INICIADO ===\n");
    g_print("Use os botões na janela para interagir!\n");
    g_print("As mensagens aparecerão aqui no terminal.\n\n");

    // Iniciar loop principal
    gtk_main();

    return 0;
}