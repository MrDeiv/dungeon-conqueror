#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fight.h"
#include "const.h"

#include "roomBuilder.h"
#include "tutorial.h"

void print_start_title();
void print_start_subtitle();
int boolean_menu();

int main() {
    char** room;
    char player_name[PLAYER_NAME_MAX_LENGHT];
    char start_key=' ';
    int i,j;
    int player_choice=1;

    //room=  get_room(10,20);
    srand(time(NULL));
    
    clear_screen();
    print_start_title();
    print_start_subtitle();
    printf("\n");

    start_key= tolower(get_key_pressed());
    
    if (start_key==START_KEY) {
        do {
            clear_screen();
            printf(ANSI_COLOR_YELLOW);
            puts("Welcome hero, can you tell me your name? (MAX 16 CHARACTERS)");
            printf(ANSI_COLOR_GREEN);
            fflush(stdin);
            scanf("%s",player_name);
            printf(ANSI_COLOR_YELLOW);
            printf("\n\nYour name is " ANSI_COLOR_CYAN "%s" ANSI_COLOR_YELLOW ", correct?",player_name);
            player_choice= boolean_menu();

        } while (!player_choice);
        clear_screen();
        printf(ANSI_COLOR_YELLOW);
        printf("Oh, %s, what a nice name! ",player_name);
        puts("Well, here is where the fun begin... are you an expert traveler? Or do you want a fast tutorial?");
        puts("Choose YES if you want to play the tutorial, else choose NO");
        player_choice = boolean_menu();
        if (player_choice) start_tutorial();
    }

    /* for (i=0; i<10; i++) {
        for (j=0; j<20; j++)
            printf("%c",room[i][j]);
        printf("\n");
    } */
}

void print_start_title() {
    char read_string[ASCII_ART_MAX_LEN];
    char* file_name="ascii_art/start_title.txt";
    FILE *file_ptr= NULL;

    if((file_ptr = fopen(file_name,"r")) == NULL)
        fprintf(stderr,"error opening %s\n",file_name);

    printf(ANSI_COLOR_YELLOW);
 
    while(fgets(read_string,sizeof(read_string),file_ptr) != NULL)
        printf("%s",read_string);
    printf(ANSI_COLOR_RESET "\n");
 
    fclose(file_ptr);
}

void print_start_subtitle() {
    char message[] ="Press E then SEND to start";
    int msg_lenght= strlen(message);
    int equals_number= (ASCII_ART_MAX_LEN-(msg_lenght+2))/2;
    int i;

    printf(ANSI_COLOR_RED);
    for (i=0; i<equals_number; i++) printf("=");
    printf(ANSI_COLOR_YELLOW "  %s ",message);
    printf(ANSI_COLOR_RED);
    for (i=0; i<equals_number; i++) printf("=");
    printf(ANSI_COLOR_RESET);
}

int boolean_menu() {
    int choice=1;
    char key_pressed;

    puts("Press K to confirm your choice, W or S to choose another one");
    do {
        if (choice) {
            printf(ANSI_COLOR_YELLOW "> [" ANSI_COLOR_GREEN "YES" ANSI_COLOR_YELLOW "] <\n");
            printf(ANSI_COLOR_YELLOW "  [" ANSI_COLOR_RED "NO" ANSI_COLOR_YELLOW "]\n");
        } else {
            printf(ANSI_COLOR_YELLOW "  [" ANSI_COLOR_GREEN "YES" ANSI_COLOR_YELLOW "]\n");
            printf(ANSI_COLOR_YELLOW "> [" ANSI_COLOR_RED "NO" ANSI_COLOR_YELLOW "] <\n");
        }
        key_pressed= tolower(get_key_pressed());
        if (key_pressed== UP_KEY && choice==1) choice=0;
        else if (key_pressed== UP_KEY && choice==0) choice= 1;
        else if (key_pressed== DOWN_KEY && choice==1) choice=0;
        else if (key_pressed== DOWN_KEY && choice==0) choice=1;

    } while (key_pressed != CONFIRM_KEY);

    return choice;
    
}