#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    int code;
    char *title;
    int year;
    struct Node *nxt;
};
typedef struct Node node;
typedef node *LIST;

LIST* c_list()
{
    LIST *start = (LIST*) malloc(sizeof(LIST));
    if (start != NULL)
    {
        *start = NULL;
    }
    else
    {
        printf("Erro na alocacao.\n");
        exit(0);
    }
    return start;
}

void add_start(LIST* list)
{
    node *new = (node*) malloc(sizeof(node));
    if (new == NULL)
    {
        printf("Erro na alocacao.\n");
        exit(0);
    }
    printf("Informe o codigo do novo livro:\n");
    scanf("%d", &new->code);
    new->title = (char*) malloc(255*sizeof(char));
    printf("Informe o titulo do novo livro (MAX=255):\n");
    scanf("%s", new->title);
    printf("Informe o ano do novo livro:\n\n");
    scanf("%i", &new->year);
    new->nxt = (*list);
    *list = new;
}

void add_end(LIST* list, int code, char* title, int year)
{
    node *new = (node*) malloc(sizeof(node));
    if (new == NULL)
    {
        printf("Erro na alocacao.\n");
        exit(0);
    }
    new->code = code;
    new->title = malloc(255*sizeof(char));
    new->title = title;
    new->year = year;
    new->nxt = NULL;
    if ((*list) == NULL)
    {
        (*list) = new;
    }
    else
    {
        node *tmp;
        tmp = (*list);
        while (tmp->nxt != NULL)
        {
            tmp = tmp->nxt;
        }
        tmp->nxt = new;
    }
}

void f_list(LIST* list)
{
    if ((*list) == NULL)
    {
        printf("Lista vazia...\n");
    }
    else
    {
        node *tmp;
        while ((*list) != NULL)
        {
            tmp = *list;
            *list = (*list)->nxt;
            free(tmp);
        }
        *list = NULL;
    }
}

void show_list(LIST* list)
{
    if ((*list) == NULL)
    {
        printf("Lista de livros vazia...\n");
    }
    else
    {
        node *tmp;
        tmp = (*list);
        while (tmp != NULL)
        {
            printf("\nLivro: \"%s\"\n", tmp->title);
            printf("Ano: %i\n", tmp->year);
            printf("Codigo: %i\n", tmp->code);
            tmp = tmp->nxt;
        }
    }
}

int main()
{
    // code,title,year...
    int op = -1;
    LIST *list = c_list();
    // Checks if file exists.
    FILE *f = fopen("arquivos.txt", "r+");
    if (f != NULL)
    {
        while (!feof(f))
        {
            int code, year;
            char *title = malloc(255*sizeof(char));
            fscanf(f, "%i", &code); 
            fgetc(f);
            fscanf(f, "%[^,]s", title);
            fgetc(f);
            fscanf(f, "%i", &year);
            fgetc(f);
            add_end(list, code, title, year);   
        }
    }
    //
    while (op != 0)
    {
        printf("\nInsira uma opcao:\n");
        printf("1 - Inserir novo livro.\n");
        printf("2 - Ver livros.\n");
        printf("0 - Sair.\n");
        scanf("%i", &op);
        if (op == 1)
        {
            int code, year;
            char *title = malloc(255*sizeof(char));
            printf("Insira o titulo do livro: ");
            while (getchar() != '\n');
            scanf("%[^\n]s", title);
            printf("Insira o ano do livro: ");
            scanf("%i", &year);
            printf("Insira o codigo do livro: ");
            scanf("%i", &code);
            add_end(list, code, title, year);
        }
        else if (op == 2) show_list(list);
    }
    printf("Salvando livros...\n");
    FILE *fsave = fopen("arquivos.txt", "w");
    node *tmp = (*list);
    while (tmp != NULL)
    {
        fprintf(fsave, "%i", tmp->code);
        fprintf(fsave, "%c", ',');
        fprintf(fsave, "%s", tmp->title);
        fprintf(fsave, "%c", ',');
        fprintf(fsave, "%i", tmp->year);
        if (tmp->nxt != NULL) fprintf(fsave, "%c", ',');
        tmp = tmp->nxt;
    }
    printf("Saindo...\n");
    fclose(fsave);

    return 0;
}