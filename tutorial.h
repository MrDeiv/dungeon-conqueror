#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "const.h"

void load_room(char** room);
void print_room(char** room);
void print_colored_wall(char** room);
void print_colored_enemy(char** room);
void print_colored_exit(char** room);
void print_colored_chest(char** room);
void print_colored_player(char** room);

int start_tutorial() {
    int i;
    int move_result;
    int action_result;
    int step= TUTORIAL_STEP_NUMBER;
    int theres_chest_to_open= 1;
    char key_pressed;
    char **room= (char**)malloc(TUTORIAL_ROWS*sizeof(char*));

    player user;
    player* user_ptr;

    user_ptr= &user;
    reset_player(user_ptr);

    for (i=0; i<TUTORIAL_ROWS; i++) room[i]= (char*)malloc(TUTORIAL_COLS*sizeof(char));
    load_room(room);

    do {
        clear_screen();
        printf(ANSI_COLOR_YELLOW);
        puts("Well, welcome to the tutorial room! Here nobody can hurt you and yes... this mean that in others room someone can");
        printf(ANSI_COLOR_RESET "\n");

        switch (step) {
            case 6:
                print_room(room);
                printf(ANSI_COLOR_YELLOW "\n");
                puts("This is a sample room: how you can see, there are some elements");
                break;
            case 5:
                print_colored_wall(room);
                printf(ANSI_COLOR_YELLOW);
                printf("\n\n");
                printf("These in " ANSI_COLOR_CYAN "cyan" ANSI_COLOR_YELLOW " are WALLS: you can't pass through them!");
                break;
            case 4:
                print_colored_enemy(room);
                printf(ANSI_COLOR_YELLOW);
                printf("\n\n");
                printf("This in " ANSI_COLOR_GREEN "green" ANSI_COLOR_YELLOW " is an ENEMY: when you will be too close to him, he will attack you!");
                break;
            case 3:
                print_colored_exit(room);
                printf(ANSI_COLOR_YELLOW);
                printf("\n\n");
                printf("This in " ANSI_COLOR_MAGENTA "magenta" ANSI_COLOR_YELLOW " is an EXIT: through her you can go in another room. Probably you will find more than 1 exit per room in your adventure");
                break;
            case 2:
                print_colored_chest(room);
                printf(ANSI_COLOR_YELLOW);
                printf("\n\n");
                printf("Finishing, this in " ANSI_COLOR_RED "red" ANSI_COLOR_YELLOW " is a CHEST: open her to get a random bonus!");
                break;
            case 1:
                print_colored_player(room);
                printf(ANSI_COLOR_YELLOW);
                printf("\n\n");
                printf("Here you are: this in " ANSI_COLOR_BLUE "blue" ANSI_COLOR_YELLOW " are you: let's start this demo now.");
                break;
        }
        printf(ANSI_FONT_ITALIC "\nPress any key to skip to next step" ANSI_FONT_RESET);
        printf("\n\n");
        get_key_pressed();
        step--;
    } while (step>0);

    clear_screen();
    printf(ANSI_COLOR_RESET);
    print_room(room);
    printf(ANSI_COLOR_YELLOW "\n");
    print_fast_guide();

    do {
        move_result= move_player(room);
        if (move_result!=-1) {
            clear_screen();
            printf(ANSI_COLOR_YELLOW);
            puts("Ok, start to explore\n");
            printf(ANSI_COLOR_RESET);
            if (is_player_near_enemy(room)) {
                print_colored_enemy(room);
                printf("\n\n");
                printf(ANSI_COLOR_YELLOW);
                puts("Ok, keep calm. The goblin is watching you...");
                printf(ANSI_FONT_ITALIC "Press any key to start the fight" ANSI_FONT_RESET);
                printf("\n\n");
                get_key_pressed();
                clear_screen();

                player tutorial_player;
                player *player_ptr;
                enemy tutorial_enemy;
                enemy *enemy_ptr;

                player_ptr= &tutorial_player;
                
                tutorial_enemy.type= GOBLIN;
                tutorial_enemy.coin_drop= GOBLIN_STANDARD_COIN_DROP;
                tutorial_enemy.id= 1;
                enemy_ptr= &tutorial_enemy;

                reset_player(player_ptr);
                reset_enemy(enemy_ptr);

                if (start_fight(player_ptr,enemy_ptr)) {
                    clear_screen();
                    printf(ANSI_COLOR_YELLOW);
                    printf("Wow! Incredible! You you kick goblin's ass like a master... WOW\n");
                    printf("Look the ground, goblin drops %d coins during the fight. NICE!\n\n",tutorial_enemy.coin_drop);
                    print_collect_message(enemy_ptr);
                    remove_enemy_from_map(room,get_near_monster_row(room),get_near_monster_col(room));
                    printf(ANSI_FONT_ITALIC "\nPress any key to continue\n" ANSI_FONT_RESET);
                    get_key_pressed();
                } else printf("You lose");
            } else if (is_player_near_exit(room)) {
                if (theres_chest_to_open)
                    printf(ANSI_FONT_ITALIC ANSI_COLOR_CYAN "\nI think you have a chest to open...\n" ANSI_FONT_RESET);
                else {
                    clear_screen();
                    puts("END");
                    exit(0);
                }
            } else if (is_player_near_chest(room)) {
                print_colored_chest(room);

                chest tutorial_chest;
                chest* chest_ptr;

                tutorial_chest.id=1;
                tutorial_chest.coins= 1000;
                tutorial_chest.payoff_type= COINS;
                tutorial_chest.is_enemy= 0;
                tutorial_chest.is_locked= 0;

                chest_ptr= &tutorial_chest;

                action_result= get_chest_option(chest_ptr);
                if (action_result) {
                    say("Nice, i found some coins in the chest");
                    remove_chest_from_map(room,get_near_chest_row(room),get_near_chest_col(room));
                    theres_chest_to_open--;
                }
                printf(ANSI_FONT_ITALIC "\nPress any key to continue\n" ANSI_FONT_RESET);
                get_key_pressed();
                clear_screen();
            }
            print_room(room);
            printf(ANSI_COLOR_YELLOW);
            print_fast_guide();
        } else if (move_result==-1) exit(0); //TODO: change this if clause

    } while (LOOP);

    for (i=0; i<TUTORIAL_ROWS; i++) free(room[i]);
    free(room);
    room= NULL;

    return 1;
}

void load_room(char** room) {
    int i,j;
    char* file_name="ascii_art/tutorial_room.txt";
    FILE *file_ptr= NULL;
    char line[TUTORIAL_COLS+1];

    file_ptr = fopen(file_name,"r");

    if (file_ptr!=NULL) {
        while (fgets(line, sizeof(line), file_ptr) && i<TUTORIAL_ROWS) {
            strcpy(room[i],line);
            i++;
        }
        fclose(file_ptr);
    }

}

void print_room(char** room) {
    int i;

    for(i = 0; i < TUTORIAL_ROWS; i++) printf("%s",room[i]);
    printf("\n");

}

void print_colored_wall(char** room) {
    int i,j;

    for(i = 0; i < TUTORIAL_ROWS; i++)
        for (j=0; j<TUTORIAL_COLS; j++) {
            if (room[i][j]=='#') printf(ANSI_COLOR_CYAN "%c",room[i][j]);
            else printf("%c",room[i][j]);
            printf(ANSI_COLOR_RESET);
        }

}

void print_colored_enemy(char** room) {
    int i,j;

    for(i = 0; i < TUTORIAL_ROWS; i++)
        for (j=0; j<TUTORIAL_COLS; j++) {
            if (room[i][j]=='O') printf(ANSI_COLOR_GREEN "%c",room[i][j]);
            else printf("%c",room[i][j]);
            printf(ANSI_COLOR_RESET);
        }

}

void print_colored_exit(char** room) {
    int i,j;

    for(i = 0; i < TUTORIAL_ROWS; i++)
        for (j=0; j<TUTORIAL_COLS; j++) {
            if (room[i][j]=='+') printf(ANSI_COLOR_MAGENTA "%c",room[i][j]);
            else printf("%c",room[i][j]);
            printf(ANSI_COLOR_RESET);
        }

}

void print_colored_chest(char** room) {
    int i,j;

    for(i = 0; i < TUTORIAL_ROWS; i++)
        for (j=0; j<TUTORIAL_COLS; j++) {
            if (room[i][j]=='@') printf(ANSI_COLOR_RED "%c",room[i][j]);
            else printf("%c",room[i][j]);
            printf(ANSI_COLOR_RESET);
        }

}

void print_colored_player(char** room) {
    int i,j;

    for(i = 0; i < TUTORIAL_ROWS; i++)
        for (j=0; j<TUTORIAL_COLS; j++) {
            if (room[i][j]=='X') printf(ANSI_COLOR_BLUE "%c",room[i][j]);
            else printf("%c",room[i][j]);
            printf(ANSI_COLOR_RESET);
        }

}