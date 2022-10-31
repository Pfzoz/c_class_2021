#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    int price;
    char *brand;
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

void add_end(LIST* list, int price, char* brand, int year)
{
    node *new = (node*) malloc(sizeof(node));
    if (new == NULL)
    {
        printf("Erro na alocacao.\n");
        exit(0);
    }
    new->price = price;
    new->brand = malloc(15*sizeof(char));
    new->brand = brand;
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
            printf("\nMarca: \"%s\"\n", tmp->brand);
            printf("Ano: %i\n", tmp->year);
            printf("Preco: %i\n", tmp->price);
            tmp = tmp->nxt;
        }
    }
}

int length(LIST* list)
{
    if ((*list) == NULL)
    {
        return 0;
    }
    else
    {
        int len = 1;
        node *tmp;
        tmp = (*list);
        while (tmp->nxt != NULL)
        {
            len++;
            tmp = tmp->nxt;
        }
        return len;
    }
}

void show_plist(LIST* list, int p)
{
    int len = length(list);
    if (len == 0) printf("\nLista está vazia...\n");
    else
    {
        int *checked = malloc(len*sizeof(int));
        for (int i = 0; i < len; i++) checked[i] = 0;
        int escape;
        do
        {
            escape = 1;
            for (int i = 0; i < len; i++) if (checked[i] == 0) escape = 0;
            int smallest = -1;
            node *tmp;
            tmp = (*list);
            int checker = -1;
            for (int i = 0; i < len; i++)
            {
                if ((smallest == -1) && (!checked[i]))
                {
                    smallest = tmp->price;
                    checker = i;
                } 
                else if ((smallest != -1) && (!checked[i]))
                {
                    if (tmp->price < smallest)
                    {
                        checker = i;
                        smallest = tmp->price;
                    }
                }
                tmp = tmp->nxt;
            }
            checked[checker] = 1;
            tmp = (*list);
            for (int i = 0; i < len; i++)
            {
                if (tmp->price < p)
                {
                    if (i == checker)
                    {
                        printf("\nMarca: \"%s\"\n", tmp->brand);
                        printf("Ano: %i\n", tmp->year);
                        printf("Preco: %i\n", tmp->price);
                    }
                    
                }
                tmp = tmp->nxt;
            }
        } while (!escape);
        
    }
}

int main()
{
    // code,title,year...
    int op = -1;
    LIST *list = c_list();
    // Checks if file exists.
    FILE *f = fopen("carros.txt", "r+");
    if (f != NULL)
    {
        while (!feof(f))
        {
            int price, year;
            char *brand = malloc(255*sizeof(char));
            fscanf(f, "%i", &price); 
            fgetc(f);
            fscanf(f, "%[^,]s", brand);
            fgetc(f);
            fscanf(f, "%i", &year);
            fgetc(f);
            add_end(list, price, brand, year);   
        }
    }
    //
    while (op != 0)
    {
        printf("\nInsira uma opcao:\n");
        printf("1 - Inserir novo carro.\n");
        printf("2 - Ver carros (por preco).\n");
        printf("0 - Sair.\n");
        scanf("%i", &op);
        if (op == 1)
        {
            int price, year;
            char *brand = malloc(15*sizeof(char));
            printf("Insira a marca do carro (15 MAX): ");
            while (getchar() != '\n');
            scanf("%[^\n]s", brand);
            printf("Insira o ano do carro: ");
            scanf("%i", &year);
            printf("Insira o preco do carro: ");
            scanf("%i", &price);
            add_end(list, price, brand, year);
        }
        else if (op == 2)
        {
            int p;
            printf("Insira o o valor P:\n");
            scanf("%i", &p);
            show_plist(list, p);
        }
    }
    printf("Salvando livros...\n");
    FILE *fsave = fopen("carros.txt", "w");
    node *tmp = (*list);
    while (tmp != NULL)
    {
        fprintf(fsave, "%i", tmp->price);
        fprintf(fsave, "%c", ',');
        fprintf(fsave, "%s", tmp->brand);
        fprintf(fsave, "%c", ',');
        fprintf(fsave, "%i", tmp->year);
        if (tmp->nxt != NULL) fprintf(fsave, "%c", ',');
        tmp = tmp->nxt;
    }
    printf("Saindo...\n");
    fclose(fsave);

    return 0;
}