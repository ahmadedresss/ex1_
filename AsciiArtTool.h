//
// Created by momok on 4/26/2022.
//

#ifndef RLELIST_C_ASCIIARTTOOL_H
#define RLELIST_C_ASCIIARTTOOL_H


#include <stdio.h>
#include <stdbool.h>



typedef enum {
    RLE_LIST_SUCCESS,
    RLE_LIST_OUT_OF_MEMORY,
    RLE_LIST_NULL_ARGUMENT,
    RLE_LIST_INDEX_OUT_OF_BOUNDS,
    RLE_LIST_ERROR
} RLEListResult;


RLEList asciiArtRead(FILE* in_stream);
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif //RLELIST_C_ASCIIARTTOOL_H
