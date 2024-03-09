// Vector text-based editor
// created by Mailinh TA and Manon GAUTIER

// it contain functions to create the geometric vector shapes

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int global_id = 0;
int get_next_id(){
    return global_id++;
}

// allows to dynamically allocate a structured Point whose coordinates are given in parameter
// two integers (the coordinates) are passed as parameters
// return a pointer to the point created
Point *create_point(int px, int py){
    Point* p = (Point*)malloc(sizeof(Point));
    p->pos_x = px;
    p->pos_y = py;
    return p;
}

// allows to free the memory allocated to the point given in parameter
// the point to be deleted is passed as parameter
// return nothing
void delete_point(Point * point){
    free(point);
}

// allows to display on the screen the information of a Point in the following form: POINT [p(pos_x, pos_y)]
// the point to be printed is passed as parameter
// return nothing
void print_point(Point * p){
    printf("POINT %d %d\n", p->pos_x, p->pos_y);
}

// allows to dynamically allocate a segment of structured type Line from two points given in parameters
// two points to create it are passed as parameters
// return a pointer to the line created
Line *create_line(Point * p1, Point * p2){
    Line *line= (Line*)malloc(sizeof(Line));
    line->p1 = p1;
    line->p2 = p2;
    return line;
}

// allows to free the memory allocated to the segment given in parameter
// the line to be deleted is passed as parameter
// return nothing
void delete_line(Line * line){
    delete_point(line->p1);
    delete_point(line->p2);
    free(line);
}

// allows to display the information of a segment according to the format described in the following
// the line to be printed is passed as parameter
// return nothing
void print_line(Line * line){
    printf("LINE %d %d %d %d\n",line->p1->pos_x,line->p1->pos_y,line->p2->pos_x,line->p2->pos_y);
}

// allows to dynamically allocate a square of structured Square from a point and a length given in parameters
// a point and an integer to create it are passed as parameters
// return a pointer to the square created
Square *create_square(Point * point, int length){
    Square *square = (Square*)malloc (sizeof(Square));
    square->point = point;
    square->length = length;
    return square;
}

// allows to free the memory allocated to a square given in parameter
// the square to be deleted is passed as parameter
// return nothing
void delete_square(Square * square){
    delete_point(square->point);
    free(square);
}

// allows to display the information of a segment according to the format described in the following
// the square to be printed is passed as parameter
// return nothing
void print_square(Square * square){
    printf("SQUARE %d %d %d\n",square->point->pos_x,square->point->pos_y,square->length);
}

// allows to dynamically allocate a rectangle of structured Rectangle from a point,a length and a width given in parameters
// a point and two integer to create it are passed as parameters
// return a pointer to the rectangle created
Rectangle *create_rectangle(Point * point, int width, int height){
    Rectangle *rectangle = (Rectangle*)malloc (sizeof(Rectangle));
    rectangle->point = point;
    rectangle->width = width;
    rectangle->height = height;
    return rectangle;
}

// allows to free the memory allocated to a rectangle given in parameter
// the rectangle to be deleted is passed as parameter
// return nothing
void delete_rectangle(Rectangle * rectangle){
    delete_point(rectangle->point);
    free(rectangle);
}

// allows to display the information of a segment according to the format described in the following
// the rectangle to be printed is passed as parameter
// return nothing
void print_rectangle(Rectangle * rectangle){
    printf("RECTANGLE %d %d %d %d\n",rectangle->point->pos_x,rectangle->point->pos_y,rectangle->width,rectangle->height);
}

// allows to dynamically allocate a circle of structured Circle from a center and a radius given in parameters
// a point and an integer to create it are passed as parameters
// return a pointer to the circle created
Circle *create_circle(Point * center, int radius){
    Circle *circle = (Circle*)malloc (sizeof(Circle));
    circle->center = center;
    circle->radius = radius;
    return circle;
}

// allows to free the memory allocated to a circle given in parameter
// the circle to be deleted is passed as parameter
// return nothing
void delete_circle(Circle * circle){
    delete_point(circle->center);
    free(circle);
}

// allows to display the information of a segment according to the format described in the following
// the circle to be printed is passed as parameter
// return nothing
void print_circle(Circle * circle){
    printf("CIRCLE %d %d %d\n",circle->center->pos_x,circle->center->pos_y,circle->radius);
}

// allows to dynamically allocate a polygon of structured Polygon from a size n given in parameters
// an integer is passed as parameters to create it
// return a pointer to the polygon created
Polygon *create_polygon(int n){
    Polygon *polygon = (Polygon*)malloc(sizeof(Polygon));
    polygon->n = n;
    return polygon;
}

// allows to free the memory allocated to a circle given in parameter
// the polygon to be deleted is passed as parameter
// return nothing
void delete_polygon(Polygon * polygon){
    int i;
    for(i=0; i<polygon->n; i++){
        delete_point(polygon->points[i]);
    }
    free(polygon);
}

// allows to display the information of a segment according to the format described in the following
// the polygon to be printed is passed as parameter
// return nothing
void print_polygon(Polygon * polygon){
    int i;
    printf("%s %d","POLYGON", polygon->n);
    for(i=0; i<polygon->n; i++){
        printf(" | %d %d", polygon->points[i]->pos_x, polygon->points[i]->pos_y);
    }
    printf("\n");
}

// allows to dynamically allocate an empty shape
// the type of the shape wanted is passed as parameters to create it
// return a pointer to the shape created
Shape *create_empty_shape(SHAPE_TYPE shape_type) {
    Shape *shape = (Shape*)malloc(sizeof(Shape));
    shape->id = get_next_id();
    shape->shape_type = shape_type;
    shape->ptrShape = NULL;
    return shape;
}

// allows to create a point shape
// two integers are passed as parameters to create it
// return a pointer to the point shape created
Shape *create_point_shape(int x, int y) {
    Shape *shp = create_empty_shape(POINT);
    Point *p = create_point(x,y);
    shp->ptrShape = p;
    return shp;
}

// allows to create a line shape
// four integers (to create two points) are passed as parameters
// return a pointer to the line shape created
Shape *create_line_shape(int x1, int y1, int x2, int y2) {
    Shape *shp = create_empty_shape(LINE);
    Point *p1 = create_point(x1,y1);
    Point *p2 = create_point(x2,y2);
    Line *l = create_line(p1, p2);
    shp->ptrShape = l;
    return shp;
}

// allows to create a square shape
// three integers (to create a point + the length) are passed as parameters
// return a pointer to the square shape created
Shape *create_square_shape(int x, int y, int length) {
    Shape *shp = create_empty_shape(SQUARE);
    Point *p = create_point(x,y);
    Square *sq = create_square(p, length);
    shp->ptrShape = sq;
    return shp;
}

// allows to create a rectangle shape
// four integers (to create a point + the length and the width) are passed as parameters
// return a pointer to the rectangle shape created
Shape *create_rectangle_shape(int x, int y, int width, int height) {
    Shape *shp = create_empty_shape(RECTANGLE);
    Point *p = create_point(x,y);
    Rectangle *r = create_rectangle(p, width, height);
    shp->ptrShape = r;
    return shp;
}

// allows to create a circle shape
// three integers (to create a point + the radius) are passed as parameters
// return a pointer to the circle shape created
Shape *create_circle_shape(int x, int y, int radius) {
    Shape *shp = create_empty_shape(CIRCLE);
    Point *p = create_point(x,y);
    Circle *c = create_circle(p, radius);
    shp->ptrShape = c;
    return shp;
}

// allows to create a polygon shape
// an array of integers (to create points), and the number of point to be created are passed as parameters
// return a pointer to the polygon shape created
Shape *create_polygon_shape(int lst[], int n) {
    int i;
    Shape *shp = create_empty_shape(POLYGON);
    /*if(n%2!=0){
        printf("Can't create a polygon with an odd number of points."); // Why ? Can't we create a triangle ?
        return shp;
    }*/
    Polygon *pl = create_polygon(n);
    pl->points = malloc(sizeof (Point)*n);
    for(i=0; i<n; i++){
        pl->points[i] = create_point(lst[i*2], lst[i*2+1]);
    }
    shp->ptrShape = pl;
    return shp;
}

// delete a shape according to its type
// the address of a shape is passed as parameter
// return nothing
void delete_shape(Shape *shp) {
    if(shp->shape_type == POINT){
        delete_point(shp->ptrShape);
    }
    else if(shp->shape_type == LINE){
        delete_line(shp->ptrShape);
    }
    else if(shp->shape_type == SQUARE){
        delete_square(shp->ptrShape);
    }
    else if(shp->shape_type == RECTANGLE){
        delete_rectangle(shp->ptrShape);
    }
    else if(shp->shape_type == CIRCLE){
        delete_circle(shp->ptrShape);
    }
    else if(shp->shape_type == POLYGON){
        delete_polygon(shp->ptrShape);
    }
    free(shp);
}

// display a shape according to its type
// the address of a shape is passed as parameter
// return nothing
void print_shape(Shape *shp) {
    switch (shp->shape_type)
    {
        case POINT:
            print_point(shp->ptrShape);
            break;
        case LINE:
            print_line(shp->ptrShape);
            break;
        case SQUARE:
            print_square(shp->ptrShape);
            break;
        case RECTANGLE:
            print_rectangle(shp->ptrShape);
            break;
        case CIRCLE:
            print_circle(shp->ptrShape);
            break;
        case POLYGON:
            print_polygon(shp->ptrShape);
            break;
    }
}

