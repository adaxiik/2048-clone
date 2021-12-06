#include "../../include/game/argsParse.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
void ParseArgs(Settings *settings, int count, char *argv[]){
    
    for (int i = 1; i < count-1; i++)
    {
        for (int j = 0; j < strlen(argv[i]); j++)
        {
            argv[i][j] = tolower(argv[i][j]);
        }

        if(!strcmp("-r",argv[i]))
            settings->RC.y=ConvertToInt(argv[i+1],RC);
        else if(!strcmp("-c",argv[i]))
            settings->RC.x=ConvertToInt(argv[i+1],RC);
        else if(!strcmp("-w",argv[i]))
            settings->resolution.x=ConvertToInt(argv[i+1],RES);
        else if(!strcmp("-h",argv[i]))
            settings->resolution.y=ConvertToInt(argv[i+1],RES);
    } 
}

int ConvertToInt(char text[],ArgType type){
    int out;
    sscanf(text,"%d",&out);

    if(!out)
        Error("Invalid parameter");

    switch (type)
    {
    case RES:
        if(out>10000||out<50)
            Error("Resolution must be greater than 49 and less than 10 001");
        break;
    case RC:
        if(out<2||out>50)
            Error("Game size must be greater than 1 and less then 51");
        break;
    default:
        Error("Unexpected Error");
        break;
    }

    return out;
}

void Error(char text[]){
    fprintf(stderr,"%s\n",text);
    exit(1);
}