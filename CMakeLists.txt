cmake_minimum_required(VERSION 3.16)
project(cw2 C)

set(CMAKE_C_STANDARD 99)

add_executable(cw2 main.c base_structs.h parser/validator/base_validator.c parser/validator/base_validator.h parser/parser.c parser/parser.h consoleLogs/help.c consoleLogs/help.h consoleLogs/info.c consoleLogs/info.h parser/validator/canvas_entity_validator.c parser/validator/canvas_entity_validator.h)