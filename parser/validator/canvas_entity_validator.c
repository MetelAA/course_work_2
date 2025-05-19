#include "canvas_entity_validator.h"

bool check_RGB_component(int a);

bool get_canvas_point_from_string(char* s, Point * point){
    if(!dots_count_and_data_check(s, 1))
        return false;
    char *p = strchr(s, '.');
    *p = '\0';
    point->x = atoi(s);
    s = s + (p-s) + 1;
    point->y = atoi(s);
    return true;
}

bool check_axis(char *s){
    if(strlen(s) != 1)
        return false;
    if(s[0] == 'x' || s[0] == 'y')
        return true;
    return false;
}

bool get_color_from_string(char *s, Rgb* color){
    if(!dots_count_and_data_check(s, 2))
        return false;
    char *p = strchr(s, '.');
    *p = '\0';
    color->r = atoi(s);
    s = s + (p-s) + 1;
    p = strchr(s, '.');
    *p = '\0';
    color->g = atoi(s);
    s = s + (p-s) + 1;
    color->b = atoi(s);

    if(check_RGB_component(color->r) &&
    check_RGB_component(color->g) &&
    check_RGB_component(color->b)
    ){
        return true;
    }
    return false;
}

bool check_RGB_component(int a){
    if(a >= 0 && a <= 255){
        return true;
    }
    return false;
}

bool get_split_counts(char *s, int *rez){
    bool is_str = true;
    for (int i = 0; i < strlen(s); ++i) {
        if(!isdigit(s[i])){
            is_str = false;
            return false;
        }
    }
    int a = atoi(s);
    if(a <= 1)
        return false;
    (*rez) = a;
    return true;
}

bool get_thickness(char *s, int *rez){
    bool is_str = true;
    for (int i = 0; i < strlen(s); ++i) {
        if(!isdigit(s[i])){
            is_str = false;
            return false;
        }
    }
    int a = atoi(s);
    if(a <= 0)
        return false;
    (*rez) = a;
    return true;
}