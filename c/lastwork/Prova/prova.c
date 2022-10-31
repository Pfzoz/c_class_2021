#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char *name;
    char type;
    int order;
    char attended;
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

void easy_sort(LIST* list)
{
    if ((*list) == NULL)
    {
        printf("\n");
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
                if (next->order < tmp->order)
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



void type_sort(LIST* list)
{
    if ((*list) != NULL)
    {
        
        int intercalated;
        do
        {
            node *tmp;
            node *previous;
            tmp = (*list);
            previous = (*list);
            int ptime = 1;
            intercalated = 1;
            node *pguy;
            int catched = 0;
            //check intercalation
            while (tmp != NULL)
            {
                if (ptime)
                {
                    if (tmp->type != 'P')
                    {
                        node *seeker;
                        seeker = tmp->nxt;
                        intercalated = 1;
                        while (seeker != NULL)
                        {
                            if (seeker->type == 'P')
                            {
                                intercalated = 0;
                                break;
                            }
                            seeker = seeker->nxt;
                        } 
                        if (intercalated) break;
                    }
                    ptime = 0;
                }
                else
                {
                    if (tmp->type != 'N')
                    {
                        node *seeker;
                        seeker = tmp->nxt;
                        intercalated = 1;
                        while (seeker != NULL)
                        {
                            if (seeker->type == 'N')
                            {
                                intercalated = 0;
                                break;
                            }
                            seeker = seeker->nxt;
                        } 
                        if (intercalated) break;
                    }
                    ptime = 1;
                }
                if (intercalated == 0 && catched == 0 && tmp->type == 'P')
                {
                    catched = 1;
                    pguy = tmp;
                    previous->nxt = tmp->nxt;
                    break;
                }
                else if (tmp->nxt != NULL)
                {
                    if (intercalated == 0 && catched == 0 && tmp->nxt->type == 'P')
                    {
                        catched = 1;
                        pguy = tmp->nxt;
                        tmp->nxt = tmp->nxt->nxt;
                        break;
                    }
                }
                previous = tmp;
                tmp = tmp->nxt;
            }
            //
            if (!intercalated)
            {
                show_list(list);
                catched = 0;
                tmp = (*list);
                previous = (*list);
                ptime = 1;
                int changedo = 0;
                while (tmp != NULL)
                {
                    if (ptime)
                    {
                        if (tmp->type != 'P')
                        {
                            if (previous == (*list))
                            {
                                pguy->nxt = previous;
                                (*list) = pguy;
                            }
                            else
                            {
                                previous->nxt = pguy;
                                pguy->nxt = tmp;
                            }
                            changedo = 1;
                            break;
                        }
                        ptime = 0;
                    }
                    else
                    {
                        ptime = 1;
                    }
                    previous = tmp;
                    tmp = tmp->nxt;
                }
                if (!changedo)
                {
                    add_end(list, pguy->type, pguy->name, pguy->order, pguy->attended);
                }
            }
            show_list(list);
        } while (!intercalated);
        //


    }
}

void show_list(LIST* list)
{
    if ((*list) == NULL)
    {
        printf("Fila vazia...\n");
    }
    else
    {
        node *tmp;
        tmp = (*list);
        printf("\n");
        while (tmp != NULL)
        {
            if (tmp->attended == 'N')
            {
                printf("%c%i, ", tmp->type, tmp->order);
            }
            
            tmp = tmp->nxt;
        }
        printf("\n\n");
    }
}

void add_end(LIST* list, char type, char* name, int order, char attended)
{
    node *new = (node*) malloc(sizeof(node));
    if (new == NULL)
    {
        printf("Erro na alocacao.\n");
        exit(0);
    }
    new->name = malloc(255*sizeof(char));
    new->name = name;
    new->type = type;
    new->order = order;
    new->attended = attended;
    //

    //   
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

int main()
{
    int op = -1;
    LIST *list = c_list();
    int order = length(list);
    //
    FILE *f = fopen("atendimentos.txt", "r+");
    if (f != NULL)
    {
        while (!feof(f))
        {
            char *name = malloc(255*sizeof(char));
            char type;
            int order;
            char attended;
            fscanf(f, "%[^,]s", name);
            fgetc(f);
            fscanf(f, "%c", &type); 
            fgetc(f);
            fscanf(f, "%i", &order);
            fgetc(f);
            fscanf(f, "%c", &attended);
            fgetc(f);
            add_end(list, type, name, order, attended);
        }
        easy_sort(list);
        type_sort(list);
        if ((*list)->type == NULL)
        {
            (*list) = NULL;
        }
    }
    fclose(f);
    while (op != 4)
    {
        printf("Insira a opcao desejada:\n");
        printf("1 - Retirar Senha\n");
        printf("2 - Exibir Senhas\n");
        printf("3 - Chamar Senha - Atendimento\n");
        printf("4 - Sair\n");
        printf("> ");
        scanf("%i", &op);
        if (op == 1)
        {
            char type;
            char *name = malloc(255*sizeof(char));
            printf("Insira o nome:\n");
            while (getchar() != '\n');
            scanf("%[^\n]s", name);
            printf("Insira o tipo de senha [P/N]:\n");
            scanf(" %c", &type);
            add_end(list, type, name, order++, 'N');
        }
        if (op == 2)
        {
            easy_sort(list);
            show_list(list);
            type_sort(list);
            show_list(list); 
        }
        if (op == 3)
        {
            node *chamarado;
            chamarado = (*list);
            while (chamarado != NULL)
            {
                if (chamarado->attended == 'N') break;
                chamarado = chamarado->nxt;
            }
            if (!(chamarado == NULL || chamarado->attended == 'S'))
            {
                chamarado->attended = 'S';
                FILE *fS = fopen("senha.txt", "w");
                printf("\n*******************************\n");
                printf("*      Agencia  Bancaria      *\n");
                printf("*           SENHA             *\n");
                printf("*           %c%i              *\n", chamarado->type, chamarado->order);
                printf("*          %c%c%c             *\n", chamarado->name[0], chamarado->name[1], chamarado->name[2]);
                printf("*   Fique atento ao painel    *\n");
                printf("*******************************\n\n");
                //
                fprintf(fS, "%s", "*******************************\n");
                fprintf(fS, "%s", "*      Agencia  Bancaria      *\n");
                fprintf(fS, "%s", "*           SENHA             *\n");
                fprintf(fS, "%s", "*           ");
                fprintf(fS, "%c", chamarado->type);
                fprintf(fS, "%i", chamarado->order);
                fprintf(fS, "%s", "              *\n");
                fprintf(fS, "%s", "*          ");
                fprintf(fS, "%c", chamarado->name[0]);
                fprintf(fS, "%c", chamarado->name[1]);
                fprintf(fS, "%c", chamarado->name[2]);
                fprintf(fS, "%s", "             *\n");
                fprintf(fS, "%s", "*   Fique atento ao painel    *\n");
                fprintf(fS, "%s", "*******************************\n");
                fclose(fS);
            }
            else
            {
                printf("Ninguem para chamar...\n");
            }
            
        }
        //DEV AREA
        if (op == 9)
        {
            show_list(list);
        }
        if (op == 10)
        {
            easy_sort(list);
            printf("SORTED.\n");
        }
    }
    printf("Salvando clientes...\n");
    FILE *fsave = fopen("atendimentos.txt", "w");
    node *tmp = (*list);
    while (tmp != NULL)
    {
        fprintf(fsave, "%s", tmp->name);
        fprintf(fsave, "%c", ',');
        fprintf(fsave, "%c", tmp->type);
        fprintf(fsave, "%c", ',');
        fprintf(fsave, "%i", tmp->order);
        fprintf(fsave, "%c", ',');
        fprintf(fsave, "%c", tmp->attended);
        if (tmp->nxt != NULL) fprintf(fsave, "%c", ',');
        tmp = tmp->nxt;
    }
    printf("Saindo...\n");
    fclose(fsave);
    return 0;
}