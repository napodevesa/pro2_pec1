#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Constants *********************************************************/

#define MAX_PAIRINGS  5
#define MAX_ROUNDS   9
#define MAX_CHAR   100
#define L1   1800
#define L2   2000
#define L3   2400


/* Types *************************************************************/

typedef enum {false, true} bool;
typedef enum {master, advanced, medium, novice} tLevel;
typedef enum {whiteWins, blackWins, draw} tResult;
typedef char string[MAX_CHAR+1];

typedef struct {
	int day; 
	int month;
	int year;
} tDate;

typedef struct {
	int id;
	string name;
	int age;
	string nationality;
	int elo;
	tLevel level;
} tPlayer;

typedef struct {
	int idPairing;
	int idWhitePlayer;
	int idBlackPlayer;
	tResult result;
} tPairing;

typedef struct {
	int number;
	tPairing pairings[MAX_PAIRINGS];
	int numPairings;
	int numWhiteWins;
	int numBlackWins;
	int numDraws;
} tRound;

typedef struct {
	string name;
	string location;
	tDate date;
	tPlayer *players;
	int numPlayers;
	tRound rounds[MAX_ROUNDS];
	int numRounds;
} tChessTournament;


/* Functions *********************************************************/

void init_chess_tournament (tChessTournament *c);
void new_player (tChessTournament *c, int id, string name, int age, string nationality, int elo);
void new_round (tChessTournament *c, int number);
void add_pairing (tChessTournament *c, int idp, int idw, int idb, int number);
void print_round_pairings (tChessTournament c, int number);


