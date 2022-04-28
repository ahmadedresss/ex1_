#include <stdio.h>
#include <string.h>
#include "mm_malloc.h"

#define ROW_DOWN '\n'

typedef char (*MapFunction)(char);
typedef enum {
    RLE_LIST_SUCCESS,
    RLE_LIST_OUT_OF_MEMORY,
    RLE_LIST_NULL_ARGUMENT,
    RLE_LIST_INDEX_OUT_OF_BOUNDS,
    RLE_LIST_ERROR
} RLEListResult;

typedef struct RLEList_t {
    char letter;
    int appearances;
    struct RLEList_t* next_letter;
} *RLEList;

int countSize(RLEList list);
int nodesCounter(RLEList list);

RLEList RLEListCreate()
{
    RLEList ptr=malloc(sizeof(*ptr));
    if(ptr==NULL)
        return 0;
    ptr->next_letter=NULL;
    ptr->appearances=1;
    return ptr;
}

RLEListResult RLEListAppend (RLEList list,char value)
{

    if(list==NULL)
        return RLE_LIST_NULL_ARGUMENT;

    RLEList temp= list;

    while(temp->next_letter!=NULL)
    {
        temp=temp->next_letter;
    }

    if(temp->letter==value)
    {
        temp->appearances++;
        return RLE_LIST_SUCCESS;
    }
    else
    {
        RLEList newHead = RLEListCreate();
        if (newHead==NULL)
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        newHead->letter = value;
        temp->next_letter = newHead;

        return RLE_LIST_SUCCESS;
    }
}

void RLEListDestroy(RLEList list)
{
    while (list->next_letter!=NULL)
    {
        RLEList toDelete=list;
        list=list->next_letter;
        toDelete->next_letter=NULL;
        free(toDelete);
    }

   /* if(nodesCounter(list)==1)
    {
        list->next_letter=NULL;
        free(list);
    }
*/
}

int RLEListSize(RLEList list)
{
    if(list==NULL)
        return -1;

    RLEList tmp=list;
    int sum=0;
    while(tmp!=NULL)
    {
        sum+=tmp->appearances;
        tmp=tmp->next_letter;
    }
    return sum-1;
}

RLEListResult RLEListRemove(RLEList list, int index)
{

    int sum=0;
    if(list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index >= RLEListSize(list)|| index<0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    if(list->next_letter!=NULL)
    {
        RLEList prev =list;
        RLEList fwr=list->next_letter ;
        sum += fwr->appearances;
        while (sum <= index)
        {
            fwr = fwr->next_letter;
            sum += fwr->appearances;
        }
        fwr->appearances--;
        if (fwr->appearances == 0)
        {
            //now we have three options
            if (fwr->next_letter == NULL)
            {
                while (prev->next_letter != fwr)
                {
                    prev = prev->next_letter;
                }
                prev->next_letter = NULL;
                free(fwr);
            }
            else if (fwr->next_letter != NULL && fwr != list->next_letter) {
                while (prev->next_letter != fwr) {
                    prev = prev->next_letter;
                }
                RLEList fwr2 = fwr->next_letter;
                if (prev->letter == fwr2->letter)
                {
                    prev->appearances += fwr2->appearances;
                    prev->next_letter = fwr2;
                    fwr->next_letter = NULL;
                    free(fwr);

                    if (fwr2->next_letter == NULL)
                    {
                        prev->next_letter=NULL;
                        free(fwr2);
                    } else {
                        prev->next_letter = fwr2->next_letter;
                        fwr2->next_letter = NULL;
                        free(fwr2);
                    }
                }
                else
                {
                    prev->next_letter = fwr->next_letter;
                    fwr->next_letter = NULL;
                    free(fwr);
                }
            }
            else if (index == 0)
            {
                list->next_letter = fwr->next_letter;
                fwr->next_letter = NULL;
                free(fwr);
            }
        }
    }
    return  RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index ,RLEListResult *result)
{

    if(list== NULL)
    {
        if(result == NULL)
        {
            return 0;
        }
        else
        {
            *result = RLE_LIST_NULL_ARGUMENT;
            return 0;
        }
    }

    if(index >= RLEListSize(list)||index<0)
    {
        if(result==NULL)
        {
            return 0;
        }
        else
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
            return 0;
        }
    }
    RLEList temp;
    temp=list->next_letter;

    int sum=0;
    while(temp!=NULL)
    {
        sum+=temp->appearances;
        if (index <= sum-1)
        {
            if(result==NULL)
            {
                return temp->letter;
            }
            else
            {
                *result = RLE_LIST_SUCCESS;
                return temp->letter;
            }
        }
        else
        {
            temp=temp->next_letter;
        }
    }
    return 0;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(list==NULL||map_function==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList tmp=list;
    while(tmp!=NULL)
    {
        tmp->letter=map_function(tmp->letter);
        tmp=tmp->next_letter;
    }
    return RLE_LIST_SUCCESS;
}
/*
char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if(list==NULL)
    {
        *result=RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int arrSize=(countSize(list))+(2* RLEListSize(list))+1;

    char *arr= malloc(sizeof(char)*arrSize);
    unsigned int i;
    RLEList tmp=list->next_letter;
    while(tmp!=NULL)
    {
        char value=tmp->letter;
        int occurrences=tmp->appearances;
        i= strlen(arr);
        sprintf(&arr[i],"%c",value);
        i= strlen(arr);
        sprintf(&arr[i],"%d",occurrences);
        i= strlen(arr);
        sprintf(&arr[i],"\n");
        tmp=tmp->next_letter;
    }
    *result=RLE_LIST_SUCCESS;
    return arr;
}

*/
char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if(list==NULL)
    { if(result!=NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int digits=countSize(list);
    int nodes=nodesCounter(list);
    char *str= malloc(sizeof(*str)*1+1);
    if(nodes==1)
    {
        if(result!=NULL)
        {
            *result=RLE_LIST_SUCCESS;
        }

        str[0]='\0';
        return str;
    }

    int arrSize=(digits)+(2*nodes);

    char *arr= malloc(sizeof(char)*arrSize+1);
    if(arr==NULL)
    {
        return 0;
    }
    for(int i=0;i<arrSize+1;i++)
    {
        arr[i]=0;
    }
    unsigned int i;
    RLEList tmp=list->next_letter;
    while(tmp!=NULL)
    {
        char value=tmp->letter;
        int occurrences=tmp->appearances;
        i= strlen(arr);
        sprintf(&arr[i],"%c",value);
        i= strlen(arr);
        sprintf(&arr[i],"%d",occurrences);
        i= strlen(arr);
        sprintf(&arr[i],"\n");
        tmp=tmp->next_letter;
    }
    if(result!=NULL)
    {
        *result = RLE_LIST_SUCCESS;
    }
    return arr;
}
int countSize(RLEList list)
{
    if(list==NULL)
        return RLE_LIST_NULL_ARGUMENT;
    int counter=0;
    int appearances;
    RLEList tmp=list;
    while(tmp!=NULL)
    {
        appearances=tmp->appearances;
        while(appearances>0)
        {
            counter++;
            appearances=appearances/10;
        }
        tmp=tmp->next_letter;
    }
    return counter;
}
int nodesCounter(RLEList list)
{
    RLEList tmp=list;
    int counter=0;
    while (tmp!=NULL)
    {
        counter++;
        tmp=tmp->next_letter;
    }
    return counter;
}
