#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "const.h"
#include "types.h"
#include "utilities.h"

int start_fight(player* pl, enemy* ms);
void print_fight_title();
void print_fight_table();
void print_stats(player* pl, enemy* ms);
void randomize_fight(player* pl, enemy* ms);

int start_fight(player* pl, enemy* ms) {
    if (pl!=NULL && ms!=NULL) {
        print_fight_title();
        printf("\n");
        print_stats(pl,ms);
        printf("\n");
        printf(ANSI_FONT_ITALIC "Press any key to skip to next phase" ANSI_FONT_RESET);
        get_key_pressed();
        randomize_fight(pl,ms);
        printf(ANSI_FONT_ITALIC "Press any key to end the battle" ANSI_FONT_RESET);
        get_key_pressed();
        if (pl->health>0) return 1;
        else return 0;
    }
    return -1;
}

void print_fight_title() {
    char read_string[FIGHT_TITLE_LENGHT];
    char* file_name="ascii_art/fight_title.txt";
    FILE *file_ptr= NULL;

    if((file_ptr = fopen(file_name,"r")) == NULL)
        fprintf(stderr,"error opening %s\n",file_name);

    printf(ANSI_COLOR_YELLOW);
 
    while(fgets(read_string,sizeof(read_string),file_ptr) != NULL)
        printf("%s",read_string);
    printf(ANSI_COLOR_RESET "\n");
 
    fclose(file_ptr);
}

void print_fight_table() {
    char read_string[FIGHT_TITLE_LENGHT];
    char* file_name="ascii_art/fight_table.txt";
    FILE *file_ptr= NULL;

    if((file_ptr = fopen(file_name,"r")) == NULL)
        fprintf(stderr,"error opening %s\n",file_name);

    printf(ANSI_COLOR_YELLOW);
 
    while(fgets(read_string,sizeof(read_string),file_ptr) != NULL)
        printf("%s",read_string);
    printf(ANSI_COLOR_RESET "\n");
 
    fclose(file_ptr);
}

void print_stats(player* pl, enemy* ms) {
    print_fight_table();
    printf("HEALTH:\t%d\t\t\t\tHEALTH:\t%d\n",pl->health,ms->health);
    printf("ATTACK:\t%d\t\t\t\tATTACK:\t%d\n",pl->atk,ms->atk);
    printf("DEF:   \t%d\t\t\t\tDEF:   \t%d\n",pl->def,ms->def);
}

void randomize_fight(player* pl, enemy* ms) {
    int turn= rand()%1;
    int damage;

    do {
        switch (turn) {
            case 0: //player
                damage= (ms->def)-(pl->atk);
                ms->health+= (damage<0)*damage;
                break;
            case 1: //enemy
                damage= (pl->def)-(ms->atk);
                pl->health+= (damage<0)*damage;
                break;
        }
        clear_screen();
        print_stats(pl,ms);
        printf("\n");
        if (!turn) printf("Enemy losts %d health points",(-1)*damage);
        else printf("You lost %d health points",(-1)*damage);
        printf("\n\n");
        turn= !turn;
        printf(ANSI_FONT_ITALIC "Press any key to skip to next phase" ANSI_FONT_RESET);
        get_key_pressed();
    } while (pl->health>0 && ms->health>0);
    
}