#include "base_validator.h"

bool check_substr(char *s);

Error dots_count_and_data_check(char* s, int required_dots_count){
    char* copy_s = malloc((strlen(s) + 1) * sizeof(char));
    strcpy(copy_s, s);
    int dot_count = 0;
    char *p;
    while ((p = strchr(copy_s, '.')) != NULL){
        *p = '\0';
        if(!check_substr(copy_s))
            return (Error){true, "argument not a number"};
        copy_s = copy_s + (p-copy_s) + 1;
        dot_count++;
    }
    if(!check_substr(copy_s))
        return (Error){true, "argument not a number"};

    if(dot_count != required_dots_count)
        return (Error){true, "non correct format of argument, correct is x.y"};
    return (Error){false, ""};
}

bool check_substr(char *s){
    if(strlen(s) == 0)
        return false;

    for (int i = 0; i < strlen(s); ++i) {
        if(!isdigit(s[i]) && !(i == 0 && s[i] == '-')){
            return false;
        }
    }
    return true;
}
