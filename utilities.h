char get_key_pressed();
void clear_screen();
void print_fast_guide();
int move_player(char** room);
int move_player_up(char** room);
int move_player_down(char** room);
int move_player_left(char** room);
int move_player_right(char** room);
int is_player_near_enemy(char** room);
int get_player_row(char** room);
int get_player_col(char** room);
void reset_player(player* pl);
void print_collect_message(enemy* defeated);
void remove_enemy_from_map(char** room, int row, int col);
int get_near_monster_row(char** room);
int get_near_monster_col(char** room);
int is_player_near_exit(char** room);
int is_player_near_chest(char** room);
int get_chest_option(chest* cptr);
int open_chest(chest* cptr);
void inspect_chest(chest* cptr);
void say(char* message);
void remove_chest_from_map(char** room, int row, int col);
int get_near_chest_row(char** room);
int get_near_chest_col(char** room);

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
        system("clear");
    #endif
}

char get_key_pressed() {
    char key_pressed;
    fflush(stdin);
    printf(ANSI_COLOR_GREEN);
    scanf("%c",&key_pressed);
    printf(ANSI_COLOR_RESET);

    return key_pressed;
}

void print_fast_guide() {
    printf("\n=========\n");
    puts("[w]   Go straight on");
    puts("[a]   Move left");
    puts("[d]   Move right");   
    puts("[s]   Come back");
    puts("[u]   Exit");
    printf("=========\n");
    printf(ANSI_FONT_ITALIC "Press a key to play\n" ANSI_FONT_RESET);
}

int move_player_up(char** room) {
    int i,j;
    int row=-1, col=-1;

    for(i = 0; i < TUTORIAL_ROWS; i++)
        for (j=0; j<TUTORIAL_COLS; j++)
            if (room[i][j]=='X') {
                row=i;
                col=j;
            }

    if (row>0 && col>0)
        if (room[row-1][col]==' ') {
            room[row][col]=' ';
            room[row-1][col]='X';
            return 1;
        }
    
    return 0;

}

int move_player_down(char** room) {
    int i,j;
    int row=-1, col=-1;

    for(i = 0; i < TUTORIAL_ROWS; i++)
        for (j=0; j<TUTORIAL_COLS; j++)
            if (room[i][j]=='X') {
                row=i;
                col=j;
            }

    if (row>0 && col>0)
        if (room[row+1][col]==' ') {
            room[row][col]=' ';
            room[row+1][col]='X';
            return 1;
        }
    
    return 0;
}

int move_player_left(char** room) {
    int i,j;
    int row=-1, col=-1;

    for(i = 0; i < TUTORIAL_ROWS; i++)
        for (j=0; j<TUTORIAL_COLS; j++)
            if (room[i][j]=='X') {
                row=i;
                col=j;
            }

    if (row>0 && col>0)
        if (room[row][col-1]==' ') {
            room[row][col]=' ';
            room[row][col-1]='X';
            return 1;
        }
    
    return 0;

}

int move_player_right(char** room) {
    int i,j;
    int row=-1, col=-1;

    for(i = 0; i < TUTORIAL_ROWS; i++)
        for (j=0; j<TUTORIAL_COLS; j++)
            if (room[i][j]=='X') {
                row=i;
                col=j;
            }

    if (row>0 && col>0)
        if (room[row][col+1]==' ') {
            room[row][col]=' ';
            room[row][col+1]='X';
            return 1;
        }
    
    return 0;

}

int move_player(char** room) {
    int key_pressed;
    int result=0;

    key_pressed= tolower(get_key_pressed());

    switch (key_pressed) {
        case MOVE_PLAYER_UP: result=move_player_up(room); break;
        case MOVE_PLAYER_BACK: result=move_player_down(room); break;
        case MOVE_PLAYER_LEFT: result=move_player_left(room); break;
        case MOVE_PLAYER_RIGHT: result=move_player_right(room); break;
        case EXIT_GAME: return -1;
    }
    return result;

}

void reset_player(player* pl) {
    if (pl!=NULL) {
        pl->health= PLAYER_STANDARD_HEALTH;
        pl->atk= PLAYER_STANDARD_ATK;
        pl->def= PLAYER_STANDARD_DEF;
    }
}

void reset_enemy(enemy* pl) {
    if (pl!=NULL)
        switch (pl->type) {
            case 0: //goblin
                pl->atk= GOBLIN_STANDARD_ATK;
                pl->def= GOBLIN_STANDARD_DEF;
                pl->health= GOBLIN_STANDARD_HEALTH;
                break;
            case 1: break;
            case 2: break;
        }
}

int get_player_row(char** room) {
    int i, j;

    for(i = 0; i < TUTORIAL_ROWS; i++)
        for (j=0; j<TUTORIAL_COLS; j++)
            if (room[i][j]=='X') return i;
    return -1;
}

int get_player_col(char** room) {
    int i, j;

    for(i = 0; i < TUTORIAL_ROWS; i++)
        for (j=0; j<TUTORIAL_COLS; j++)
            if (room[i][j]=='X') return j;
    return -1;
}

int is_player_near_enemy(char** room) {
    int i,j;
    int row= (get_player_row(room));
    int col= (get_player_col(room));

    row+=1;
    col-=1;

    for (i=0; i<ENEMY_CLOSE_RANGE; i++)
        for (j=0; j<ENEMY_CLOSE_RANGE; j++)
            if (room[row-i][col+j]=='O') return 1;
    
    return 0;

}

void print_collect_message(enemy* defeated) {
    if (defeated!=NULL) {
        printf(ANSI_COLOR_CYAN);
        printf("[" ANSI_FONT_BOLD "INVENTORY" ANSI_FONT_RESET ANSI_COLOR_CYAN "] Collected %d coins",defeated->coin_drop);
        printf(ANSI_COLOR_RESET);
    }
        
}

void remove_enemy_from_map(char** room, int row, int col) {
    room[row][col]=' ';
}

int get_near_monster_row(char** room) {
    int i,j;
    int row= (get_player_row(room));
    int col= (get_player_col(room));

    row+=1;
    col-=1;

    for (i=0; i<ENEMY_CLOSE_RANGE; i++)
        for (j=0; j<ENEMY_CLOSE_RANGE; j++)
            if (room[row-i][col+j]=='O') return (row-i);
    return 0;
}

int get_near_monster_col(char** room) {
    int i,j;
    int row= (get_player_row(room));
    int col= (get_player_col(room));

    row+=1;
    col-=1;

    for (i=0; i<ENEMY_CLOSE_RANGE; i++)
        for (j=0; j<ENEMY_CLOSE_RANGE; j++)
            if (room[row-i][col+j]=='O') return (col+j);
    return 0;
}

int is_player_near_exit(char** room) {
    int row= (get_player_row(room));
    int col= (get_player_col(room));

    if (room[row+1][col]=='+' || room[row-1][col]=='+' || room[row][col+1]=='+' || room[row][col-1]=='+') return 1;
    return 0;
}

int is_player_near_chest(char** room) {
    int i,j;
    int row= (get_player_row(room));
    int col= (get_player_col(room));

    row+=1;
    col-=1;

    for (i=0; i<PLAYER_RANGE; i++)
        for (j=0; j<PLAYER_RANGE; j++)
            if (room[row-i][col+j]=='@') return 1;
    
    return 0;
}

int get_chest_option(chest* cptr) {
    int option;

    printf(ANSI_COLOR_YELLOW);
    printf("\n\n=== WHAT DO YOU WANT TO DO? ===\n");
    puts("[1] Open");
    puts("[2] Inspect");
    puts("[3] Ignore");
    printf(ANSI_FONT_ITALIC "\nPress the number to choose an action\n" ANSI_FONT_RESET);
    option = get_key_pressed();

    switch (option) {
        case ONE:
            return open_chest(cptr);
        case TWO:
            inspect_chest(cptr);
            return 0;
        case THREE:
            say("I'll open that later");
            return 0;
    }

    return -1;
}

int open_chest(chest* cptr) {
    if (cptr->is_locked) puts("LOCKED");
    else if (cptr->is_enemy) puts("ENEMY");
    else {
        if (cptr->payoff_type==COINS) return cptr->coins;
    }
    return -1;
}

void inspect_chest(chest* cptr) {
    int inspect_prob= rand()%100;

    //TODO: upgrade
     say("It's a normal chest");
    
}

void say(char* message) {
    printf(ANSI_COLOR_GREEN ANSI_FONT_BOLD"[YOU] " ANSI_COLOR_RESET ANSI_COLOR_GREEN "%s\n\n" ANSI_COLOR_RESET,message);
}

void remove_chest_from_map(char** room, int row, int col) {
    room[row][col]=' ';
}

int get_near_chest_row(char** room) {
    int i,j;
    int row= (get_player_row(room));
    int col= (get_player_col(room));

    row+=1;
    col-=1;

    for (i=0; i<PLAYER_RANGE; i++)
        for (j=0; j<PLAYER_RANGE; j++)
            if (room[row-i][col+j]=='@') return (row-i);
    return 0;
}

int get_near_chest_col(char** room) {
    int i,j;
    int row= (get_player_row(room));
    int col= (get_player_col(room));

    row+=1;
    col-=1;

    for (i=0; i<PLAYER_RANGE; i++)
        for (j=0; j<PLAYER_RANGE; j++)
            if (room[row-i][col+j]=='@') return (col+j);
    return 0;
}