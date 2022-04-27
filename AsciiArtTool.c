#include <stdio.h>
#include "RLEList.h"
#include <stdlib.h>


#define MAX_SIZE 256

RLEList asciiArtRead(FILE* in_stream)
{
    if(in_stream==NULL)
    {
        return NULL;
    }

    char *reader;
    RLEList list=RLEListCreate();
    if(fscanf(in_stream, "%s", reader)!=EOF)
    {
        return NULL;
    }

    while (*reader)
    {
        RLEListAppend(list,*reader);
        reader++;
    }
    return list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if(list==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList tmp=list;
    RLEListResult result;
    char *arr=malloc(sizeof(*arr)* RLEListSize(tmp)+1);
    if(arr==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    for (int i = 0; i < RLEListSize(tmp)-1; i++)
    {
        arr[i]= RLEListGet(list,i,&result);
    }
    if(fputs(arr,out_stream)>0)
    {
        free(arr);
        return RLE_LIST_SUCCESS;
    }
    else
    {
        free(arr);
        return RLE_LIST_ERROR;
    }
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(list==NULL||out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result=RLE_LIST_NULL_ARGUMENT;
    char *arr=RLEListExportToString(list,&result);
    if(arr==NULL)
        return RLE_LIST_NULL_ARGUMENT;
    if(fputs(arr,out_stream)!=EOF)
    {
        free(arr);
        return RLE_LIST_ERROR;
    }
    else
    {
        free(arr);
        return RLE_LIST_SUCCESS;
    }
}
