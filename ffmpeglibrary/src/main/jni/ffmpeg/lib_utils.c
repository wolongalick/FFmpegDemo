//
// Created by alick on 2018/11/27.
//

#include "lib_utils.h"

char *buildStr(char *str1, char *str2) {
    char *result = malloc(strlen(str1) + strlen(str2));
    sprintf(result, "%s%s", str1, str2);
    return result;
}

