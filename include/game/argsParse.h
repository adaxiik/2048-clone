#pragma once
#include "game.h"
typedef enum {RES,RC} ArgType;
void ParseArgs(Settings *settings, int count, char *argv[]);
int ConvertToInt(char text[],ArgType type);
void Error(char text[]);