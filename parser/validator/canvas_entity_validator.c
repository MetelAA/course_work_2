#include "canvas_entity_validator.h"

bool check_RGB_component(int a);

Error get_canvas_point_from_string(char* s, Point * point){
    Error parse_error = dots_count_and_data_check(s, 1);
    if(parse_error.hasError)
        return parse_error;
    char *p = strchr(s, '.');
    *p = '\0';
    point->x = atoi(s);
    s = s + (p-s) + 1;
    point->y = atoi(s);
    return (Error){false, ""};
}

Error check_axis(char *s){
    if(strlen(s) != 1)
        return (Error){true, "axis argument must be 1 length"};
    if(s[0] == 'x' || s[0] == 'y')
        return (Error){false, ""};
    return (Error){true, "axis must be x or y"};
}

Error get_color_from_string(char *s, Rgb* color){
    Error parse_error =dots_count_and_data_check(s, 2);
    if(parse_error.hasError)
        return parse_error;
    char *p = strchr(s, '.');
    *p = '\0';
    int r = atoi(s);
    s = s + (p-s) + 1;
    p = strchr(s, '.');
    *p = '\0';
    int g = atoi(s);
    s = s + (p-s) + 1;
    int b = atoi(s);

    if(check_RGB_component(r) &&
    check_RGB_component(g) &&
    check_RGB_component(b)
    ){
        color->r = r;
        color->g = g;
        color->b = b;
        return (Error){false, ""};
    }
    return (Error){true, "r, g, b params must be between 0 and 255"};
}

bool check_RGB_component(int a){
    if(a >= 0 && a <= 255){
        return true;
    }
    return false;
}

Error get_split_counts(char *s, int *rez){
    for (int i = 0; i < strlen(s); ++i) {
        if(!isdigit(s[i])){
            return (Error){true, "not a number"};
        }
    }
    int a = atoi(s);
    if(a <= 1)
        return (Error){true, "must be >= 1"};
    (*rez) = a;
    return (Error){false, ""};
}

Error get_thickness(char *s, int *rez){
    for (int i = 0; i < strlen(s); ++i) {
        if(!isdigit(s[i])){
            return (Error){true, "not a number"};
        }
    }
    int a = atoi(s);
    if(a <= 0)
        return (Error){true, "must be > 0"};
    (*rez) = a;
    return (Error){false, ""};
}