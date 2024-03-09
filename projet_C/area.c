// Vector text-based editor
// created by Mailinh TA and Manon GAUTIER

// it contain functions to display the shape and make it possible for the user to interact

#include "area.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SHAPE_MAX 100 // Maximum number of shapes
#define BOOL int

// creates a zone of type area and returns a pointer to it
// the width and height of the zone to be created are passed as parameters
// return a pointer to the area created
Area* create_area(unsigned int width, unsigned int height){
    Area *zone = (Area*)malloc(sizeof(Area));

    BOOL **matrix = (BOOL**)malloc(sizeof(BOOL*)*height);
    for (int i=0;i<height;i++){
        matrix[i] = (BOOL*)malloc(sizeof(BOOL)*width);
    }

    zone->width=width;
    zone->height=height;

    zone->nb_shape = 0;
    zone->mat = matrix;

    return zone;
}

// add a shape to the drawing area, and increment nb_shape
// the addresses of the area and of the shape are passed as parameters
// return nothing
void add_shape_to_area(Area* area, Shape* shape){
    area->shapes[area->nb_shape]=shape;
    area->nb_shape+=1;
}

// initialise all the pixels to 0
// the address of the area is passed as parameter
// return nothing
void clear_area(Area* area){
    for (int i=0;i<area->height;i++) {
        for (int j=0;j<area->width;j++)
            area->mat[i][j]=0;
    }
}

// delete all the shapes drawn in this drawing area
// the address of the area is passed as parameter
// return nothing
void erase_area(Area* area) {
    for (int i=0;i<area->nb_shape;i++){
        delete_shape(area->shapes[i]);
    }
    area->nb_shape=0;
}

// deletes a drawing area with all the associated shapes
// the address of the area is passed as parameter
// return nothing
void delete_area(Area* area){
    for (int i=0;i<area->height;i++) {
        free(area->mat[i]);
    }
    free(area->mat);
    free(area);
}

// draw a shape in the drawing area
// the address of the area is passed as parameter
// return nothing
void draw_area(Area* area) {
    clear_area(area);

    int nb_pixels;
    Pixel **pixels;
    for (int shp_nb = 0; shp_nb<area->nb_shape; shp_nb++) {
        pixels = create_shape_to_pixel(area->shapes[shp_nb], &nb_pixels);
        for (int pix = 0; pix<nb_pixels; pix++) {
            if (area->height > pixels[pix]->py && pixels[pix]->py >= 0 && area->width > pixels[pix]->px && area->width >= 0) {
                area->mat[pixels[pix]->py][pixels[pix]->px] = 1;
            }
        }
        delete_pixel_shape(pixels, nb_pixels);
    }
}

// display the pixels of the matrix mat on the screen using the function printf()
// the address of the area is passed as parameter
// return nothing
void print_area(Area* area) {
    for (int i=0; i<area->height;i++){
        for (int j=0;j<area->width;j++){
            if (area->mat[i][j]==0){
                printf(". ");
            } else {
                printf("# ");
            }
        }
        printf(" \n");
    }
}

// allocate a memory space of type Pixel, to initialize it and to return the address of the allocated memory space
// the coordinates (px and py) of the pixel are passed as parameters
// return a pointer the pixel created
Pixel* create_pixel(int px, int py){
    Pixel* pixel=(Pixel*)malloc(sizeof(Pixel));
    pixel->px=px;
    pixel->py=py;
    return pixel;
}

// free the memory space allocated by the previous function
// the address of a pixel is passed as parameter
// return nothing
void delete_pixel(Pixel* pixel){
    free(pixel);
}

// create point
// the addresses of a shape and an integer are passed as parameters
// return an array of pointers to pixels
Pixel **pixel_point(Shape *shp, int *nb_pixels) {
    Point *pt = (Point*)shp->ptrShape;
    Pixel *p = create_pixel(pt->pos_x, pt->pos_y);
    Pixel **pixel_tab = (Pixel**) malloc(sizeof(Pixel*));
    pixel_tab[0] = p;
    *nb_pixels = 1;
    return pixel_tab;
}

// create line
// the addresses of a shape and an integer are passed as parameters
// return an array of pointers to pixels
Pixel **pixel_line(Shape *shp, int *nb_pixels) {
    Line *line = (Line*)shp->ptrShape;

    int xa = line->p1->pos_x;
    int xb = line->p2->pos_x;
    int ya = line->p1->pos_y;
    int yb = line->p2->pos_y;

    if (xa > xb) {
        int tmp = xa;
        xa = xb;
        xb = tmp;
        tmp = ya;
        ya = yb;
        yb = tmp;
    }

    int dx = xb - xa;
    int dy = yb - ya;

    int d_min, d_max;
    if (abs(dx) < abs(dy)){
        d_min=abs(dx);
        d_max=abs(dy);
    } else {
        d_min=abs(dy);
        d_max=abs(dx);
    }

    int nb_segs = d_min + 1;
    int base_size = (d_max + 1) / nb_segs;
    int remaining = (d_max + 1) % nb_segs;

    int *segments = malloc(nb_segs * sizeof(int));
    for (int i = 0; i < nb_segs; i++) {
        segments[i] = base_size;
    }
    for (int i = 0; i < remaining; i++) {
        segments[i]++;
    }

    Pixel **pixels = malloc((d_max + 1) * sizeof(Pixel *));
    *nb_pixels = 0;

    int x = xa;
    int y = ya;

    int direction=dy;
    if (direction < 0 ){
        direction=-1;
    } else {
        direction=1;
    }

    for (int i = 0; i < nb_segs; i++) {
        int is_horizontal = abs(dx) > abs(dy);

        for (int j = 0; j < segments[i]; j++) {
            pixels[*nb_pixels] = malloc(sizeof(Pixel));
            pixels[*nb_pixels]->px = x;
            pixels[*nb_pixels]->py = y;
            (*nb_pixels)++;

            if (is_horizontal) {
                x += direction;
            } else {
                y += direction;
            }
        }

        if (is_horizontal) {
            y -= direction;
        } else {
            x += direction;
        }
    }
    return pixels;
}

// create square
// the addresses of a shape and an integer are passed as parameters
// return an array of pointers to pixels
Pixel **pixel_square(Shape *shp, int* nb_pixels) {
    Square *sq = (Square*)shp->ptrShape;

    int nb_pix1, nb_pix2, nb_pix3, nb_pix4;

    Shape *ln1 = create_line_shape(sq->point->pos_x, sq->point->pos_y, sq->point->pos_x+sq->length, sq->point->pos_y);
    Shape *ln2 = create_line_shape(sq->point->pos_x, sq->point->pos_y, sq->point->pos_x, sq->point->pos_y+sq->length);
    Shape *ln3 = create_line_shape(sq->point->pos_x, sq->point->pos_y+sq->length, sq->point->pos_x+sq->length, sq->point->pos_y+sq->length);
    Shape *ln4 = create_line_shape(sq->point->pos_x+sq->length, sq->point->pos_y, sq->point->pos_x+sq->length, sq->point->pos_y+sq->length);

    Pixel **p1 = pixel_line(ln1, &nb_pix1);
    Pixel **p2 = pixel_line(ln2, &nb_pix2);
    Pixel **p3 = pixel_line(ln3, &nb_pix3);
    Pixel **p4 = pixel_line(ln4, &nb_pix4);

    *nb_pixels = nb_pix1 + nb_pix2 + nb_pix3 + nb_pix4;
    Pixel **pixel_tab = malloc(*nb_pixels * sizeof(Pixel*));

    delete_shape(ln1); delete_shape(ln2); delete_shape(ln3); delete_shape(ln4);

    for (int i = 0; i < nb_pix1; i++) {
        pixel_tab[i] = p1[i];
    }
    for (int i = 0; i < nb_pix2; i++) {
        pixel_tab[i + nb_pix1] = p2[i];
    }
    for (int i = 0; i < nb_pix3; i++) {
        pixel_tab[i + nb_pix1 + nb_pix2] = p3[i];
    }
    for (int i = 0; i < nb_pix4; i++) {
        pixel_tab[i + nb_pix1 + nb_pix2 + nb_pix3] = p4[i];
    }
    return pixel_tab;
}

// create rectangle
// the addresses of a shape and an integer are passed as parameters
// return an array of pointers to pixels
Pixel **pixel_rectangle(Shape *shp, int* nb_pixels) {
    Rectangle *rect = (Rectangle*)shp->ptrShape;

    int nb_pix1, nb_pix2, nb_pix3, nb_pix4;

    Shape *ln1 = create_line_shape(rect->point->pos_x, rect->point->pos_y, rect->point->pos_x+rect->width, rect->point->pos_y);
    Shape *ln2 = create_line_shape(rect->point->pos_x, rect->point->pos_y, rect->point->pos_x, rect->point->pos_y+rect->height);
    Shape *ln3 = create_line_shape(rect->point->pos_x, rect->point->pos_y+rect->height, rect->point->pos_x+rect->width, rect->point->pos_y+rect->height);
    Shape *ln4 = create_line_shape(rect->point->pos_x+rect->width, rect->point->pos_y, rect->point->pos_x+rect->width, rect->point->pos_y+rect->height);

    Pixel **p1 = pixel_line(ln1, &nb_pix1);
    Pixel **p2 = pixel_line(ln2, &nb_pix2);
    Pixel **p3 = pixel_line(ln3, &nb_pix3);
    Pixel **p4 = pixel_line(ln4, &nb_pix4);

    delete_shape(ln1);
    delete_shape(ln2);
    delete_shape(ln3);
    delete_shape(ln4);

    *nb_pixels = nb_pix1 + nb_pix2 + nb_pix3 + nb_pix4;
    Pixel **pixel_tab = malloc(*nb_pixels * sizeof(Pixel*));

    for (int i = 0; i < nb_pix1; i++) {
        pixel_tab[i] = p1[i];
    }
    for (int i = 0; i < nb_pix2; i++) {
        pixel_tab[i + nb_pix1] = p2[i];
    }
    for (int i = 0; i < nb_pix3; i++) {
        pixel_tab[i + nb_pix1 + nb_pix2] = p3[i];
    }
    for (int i = 0; i < nb_pix4; i++) {
        pixel_tab[i + nb_pix1 + nb_pix2 + nb_pix3] = p4[i];
    }

    return pixel_tab;
}

// create polygon
// the addresses of a shape and an integer are passed as parameters
// return an array of pointers to pixels
Pixel **pixel_polygon(Shape *shp, int* nb_pixels) {
    Polygon *pol = (Polygon*)shp->ptrShape;

    Pixel ***pixel_tab = malloc(sizeof(Pixel**)*(pol->n));
    int pixel_count[pol->n];
    *nb_pixels = 0;
    int i=0;
    for (; i < pol->n-1; i++) {
        Shape *ln = create_line_shape(pol->points[i]->pos_x, pol->points[i]->pos_y,
                                      pol->points[i+1]->pos_x, pol->points[i+1]->pos_y);
        pixel_tab[i] = pixel_line(ln, &pixel_count[i]);
        delete_shape(ln);
        *nb_pixels += pixel_count[i];
    }

    Pixel **pixels = malloc(sizeof(Pixel*)*(*nb_pixels));
    int k = 0, j;
    for (i=0; i < pol->n-1; i++) {
        for (j=0; j < pixel_count[i]; j++) {
            pixels[k++] = pixel_tab[i][j];
        }
    }

    return pixels;
}


// create circle
// the addresses of a shape and an integer are passed as parameters
// return an array of pointers to pixels
Pixel **pixel_circle(Shape *shape, int *nb_pixels) {
    Circle *circle = (Circle*)shape->ptrShape;

    int x = 0;
    int y = circle->radius;
    int d = circle->radius-1;
    *nb_pixels = 0;

    while (y >= x) {
        *nb_pixels += 8;

        if (d >= 2 * x) {
            d -= 2 * x + 1;
            x++;
        } else if (d < 2 * (circle->radius - y)) {
            d += 2 * y - 1;
            y--;
        } else {
            d += 2 * (y - x - 1);
            y--;
            x++;
        }
    }


    Pixel **pixels = malloc(sizeof(Pixel)*(*nb_pixels));
    Pixel *px = NULL;

    x = 0;
    y = circle->radius;
    d = circle->radius-1;
    *nb_pixels = 0;

    while (y >= x) {
        px = create_pixel(circle->center->pos_x + x, circle->center->pos_y + y);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->pos_x + y, circle->center->pos_y + x);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->pos_x - x, circle->center->pos_y + y);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->pos_x - y, circle->center->pos_y + x);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->pos_x + x, circle->center->pos_y - y);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->pos_x + y, circle->center->pos_y - x);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->pos_x - x, circle->center->pos_y - y);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->pos_x - y, circle->center->pos_y - x);
        pixels[(*nb_pixels)++] = px;

        if (d >= 2 * x) {
            d -= 2 * x + 1;
            x++;
        } else if (d < 2 * (circle->radius - y)) {
            d += 2 * y - 1;
            y--;
        } else {
            d += 2 * (y - x - 1);
            y--;
            x++;
        }
    }

    return pixels;
}

// transform shape to array of pixels
// the addresses of a shape and an integer are passed as parameters
// return an array of pointers to pixels
Pixel** create_shape_to_pixel(Shape* shape, int *nb_pixels) {
    switch (shape->shape_type) {
        case POINT:
            return pixel_point(shape, nb_pixels);

        case LINE:
            return pixel_line(shape, nb_pixels);

        case SQUARE:
            return pixel_square(shape, nb_pixels);

        case RECTANGLE:
            return pixel_rectangle(shape, nb_pixels);

        case CIRCLE:
            return pixel_circle(shape, nb_pixels);

        case POLYGON:
            return pixel_polygon(shape, nb_pixels);

        default:
            return NULL;
    }
}

// delete pixels
// the address of an array of pixels and an integer are passed as parameters
// return nothing
void delete_pixel_shape(Pixel** pixel, int nb_pixels) {
    for (int i = 0; i<nb_pixels; i++) {
        delete_pixel(pixel[i]);
    }
    free(pixel);
}

extern int global_id;

// create command
// nothing is passed as parameter
// return a pointer to a command
Command* create_command(){
    Command *c = (Command*)malloc(sizeof(Command));
    return c;
}

// insert in the array str_params the characters and increment str_size
// pointers to a command and a string are passed as parameters
// return nothing
void add_str_param(Command* cmd, char* s){
    int i=0;
    while(*s != '\n' && ((*s > '@' && *s < '[')||((*s > '`' && *s < '{')))){
        while (*s != ' ' && *s != '\0') {
            *cmd->str_params[i] = *s;
            cmd->str_params[i] += sizeof(char);
            s += sizeof(char);
        }
        *cmd->str_params[i] = '\0';
        i++;
        s += sizeof(char);
    }
    cmd->str_size = i;
}

// insert in the array int_params the integers and increment str_size
// pointers to a command and a string are passed as parameters
// return nothing
void add_int_param(Command* cmd, char* s){
    int i = 0;
    int cpt;
    while(*s != '\0' && (*s > '/' && *s < ':')) {
        cmd->int_params[i] = 0;
        cpt = 1;
        while (*s != ' ' && *s != '\n') {
            cmd->int_params[i] += (*s-'0')*cpt;
            s += sizeof(char);
            cpt*=10;
        }
        i++;
        s += sizeof(char);
    }
    cmd->int_size = i;
}

// free the memory occupied by the command / delete it
// pointer to a command is passed as parameter
// return nothing
void free_cmd(Command* cmd){
    free(cmd);
}

// execute the command entered by the user
// pointers to a command and an area are passed as parameters
// return an int (0 to exit else 1)
int read_exec_command(Command* cmd, Area *draw_zone){

    if (strcmp(cmd->name, "clear")==0) {
        clear_area(draw_zone);
    }

    else if (strcmp(cmd->name, "exit") == 0) {
        printf("Bye !");
        free_cmd(cmd);
        return 0;

    } else if (strcmp(cmd->name, "point") == 0) {
        if(cmd->int_size==2) {
            Shape *shape5 = create_point_shape(cmd->int_params[0], cmd->int_params[1]);
            add_shape_to_area(draw_zone, shape5);
        }
        else{
            error_message("point", 2);
        }

    } else if (strcmp(cmd->name, "line") == 0) {
        if(cmd->int_size==4) {
            Shape *shape1 = create_line_shape(cmd->int_params[0], cmd->int_params[1], cmd->int_params[2],
                                              cmd->int_params[3]);
            add_shape_to_area(draw_zone, shape1);
        }
        else{
            error_message("line", 4);
        }

    } else if (strcmp(cmd->name, "circle") == 0) {
        if(cmd->int_size==3) {
            Shape *shape1 = create_circle_shape(cmd->int_params[0], cmd->int_params[1], cmd->int_params[2]);
            add_shape_to_area(draw_zone, shape1);
        }
        else{
            error_message("circle", 3);
        }

    } else if (strcmp(cmd->name, "square") == 0) {
        if(cmd->int_size==3) {
            Shape *shape1 = create_square_shape(cmd->int_params[0], cmd->int_params[1],
                                                cmd->int_params[2]);
            add_shape_to_area(draw_zone, shape1);
        }
        else{
            error_message("square", 3);
        }

    } else if (strcmp(cmd->name, "rectangle") == 0) {
        if(cmd->int_size==4) {
            Shape *shape1 = create_rectangle_shape(cmd->int_params[0], cmd->int_params[1],
                                                   cmd->int_params[2],
                                                   cmd->int_params[3]);
            add_shape_to_area(draw_zone, shape1);
        }
        else{
            error_message("rectangle", 4);
        }

    } else if (strcmp(cmd->name, "polygon") == 0) {
        if(cmd->int_size%2 == 0) {
            int i;
            int l[] = {};
            for (i = 0; i < cmd->int_size; i++) {
                l[i] = cmd->int_params[i];
            }
            Shape *shape1 = create_polygon_shape(cmd->int_params, cmd->int_size/2);
            add_shape_to_area(draw_zone, shape1);
        }
        else{
            error_message("polygon", -2);
        }

    } else if (strcmp(cmd->name, "plot") == 0) {
        draw_area(draw_zone);
        print_area(draw_zone);

    } else if (strcmp(cmd->name, "list") == 0) {
        for (int i = 0; i < draw_zone->nb_shape; i++) {
            printf("shape %d :\n", draw_zone->shapes[i]->id);
            print_shape(draw_zone->shapes[i]);
        }

    } else if (strcmp(cmd->name, "delete") == 0) {
        for (int i = 0; i < draw_zone->nb_shape; i++) {
            if(cmd->int_size == 1) {
                if (draw_zone->shapes[i]->id == cmd->int_params[0]) {
                    delete_shape(draw_zone->shapes[i]);
                    draw_zone->nb_shape-=1;
                    printf("The shape whose id was %d has been deleted.\n", cmd->int_params[0]);
                }
            }
            else{
                error_message("deletion", 1);
            }
        }

    } else if (strcmp(cmd->name, "erase\0") == 0) {
        erase_area(draw_zone);

    } else if (strcmp(cmd->name, "help\0") == 0) {
        printf("-   To insert a shape please type: 'name_shape coord_x1 coord_y1 coord_x2 coord_y2 etc.' ex: 'point 3 5'\n"
               "You can create a point, a line, a square, a rectangle, a circle or a polygon\n"
               "-   To plot the shapes on the board please type: 'plot'\n"
               "-   To display the list of shapes please type: 'list'\n"
               "-   To clear the board please type: 'clear'\n"
               "-   To delete a shape please type: 'delete id_of_shape' ex: 'delete 0'\n"
               "-   To erase the board please type: 'erase'\n"
               "-   To exit please type: 'exit'\n");


    } else {
        error_message("not valid", 0);
    }

    free_cmd(cmd);
    return 1;
}

// read and parse the command entered by the user
// pointer to a command is passed as parameter
// return nothing
void read_from_stdin(Command* cmd){
    char *s = (char*)malloc(sizeof(char)*60);
    printf("Please type a command line:");
    fgets (s, 60, stdin);
    int i =0;
    while (*s != ' ' && *s != '\n') {
        cmd->name[i] = *s;
        i++;
        s += sizeof(char);
    }
    cmd->name[i] = '\0';
    s += sizeof(char);
    // not useful for the moment...
    // add_str_param(cmd, s);
    add_int_param(cmd,s);
}

// display an error message according to the problem encountered
// a string and an int are passed as parameters
// return nothing
void error_message(char* c, int n){
    if(n==0){
        printf("Your command is %s.", c);
    }
    else if(n==-2){
        printf("A %s does require a list 'l' that contain an even number of integers to be created.", c);
    }
    else{
        printf("A %s does require %d integers to be created.", c, n);
    }
    printf(" Try again ! If help is needed, write the command 'help'.\n");
}
