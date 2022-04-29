#include <stdio.h>
#include "RLEList.h"
#include <stdlib.h>
#include "AsciiArtTool.h"


#define MAX_SIZE 256

RLEList asciiArtRead(FILE* in_stream)
{
    if(in_stream==NULL)
    {
        return NULL;
    }

    char reader[MAX_SIZE];
    RLEList list=RLEListCreate();
    if(!list)
    {
        return NULL;
    }
    while(fgets(reader,MAX_SIZE,in_stream) != NULL)
    {
        int i=0;
        while(reader[i])
        {
            RLEListAppend(list,reader[i++]);
        }
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
    char letter =0;
    RLEListResult result;
    for (int i = 0; i < RLEListSize(list); i++)
    {
        letter= RLEListGet(list,i,&result);
        if(result != RLE_LIST_SUCCESS)
        {
            result=RLE_LIST_ERROR;
            return result;
        }
        fputs(&letter,out_stream);
    }
     return result;
}



RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(list==NULL||out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;
    char *arr=RLEListExportToString(list,&result);
    if(arr==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    fprintf(out_stream,arr);
    free(arr);
    return RLE_LIST_SUCCESS;
}
