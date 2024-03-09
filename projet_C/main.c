// Vector text-based editor
// created by Mailinh TA and Manon GAUTIER

// main program to run the functions created

#include "area.h"

int main(){

    Area *draw_zone1 = create_area(12, 14);
    int run = 1;
    // Read, analyse the command, and then execute it
    while(run){
        Command *cmd = create_command();
        read_from_stdin(cmd);
        if (read_exec_command(cmd, draw_zone1) == 0){
            run = 0;
        }
     }
    delete_area(draw_zone1);

    return 0;
}