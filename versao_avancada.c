#include <gtk/gtk.h>
#include <string.h>

// Estrutura para armazenar os alunos
#define MAX_ALUNOS 100
#define MAX_NOME 50

static char lista_alunos[MAX_ALUNOS][MAX_NOME];
static int total_alunos = 0;

// Widgets globais para acesso em diferentes funções
static GtkWidget *entry_nome;
static GtkWidget *text_view;
static GtkTextBuffer *text_buffer;

// Função para adicionar aluno usando o texto digitado
static void adicionar_aluno_digitado(GtkWidget *widget, gpointer data) {
    const char *nome = gtk_entry_get_text(GTK_ENTRY(entry_nome));
    
    if (strlen(nome) == 0) {
        g_print("Por favor, digite um nome antes de adicionar!\n");
        return;
    }
    
    if (total_alunos < MAX_ALUNOS) {
        strcpy(lista_alunos[total_alunos], nome);
        total_alunos++;
        
        g_print("Aluno adicionado: %s\n", nome);
        
        // Limpar o campo de entrada
        gtk_entry_set_text(GTK_ENTRY(entry_nome), "");
        
        // Atualizar a lista visual
        char texto_completo[2000] = "=== LISTA DE ALUNOS ===\n\n";
        
        if (total_alunos == 0) {
            strcat(texto_completo, "Nenhum aluno cadastrado.\n");
        } else {
            for (int i = 0; i < total_alunos; i++) {
                char linha[100];
                sprintf(linha, "%d. %s\n", i + 1, lista_alunos[i]);
                strcat(texto_completo, linha);
            }
        }
        
        char rodape[100];
        sprintf(rodape, "\nTotal: %d aluno(s)", total_alunos);
        strcat(texto_completo, rodape);
        
        gtk_text_buffer_set_text(text_buffer, texto_completo, -1);
    } else {
        g_print("Lista cheia! Máximo de %d alunos.\n", MAX_ALUNOS);
    }
}

// Função para limpar a lista
static void limpar_lista(GtkWidget *widget, gpointer data) {
    total_alunos = 0;
    gtk_text_buffer_set_text(text_buffer, "=== LISTA DE ALUNOS ===\n\nNenhum aluno cadastrado.\n\nTotal: 0 aluno(s)", -1);
    g_print("Lista limpa!\n");
}

// Função chamada quando Enter é pressionado no campo de texto
static void on_entry_activate(GtkWidget *widget, gpointer data) {
    adicionar_aluno_digitado(widget, data);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *input_box;
    GtkWidget *button_box;
    GtkWidget *label_nome;
    GtkWidget *button_adicionar;
    GtkWidget *button_limpar;
    GtkWidget *scrolled_window;

    gtk_init(&argc, &argv);

    // Criar janela principal
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sistema Avançado de Alunos - FIAP");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Container principal
    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 15);

    // Seção de entrada de dados
    input_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    label_nome = gtk_label_new("Nome do Aluno:");
    gtk_widget_set_size_request(label_nome, 100, -1);
    
    entry_nome = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_nome), "Digite o nome do aluno aqui...");
    g_signal_connect(entry_nome, "activate", G_CALLBACK(on_entry_activate), NULL);

    gtk_box_pack_start(GTK_BOX(input_box), label_nome, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(input_box), entry_nome, TRUE, TRUE, 0);

    // Seção de botões
    button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    button_adicionar = gtk_button_new_with_label("Adicionar Aluno");
    g_signal_connect(button_adicionar, "clicked", G_CALLBACK(adicionar_aluno_digitado), NULL);
    
    button_limpar = gtk_button_new_with_label("Limpar Lista");
    g_signal_connect(button_limpar, "clicked", G_CALLBACK(limpar_lista), NULL);

    gtk_box_pack_start(GTK_BOX(button_box), button_adicionar, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_box), button_limpar, TRUE, TRUE, 0);

    // Área de texto com scroll para mostrar a lista
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), 
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrolled_window, -1, 200);

    text_view = gtk_text_view_new();
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_buffer_set_text(text_buffer, "=== LISTA DE ALUNOS ===\n\nNenhum aluno cadastrado.\n\nTotal: 0 aluno(s)", -1);

    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    // Montar interface
    gtk_box_pack_start(GTK_BOX(main_box), input_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), button_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), scrolled_window, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), main_box);

    // Focar no campo de entrada
    gtk_widget_grab_focus(entry_nome);

    // Mostrar todos os elementos
    gtk_widget_show_all(window);

    g_print("=== SISTEMA AVANÇADO DE ALUNOS INICIADO ===\n");
    g_print("Digite nomes na interface gráfica!\n");
    g_print("Você pode pressionar Enter ou clicar em 'Adicionar Aluno'\n\n");

    // Iniciar loop principal
    gtk_main();

    return 0;
}