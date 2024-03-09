// Vector text-based editor
// created by Mailinh TA and Manon GAUTIER

// structures and functions linked to geometric forms and the shapes are defined here

#ifndef UNTITLED2_FUNCTIONS_H
#define UNTITLED2_FUNCTIONS_H

typedef struct {
    int pos_x;
    int pos_y;
}Point;

typedef struct line {
    Point *p1;
    Point *p2;
}Line;

typedef struct square {
    Point *point;
    int length;
}Square;

typedef struct rectangle {
    Point *point;
    int width;
    int height;
}Rectangle;

typedef struct circle {
    Point *center;
    int radius;
}Circle;

typedef struct polygon {
    int n;
    Point ** points; // dynamic 1D array Point*
}Polygon;

typedef enum { POINT, LINE, SQUARE, RECTANGLE, CIRCLE, POLYGON} SHAPE_TYPE;

typedef struct shape {
    int id; // unique identifier of the shape
    SHAPE_TYPE shape_type; // type of the shape pointed
    void *ptrShape; // pointer to any shape
}Shape;

Point *create_point(int px, int py);
void delete_point(Point * point);
void print_point(Point * p);

Line *create_line(Point * p1, Point * p2);
void delete_line(Line * line);
void print_line(Line * line);

Square *create_square(Point * point, int length);
void delete_square(Square * square);
void print_square(Square * square);

Rectangle *create_rectangle(Point * point, int width, int height);
void delete_rectangle(Rectangle * rectangle);
void print_rectangle(Rectangle * rectangle);

Circle *create_circle(Point * center, int radius);
void delete_circle(Circle * circle);
void print_circle(Circle * circle);

Polygon *create_polygon(int n);
void delete_polygon(Polygon * polygon);
void print_polygon(Polygon * polygon);

Shape *create_empty_shape(SHAPE_TYPE shape_type);
Shape *create_point_shape(int px, int py);
Shape *create_line_shape(int px1, int py1, int px2, int py2);
Shape *create_square_shape(int px, int py, int length);
Shape *create_rectangle_shape(int px, int py, int width, int height);
Shape *create_circle_shape(int px, int py, int radius);
Shape *create_polygon_shape(int lst[], int n);
void delete_shape(Shape * shape);
void print_shape(Shape * shape);

int get_next_id();

#endif
