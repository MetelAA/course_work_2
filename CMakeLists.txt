cmake_minimum_required(VERSION 3.16)
project(cw2 C)

set(CMAKE_C_STANDARD 99)

add_executable(cw2 main.c base_structs.h parser/validator/base_validator.c parser/validator/base_validator.h parser/parser.c parser/parser.h consoleLogs/help.c consoleLogs/help.h consoleLogs/info.c consoleLogs/info.h parser/validator/canvas_entity_validator.c parser/validator/canvas_entity_validator.h image_funcs/file_actions.c image_funcs/file_actions.h image_funcs/image_mirror_func.c image_funcs/image_mirror_func.h image_funcs/image_copy_func.c image_funcs/image_copy_func.h image_funcs/image_color_replace_func.c image_funcs/image_color_replace_func.h image_funcs/image_split_func.c image_funcs/image_split_func.h image_funcs/image_border_with_extension.c image_funcs/image_border_with_extension.h image_funcs/encircle_white_area.c image_funcs/encircle_white_area.h)