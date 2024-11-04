#include <ctype.h>
#include <string.h>

#include "shared.hpp"

void skip_whitespaces (char *str, int len) {
    if (len < 0) 
        len = strlen (str);
    while (len) {
        if (isspace(str[len - 1])) {
            --len;
        }else {
            break;
        }
    }
    str[len] = '\0';
}