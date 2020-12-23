#include "const.h"

//ENUM TYPES
typedef enum {
    GOBLIN,
    SKELETON,
    ZOMBIE
} enemy_type;

typedef enum {
    COMMON,
    UNCOMMON,
    EPIC,
    LEGENDARY
} rarity;

typedef enum {
    COINS,
    OBJECT
} reward;

//TYPES
typedef struct {
    char name[PLAYER_NAME_MAX_LENGHT];
    int health;
    int atk;
    int def;
    int coins;
} player;

typedef struct {
    enemy_type type;
    int id;
    int health;
    int atk;
    int def;
    int coin_drop;
} enemy;

typedef struct {
    int id;
    rarity rareness;
    reward payoff_type;
    int coins;
    int is_enemy;
    int is_locked;
} chest;
