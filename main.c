//Predescu Ioan-Alxandru 313cb
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct director
{
    char *nume;
    struct director *st, *dr;
    struct director *parinte;
    struct fisier *files;
    struct director *directories;

} Tdir;

typedef struct fisier
{
    char *nume;
    struct fisier *st, *dr;
    struct director *parinte;
} Tfis;


void free_fis(Tfis*a)
{
    if(a!=NULL)
    {
        free_fis(a->dr);
        free_fis(a->st);
        free(a->nume);
        free(a);
    }
}
void free_tot(Tdir*a)
{
    if(a!=NULL)
    {
        free_tot(a->directories);
        free_tot(a->st);
        free_tot(a->dr);
        free_fis(a->files);
        free(a->nume);
        free(a);
    }
}


void SRD_dir(Tdir *a)
{
    if (a)
    {
        if (a->st)
            SRD_dir(a->st);
        printf("%s ", a->nume);
        if (a->dr)
        SRD_dir(a->dr);
    }
}

void SRD_fis(Tfis *a)
{
    if (a)
    {
        if (a->st)
            SRD_fis(a->st);
        printf("%s ", a->nume);
        if (a->dr)
            SRD_fis(a->dr);
    }
}

int LS(Tdir *c)
{
    SRD_dir(c->directories);
    SRD_fis(c->files);
    printf("\n");
    return 0;
}

Tdir *Fr_dir(char *a)
{
    Tdir *x = malloc(sizeof(Tdir));
    if (!x)
        {
            return NULL;
        }
    x->nume = malloc(sizeof(char) * 50);
    if(!x->nume)
    {
        return NULL;
    }
    memcpy(x->nume, a, 50);
    x->st = NULL;
    x->dr = NULL;
    x->directories = NULL;
    x->parinte=NULL;
    x->files=NULL;
    return x;
}

Tfis *Fr_fis(char *a)
{
    Tfis *x = malloc(sizeof(Tfis));
    if (!x)
        {
            return NULL;
        }
    x->nume = malloc(sizeof(char) * 50 );
        if(!x->nume)
        {
            return NULL;
        }
    memcpy(x->nume, a, 50);
    x->st = NULL;
    x->dr = NULL;
    x->parinte=NULL;
    return x;
}
int exista_fis(Tfis *a, char *x)
{
    if (a == NULL)
        return 0;
    if (strcmp(a->nume, x) == 0)
        return 1;
    if (strcmp(x, a->nume) > 0)
        return exista_fis(a->dr, x);
    else if (strcmp(x, a->nume) < 0)
        return exista_fis(a->st, x);
}
int exista_dir(Tdir *a, char *x)
{
    if (a == NULL)
        return 0;
    if (strcmp(a->nume, x) == 0)
        return 1;
    if (strcmp(x, a->nume) > 0)
        return exista_dir(a->dr, x);
    else if (strcmp(x, a->nume) < 0)
        return exista_dir(a->st, x);
}

int Inserare_touch(Tfis **a, char *x, Tdir *b)
{
    if (*a == NULL)
    {
        *a = Fr_fis(x);
        if (*a == NULL)
            return -1;
        (*a)->parinte = b;
    }
    if (strcmp((*a)->nume, x) > 0)
        Inserare_touch(&((*a)->st), x, b);
    else if (strcmp((*a)->nume, x) < 0)
        Inserare_touch(&((*a)->dr), x, b);
}

int Inserare_mkdir(Tdir **a, char *x, Tdir *b)
{
    if (*a == NULL)
    {
        *a = Fr_dir(x);
        if (*a == NULL)
            return -1;
        (*a)->parinte = b;
    }
    if (strcmp(x, (*a)->nume) > 0)
    {
        Inserare_mkdir(&((*a)->dr), x, b);
    }
    else if (strcmp((*a)->nume, x) > 0)
        Inserare_mkdir(&((*a)->st), x, b);
}
void RM(Tfis **a, char *x, Tfis **aux, Tdir *b)
{
    if ((*a) != NULL)
    {
        if ((*a)->st)
            RM(&((*a)->st), x, &(*aux), b);
        if (strcmp(x, (*a)->nume) != 0)
            Inserare_touch(&(*aux), (*a)->nume, b);
        if ((*a)->dr)
            RM(&((*a)->dr), x, &(*aux), b);
    }

}

void RMDIR(Tdir **a, char *x, Tdir **aux, Tdir *b)
{
    if (*a)
    {
        if ((*a)->st)
            RMDIR(&(*a)->st, x, &(*aux), b);
        if (strcmp(x, (*a)->nume) != 0)
            Inserare_mkdir(&(*aux), (*a)->nume, b);
        if ((*a)->dr)
            RMDIR(&((*a)->dr), x, &(*aux), b);
    }
}

void CD(Tdir *a, char *x, Tdir **b)
{
    if (a)
    {
        if (strcmp(a->nume, x) == 0)
        {
            *b = a;
            return;
        }
        else if (strcmp(a->nume, x) < 0)
            CD(a->dr, x, b);
        if (strcmp(a->nume, x) > 0)
            CD(a->st, x, b);
    }
}

void PWD(Tdir *a)
{
    if (strcmp(a->nume, "root") == 0)
        printf("/root");
    else
    {
        PWD(a->parinte);
        printf("/%s", a->nume);
    }
}
int exista_dir_in_tot(Tdir *a, char *x)
{
    if (a == NULL)
        return 0;
    if (exista_dir(a->directories, x) == 1)
    {
        printf("Directory %s found!\n", x);
        PWD(a);
        printf("/%s", x);
        printf("\n");
    }
    return exista_dir(a->directories, x) +
           exista_dir_in_tot(a->st, x) +
           exista_dir_in_tot(a->dr, x) +
           exista_dir_in_tot(a->directories, x);
}
int exista_fis_in_tot(Tdir *a, char *x)
{
    if (a == NULL)
        return 0;
    if (exista_fis(a->files, x) == 1)
    {
        printf("File %s found!\n", x);
        PWD(a);
        printf("\n");
    }
    return exista_fis(a->files, x) +
           exista_fis_in_tot(a->st, x) +
           exista_fis_in_tot(a->dr, x) +
           exista_fis_in_tot(a->directories, x);
}


int main()
{
    char *line = NULL, *s=NULL;
    size_t len = 0;
    Tdir *root = malloc(sizeof(Tdir));
    if (!root)
    {
        return 0;
    }
    root->parinte = NULL;
    root->files = NULL;
    root->st = NULL;
    root->dr = NULL;
    root->directories = NULL;
    root->nume = malloc(10 * sizeof(char));
    if (!root->nume)
    {
        return 0;
    }
    strcpy(root->nume, "root");
    Tdir *curent = root;
    while (getline(&line, &len, stdin) != -1)
    {
        s = strtok(line, " \n");
        if (strcmp(s, "touch") == 0)
        {
            s = strtok(NULL, " \n");
            if (exista_dir(curent->directories, s) == 1)
                printf("Directory %s already exists!\n", s);
            else if (exista_fis(curent->files, s) == 1)
                printf("File %s already exists!\n", s);
            else
                Inserare_touch(&(curent->files), s, curent);
        }
        if (strcmp(s, "ls") == 0)
        {
            LS(curent);
        }
        if (strcmp(s, "mkdir") == 0)
        {
            s = strtok(NULL, "\n");
            if (exista_fis(curent->files, s) == 1)
                printf("File %s already exists!\n", s);
            else if (exista_dir(curent->directories, s) == 1)
                printf("Directory %s already exists!\n", s);
            else
                Inserare_mkdir(&(curent->directories), s, curent);
        }
        if (strcmp(s, "rm") == 0)
        {
            Tfis *aux = NULL;
            s = strtok(NULL, " \n");
            if (exista_fis(curent->files, s) == 0)
                printf("File %s doesn't exist!\n", s);
            else
            {
                RM(&(curent->files), s, &aux, curent);
                free_fis(curent->files);
                curent->files = aux;
            }
        }
        if (strcmp(s, "rmdir") == 0)
        {
            Tdir *aux = NULL;
            s = strtok(NULL, " \n");
            if (exista_dir(curent->directories, s) == 0)
                printf("Directory %s doesn't exist!\n", s);
            else
            {
                RMDIR(&(curent->directories), s, &aux, curent);
                free_tot(curent->directories);
                curent->directories = aux;
            }
        }
        if (strcmp(s, "cd") == 0)
        {
            s = strtok(NULL, " \n");
            if (strcmp(s, "..") == 0)
                curent = curent->parinte;
            else if (exista_dir(curent->directories, s) == 0)
                printf("Directory not found!\n");
            else
                CD(curent->directories, s, &curent);
        }
        if (strcmp(s, "pwd") == 0)
        {
            PWD(curent);
            printf("\n");
        }
        if (strcmp(s, "find") == 0)
        {
            s = strtok(NULL, " \n");
            if (strcmp(s, "-f") == 0)
            {
                s = strtok(NULL, " \n");
                if (exista_fis_in_tot(root, s) == 0)
                    printf("File %s not found!\n", s);
            }
            if (strcmp(s, "-d") == 0)
            {
                s = strtok(NULL, " \n");
                if (exista_dir_in_tot(root, s) == 0)
                    printf("Directory %s not found!\n", s);
            }
        }
        if (strcmp(s, "quit") == 0)
            break;
    }
    free_tot(root);
    free(line);
    return 0;
}