#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void initialize_room(char** room, int rows, int cols) {
    int i, j;

    for (i=0; i<rows; i++)
        for (j=0; j<cols; j++)
            room[i][j]=' ';
}

void build_walls(char** room, int rows, int cols) {
    int i;

    for (i=0; i<rows; i++) {
        room[i][0]='#';
        room[i][cols-1]='#';
    }
        
    for (i=0; i<cols; i++) {
        room[0][i]='#';
        room[rows-1][i]='#';
    }

}

void set_obstacles(char** room, int rows, int cols) {
    srand(time(NULL));
    int obstacles_number = rand()%(rows+cols);
    int i= obstacles_number;

    int row;
    int col;

    while (i>0) {
        row= rand()%rows;
        col= rand()%cols;
        room[row][col]='#';
        i--;
    }
}

void set_exits(char** room, int rows, int cols) {
    srand(time(NULL));
    int exits_number = rand()%3+1;
    int wall_id;
    int i;

    for (i=0; i<exits_number; i++) {
        wall_id= rand()%3+1;
        switch (wall_id) {
            case 1: //left wall
                room[i][0]='+';
                break;
            case 2: //top wall
                room[0][i]='+';
                break;
            case 3: //right wall
                room[i][cols-1]='+';
                break;
            case 4: //bottom wall
                room[rows-1][i]='+';
            break;
        }
    }
}

char** get_room(int rows, int cols) {
    int i,j;
    char** room= (char**)malloc(rows*sizeof(char*));

    if (room!=NULL) {
        for (i=0; i<rows; i++) {
            room[i] = (char*)malloc(cols*sizeof(char));
            if (room[i]==NULL) return NULL;
        }
        initialize_room(room,rows,cols);
        build_walls(room,rows,cols);
        set_obstacles(room,rows,cols);
        set_exits(room,rows,cols);
        return room;
    } else return NULL;
            
}

