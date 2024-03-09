// Vector text-based editor
// created by Mailinh TA and Manon GAUTIER

// structures and functions linked to the area, pixels or commands are defined here

#ifndef UNTITLED2_AREA_H
#define UNTITLED2_AREA_H

#include "functions.h"

#define SHAPE_MAX 100 // Maximum number of shapes
#define BOOL int

struct area {
    unsigned int width; // Number of pixels in width or number of columns (y-axis)
    unsigned int height; // Number of pixels in height or number of lines (x axis)
    BOOL** mat; // pixel size matrix (width * height)
    Shape* shapes[SHAPE_MAX]; // array of shapes
    int nb_shape; // number of shapes in the shapes array (logical size)
};
typedef struct area Area;

struct pixel {
    int px;
    int py;
};
typedef struct pixel Pixel;

Area* create_area(unsigned int width, unsigned int height);
void add_shape_to_area(Area* area, Shape* shape);
void clear_area(Area* area);
void erase_area(Area* area);
void delete_area(Area* area);
void draw_area(Area* area);
void print_area(Area* area);
Pixel* create_pixel(int px, int py);
void delete_pixel(Pixel* pixel);
Pixel **pixel_point(Shape *shp, int *nb_pixels);
Pixel **pixel_square(Shape *shp, int* nb_pixels);
Pixel **pixel_rectangle(Shape *shp, int* nb_pixels);
Pixel **pixel_polygon(Shape *shp, int* nb_pixels);
Pixel **pixel_circle(Shape *shape, int *nb_pixels);
Pixel** create_shape_to_pixel(Shape* shape, int *nb_pixels);
void delete_pixel_shape(Pixel** pixel, int nb_pixels);


struct command {
    char name[50];
    int int_size;
    int int_params[10];
    int str_size;
    char* str_params[10];
};
typedef struct command Command;

Command* create_command();
void add_str_param(Command* cmd, char* s);
void add_int_param(Command* cmd, char* s);
void free_cmd(Command* cmd);
int read_exec_command(Command* cmd, Area *draw_zone1);
void read_from_stdin(Command* cmd);

void error_message(char* c, int n);

#endif //UNTITLED2_AREA_H
