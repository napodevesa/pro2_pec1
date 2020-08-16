

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/* Constants *********************************************************/

//#define 
#define MAX_CHAR 100
#define MAX_PAR 5
#define MAX_ROUND 9

/* Types *************************************************************/
typedef char string [MAX_CHAR+1];
typedef enum {false, true} bool;
typedef enum {whiteWins, blackWins, draw} tTypeResult;
typedef enum {novice, medium, advanced, master} tTypeLevel;


typedef struct {
	int idPlayer;
	string namePlayer;
	int age;
	string nationality;
	int elo;
	tTypeLevel level;
} tPlayer;

typedef struct {
  
	int idPairing;
	int idWhite;
	int idBlack;
	tTypeResult result;

} tPairing;


typedef struct {
    int day, month, year;
} tDate;


typedef struct {
	
	int roundId;
	tPairing paring[MAX_PAR];
	int pairingNum ;
	int whiteWinsNum;
	int blackWinsNum;
	int drawWinsNum;

} tRound;


typedef struct {
	
	string chessTournamentName;
	string location;
	tDate *date;
	tPlayer *playerList;
	int playersNum;
	tRound rounds [MAX_ROUND];
	int roundsNum;
  
} tChessTournament;

/* Functions *********************************************************/

void init_chess_tournament (tChessTournament *c);
void new_player (tChessTournament *c, int idPlayer, string name, int age, string nationality, int elo);
void new_round (tChessTournament *c, int roundId);
void add_pairing (tChessTournament *c, int idPairing, int idPlayer1, int idPlayer2, int round);
void print_round_pairings (tChessTournament c, int round);
int rand ();
