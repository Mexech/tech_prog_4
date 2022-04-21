#ifndef UTILS_H
#define UTILS_H

#include <iostream>

char* random_str(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    char* res = (char*)calloc(len + 1, sizeof(char));

    for (int i = 0; i < len; ++i) {
        res[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return res;
}

#endif