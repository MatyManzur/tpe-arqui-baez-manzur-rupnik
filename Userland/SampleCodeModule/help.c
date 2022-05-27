
#include <help.h>
#include <userlib.h>

void help(){
    printStringColor("The available commands are the following: ", MAGENTA,BLACK);
    setColor(L_GRAY,BLUE);
    sys_move_cursor(1,0);
    printString("help y nada mas asjasj ");
    printString("lol ayuda");
    sys_exit();
}
