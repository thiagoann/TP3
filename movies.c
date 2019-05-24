/*****************************************************************/
/*           Movies | PROG2 | MIEEC | 2018/19                */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "movies.h"

//Declaracao funcoes auxiliares//

//////   Implementacao Tabela de Dispersão - Clientes  ///////
colecaoClientes *colecaoClientesNova(int tamanho)
{
    /* aloca memoria para a estrutura tabela_dispersao */

    colecaoClientes *t = (colecaoClientes *)malloc(sizeof(colecaoClientes));
    if (t == NULL)
        return NULL;

    /* aloca memoria para os elementos */
    t->elementos = (elementoCliente **)calloc(tamanho, sizeof(elementoCliente *));
    if (t->elementos == NULL)
    {
        free(t);
        return NULL;
    }

    t->tamanho = tamanho;

    return t;
}

void colecaoClientesApaga(colecaoClientes *td)
{
    int i;
    elementoCliente *elem, *aux;

    if (td == NULL)
        return;

    /* para cada entrada na tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        /* e enquanto existirem elementos nessa entrada */
        elem = td->elementos[i];
        while (elem != NULL)
        {
            /* liberta cada elemento */
            aux = elem->proximo;
            vetor_apaga(elem->clien->vistos);
            free(elem->clien->username);
            elem->clien->username = NULL;
            free(elem->clien);
            free(elem);
            elem = aux;
        }
    }

    /* liberta vector e estrutura */
    free(td->elementos);
    free(td);
}

int clienteAdiciona(colecaoClientes *td, const char *username, unsigned int filmId)
{
    /*
    //Se a table for NULL ou username for NULL ou filmId for 0, return -1.
    if (td == NULL || username == NULL || filmId < 0)
    {
        return -1;
    }
    cliente *newClient;
    elementoCliente *elements;
    int posicao = 0;
    //Se a filmId já foi vista, sai do ciclo. Caso contrário, adiciona.

    /**Perguntar se pode usar outro ficheiro e se o filme pode existir
     * mais de uma vez.
     */
    /*Enquanto o vetor de elementos for diferente de NULL*/
    /*
    while (elements != NULL)
    {
        if (strcmp(elements->clien->username, username) == 0)
        {
            int filmExiste = 0;
            //Se o cliente já existe e já viu o filme...
            for (int i = 0; i < elements->clien->vistos; i++)
            {
                int filmeIdAtual = elements->clien->vistos->elementos[i];
                /*Percorrendo vetor*/
    /*
                if (filmId == filmeIdAtual)
                {
                    filmExiste = 1;
                }
            }
            
            if (filmExiste = 1)
            {
                return 0;
            }
            if (filmId == 0)
            {
                return 0;
            }
            vetor_insere(elements->clien->vistos, filmId, -1);
        }
    }
    /*Senão...*/
    /*
    hash_cliente(username, newClient->vistos->tamanho);
    vetor_insere(new)
*/
    return 0;
}

int clienteRemove(colecaoClientes *td, const char *username)
{
    int index;
    elementoCliente *elem, *aux;

    if (!td)
        return -1;

    /* calcula hash para a string a remover */
    index = hash_cliente(username, td->tamanho);

    elem = td->elementos[index];
    aux = NULL;

    /* para cada elemento na posicao index */
    while (elem != NULL)
    {
        /* se for a string que se procura, e' removida */
        if (strcmp(elem->clien->username, username) == 0)
        {
            /* se nao for a primeira da lista */
            if (aux != NULL)
                aux->proximo = elem->proximo;
            else
                td->elementos[index] = elem->proximo;
            free(elem->clien);
            free(elem);

            return 1;
        }

        aux = elem;
        elem = elem->proximo;
    }
    return 0;
}

/*Exercicio 2 - FEITO!!!*/
int colecaoNumClientes(colecaoClientes *td)
{
    if (td == NULL)
    {
        return -1;
    }
    int j;
    elementoCliente *searchClient = (elementoCliente *)malloc(sizeof(elementoCliente));
    int numClients = 0;

    if(searchClient == NULL){
        free(searchClient);
    }

    for (j = 0; j < td->tamanho; j++)
    {
        searchClient = td->elementos[j];
        while (searchClient != NULL)
        {
            searchClient = searchClient->proximo;
            numClients++;
        }
    }
    return numClients;
}

int clienteExiste(colecaoClientes *td, const char *username)
{
    if (td == NULL)
    {
        return -1;
    }
    int key = hash_cliente(username, td->tamanho);
    elementoCliente *verifCliente = td->elementos[key];
    int k;
    if(td->elementos[key] == NULL){
        free(td);
    }
    //Percorre tabela

    while (verifCliente != NULL)
    {

        if (strcmp(verifCliente->clien->username, username) == 0)
        {
            //Se os nomes batem um com o outro, retorna 1
            return 1;
        }
        //Senão, retorna 0
        else
        {
            return 0;
        }
    }
}

unsigned long hash_cliente(const char *username, int tamanho)
{
    int c, t = strlen(username);
    unsigned long hash = 7;

    for (c = 0; c < t; c++)
    {
        hash += (int)username[c] * powf(2, c);
    }

    return hash % tamanho;
}

/*================================================================================*/
void mostraTabela(colecaoClientes *td)
{
    int i;
    elementoCliente *elem;

    printf("TABELA DE CLIENTES (%d Clientes)\n", colecaoNumClientes(td));
    for (i = 0; i < td->tamanho; i++)
    {
        if (td->elementos[i])
        {
            printf("\t[%2d]", i);
            elem = td->elementos[i];
            while (elem)
            {
                printf(" : [\"%s\" Filmes: ", elem->clien->username);
                if (elem->clien->vistos->tamanho > 0)
                {

                    for (int j = 0; j < elem->clien->vistos->tamanho; j++)
                    {
                        printf(" (%d)", elem->clien->vistos->elementos[j]);
                    }
                }
                printf("]");
                elem = elem->proximo;
            }
            printf("\n");
        }
    }
    printf("\n");
}

///////////////////////////////////////////////////

/* inserir um Novo Filme*/
int inserirNovoFilme(colecaoFilmes *colecFilmes, char *titulo, char *categoria, int filmId, float rating)
{
    colecFilmes = (colecaoFilmes*) malloc(sizeof(colecaoFilmes));
    if (colecFilmes == NULL || titulo == NULL || categoria == NULL || filmId < 0 || rating < 0)
    {   
        free(colecFilmes);
        return -1;
        
    }
    int cont;
    filme *newMovie;
    for (cont = 0; cont < colecFilmes->tamanhoFilm; cont++)
    {
        //Insere no vetor
        vetor_insere(newMovie->film, )
        colecFilmes->film->categoria = categoria;
        colecFilmes->film->filmId = filmId;
        colecFilmes->film->rating = rating;
    }
    if (colecFilm->film->filmId == filmdId)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

colecaoFilmes *filmesCarrega(const char *nomeFicheiro)
{
    FILE *f;
    nomef = "filmeShort.txt";
    f = fopen("fi")

        return NULL;
}

// Remover um filme///
int removerFilme(colecaoFilmes *colecFilmes, colecaoClientes *td, int filmId)
{
    if (colecFilmes == NULL || td == NULL || filmId < 0)
    {
        return -1;
    }
    elementoCliente *watched = (elementoCliente*)malloc(sizeof(elementoCliente));
    filme *movie = (filme*)malloc(sizeof(filme));
    int contClient;
    int contFilm;
    
    while (watched!= NULL)
    {
        if(colecFilmes->film->filmId == filmId){
            if(watched->clien->)
        }
    }
    
    }

// Remover a estrutura colecaoFilmes
void colecaoFilmesApaga(colecaoFilmes *colecFilmes, colecaoClientes *td)
{
    // resolução do exercicio 8
}

//Sugestões //////////////////////////////

vetor *sugestoes(colecaoFilmes *colecFilmes, colecaoClientes *td, char *username, int nFilmes, float limiar)
{
    // resolução do exercicio 9
    return NULL;
}

///////////////////////////////////////
