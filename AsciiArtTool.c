//
// Created by momok on 4/26/2022.
//


#include <stdio.h>
#include <RLEList.h>
#include <RLEList.c>

#define MAX_SIZE 256///////////////////////////مش متاكد بس من ها الرقم


RLEList asciiArtRead(FILE* in_stream)
{
    if(in_stream==NULL)
    {
        return NULL;
    }
    char read_string[MAX_SIZE];
    RLEList list=RLEListCreate();
    char *letter=fgets(read_string, MAX_SIZE, in_stream);

    while (letter!=0)
    {
        RLEListAppend(list,*letter);
        letter=fgets(read_string, MAX_SIZE, in_stream);
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
    while(tmp!=NULL)
    {
        char c =tmp->letter;
        fputs(&c,out_stream);
        tmp=tmp->next_letter;
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(list==NULL||out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result=RLE_LIST_NULL_ARGUMENT;
    char *arr=RLEListExportToString(list,&result);

    if(fputs(arr,out_stream)<0)
        return RLE_LIST_ERROR;
    else
        return RLE_LIST_SUCCESS;


}


