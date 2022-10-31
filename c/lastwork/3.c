#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    int CPF;
    char *name;
    int birthYear;
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

void add_end(LIST* list, int CPF, char* name, int birthYear)
{
    node *new = (node*) malloc(sizeof(node));
    if (new == NULL)
    {
        printf("Erro na alocacao.\n");
        exit(0);
    }
    new->CPF = CPF;
    new->name = malloc(255*sizeof(char));
    new->name = name;
    new->birthYear = birthYear;
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

void easy_sort(LIST* list)
{
    if ((*list) == NULL)
    {
        printf("Lista está vazia...\n");
    }
    else
    {
        int changed;
        node *tmp;
        do
        {
            changed = 0;
            tmp = (*list);
            node *previous = (*list);
            while ((tmp != NULL) && (tmp->nxt != NULL))
            {
                node *next = tmp->nxt;
                if (next->birthYear < tmp->birthYear)
                {
                    if (next->nxt != NULL) tmp->nxt = next->nxt;
                    else tmp->nxt = NULL;
                    if ((previous != NULL) && (previous != tmp)) previous->nxt = next;
                    if (previous == tmp) (*list) = next;
                    next->nxt = tmp;
                    changed = 1;
                }
                previous = tmp;
                tmp = tmp->nxt;
                
            }
        } while (changed);   
    }
}

void show_list(LIST* list)
{
    if ((*list) == NULL)
    {
        printf("Lista de de clientes vazia...\n");
    }
    else
    {
        node *tmp;
        tmp = (*list);
        while (tmp != NULL)
        {
            printf("\nCliente: \"%s\"\n", tmp->name);
            printf("Ano de Nascimento: %i\n", tmp->birthYear);
            printf("CPF: %i\n", tmp->CPF);
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
    FILE *f = fopen("clientes.txt", "r+");
    if (f != NULL)
    {
        while (!feof(f))
        {
            int CPF, birthYear;
            char *name = malloc(255*sizeof(char));
            fscanf(f, "%i", &CPF); 
            fgetc(f);
            fscanf(f, "%[^,]s", name);
            fgetc(f);
            fscanf(f, "%i", &birthYear);
            fgetc(f);
            add_end(list, CPF, name, birthYear);   
        }
        easy_sort(list);
    }
    //
    while (op != 0)
    {
        printf("\nInsira uma opcao:\n");
        printf("1 - Inserir novo cliente.\n");
        printf("2 - Ver clientes.\n");
        printf("0 - Sair.\n");
        scanf("%i", &op);
        if (op == 1)
        {
            int CPF, birthYear;
            char *name = malloc(255*sizeof(char));
            printf("Insira o nome do cliente: ");
            while (getchar() != '\n');
            scanf("%[^\n]s", name);
            printf("Insira o ano de nascimento do cliente: ");
            scanf("%i", &birthYear);
            printf("Insira o CPF do cliente: ");
            scanf("%i", &CPF);
            add_end(list, CPF, name, birthYear);
            easy_sort(list);
        }
        else if (op == 2) show_list(list);
    }
    printf("Salvando livros...\n");
    FILE *fsave = fopen("clientes.txt", "w");
    node *tmp = (*list);
    while (tmp != NULL)
    {
        fprintf(fsave, "%i", tmp->CPF);
        fprintf(fsave, "%c", ',');
        fprintf(fsave, "%s", tmp->name);
        fprintf(fsave, "%c", ',');
        fprintf(fsave, "%i", tmp->birthYear);
        if (tmp->nxt != NULL) fprintf(fsave, "%c", ',');
        tmp = tmp->nxt;
    }
    printf("Saindo...\n");
    fclose(fsave);

    return 0;
}