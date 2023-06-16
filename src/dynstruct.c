#include <dynstruct.h>
#include <stdlib.h>


void dynstring_init(Dynstring* pstr, int initsize)
{
    if(pstr)
    {
        pstr->data = (char *)malloc(sizeof(char) * initsize);
        if(pstr->data == NULL)
        {
            printf("pstr malloc failed\n");
            return;
        }
        pstr->capacity = initsize;
        pstr->count = 0;
    }
    else
    {
        printf("pstr is NULL!\n");
    }
}

void dynstring_free(Dynstring* pstr)
{
    if(pstr)
    {
        if(pstr->data)
        {
            free(pstr->data);
        }
        pstr->capacity = 0;
        pstr->count = 0;
    }
}

void dynstring_reset(Dynstring* pstr)
{
    dynstring_free(pstr);
    dynstring_init(pstr, 8);
}

void dynstring_realloc(Dynstring* pstr, int newsize)
{
    int capacity;
    char *data = NULL;
    capacity = pstr->capacity;
    while (capacity < newsize)
    {
        capacity *= 2;
    }
    data = realloc(pstr->data, capacity);
    if(!data)
    {
        printf("realloc failed!\n");
        return;
    }
    pstr->capacity = capacity;
    pstr->data = data;
}

void dynstring_addchar(Dynstring* pstr, int ch)
{
    int count;
    count = pstr->count + 1;
    if(count > pstr->capacity)
    {
        dynstring_realloc(pstr, count);
    }
    ((char *)pstr->data)[count - 1] = ch;
    pstr->count = count;
}


void dynarr_realloc(DynArray* parr, int newsize)
{
    int capacity;
    void* data;
    capacity = parr->capacity;
    while(capacity < newsize)
    {
        capacity *= 2;
    }
    data = realloc(parr->data, capacity);       //only update pointer array
    if(!data)
    {
        printf("realloc error!\n");
        return;
    }
    parr->capacity = capacity;
    parr->data = data;
}

void dynarr_add(DynArray* parr, void* data)
{
    int count = parr->count + 1;
    if(count * sizeof(void *) > parr->capacity)
    {
        dynarr_realloc(parr, count*sizeof(void*));
    }
    parr->data[count - 1] = data;
    parr->count = count;
}

void dynarr_init(DynArray* parr, int initsize)
{
    if(parr)
    {
        parr->data = (void**)malloc(sizeof(void*) * initsize);
        parr->capacity = initsize;
        parr->count = 0;
    }
    else
    {
        printf("dynarr_init failed, malloc failed!\n");
    }
}

void dynarr_free(DynArray* parr)
{
    void **p = parr->data;
    for(; parr->count != 0; p++)
    {
        if(*p)
        {
            free(*p);
            *p = NULL;
            parr->count--;
        }
    }
    free(parr->data);
    parr->data = NULL;
}

int dynarr_search(DynArray* parr, int key)
{
    int i = 0;
    int **p = (int**)parr->data;
    for(; i < parr->count; i++)
    {
        if(**p == key)
        {
            return i;
        }
        p++;
    }
    return -1;
}
