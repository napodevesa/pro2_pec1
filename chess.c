#include "chess.h"

/* Auxiliary functions ****************************************************/

/**************************************************************************/
 tPlayer *find_player (tChessTournament c, int id)
/**************************************************************************/
{
  tPlayer *p;
  int  i;

  p = NULL;
  i  = 0;  
  
  while ((i < c.numPlayers) && (p == NULL)) {
        if (c.players[i].id == id)
           p = &(c.players[i]);
        else
           i++;
  }

  return p;
}

/**************************************************************************/
 tPlayer *find_player_round (tChessTournament c, int number, int id)
/**************************************************************************/
{
   tRound r;
   tPlayer *p;
   int i;
   
   r = c.rounds[number-1];
   p = NULL;   
   i = 0;   
  
   while ((i < r.numPairings) && (p == NULL)){
	   if ((r.pairings[i].idWhitePlayer == id) || (r.pairings[i].idBlackPlayer == id))
           p = find_player(c, id);
        else
           i++;
   }
   
   return p;   
}

/**************************************************************************/
void set_player_level (tPlayer *p, int elo)
/**************************************************************************/
{
  tLevel l;

  if (elo <= L1) l = novice; 
  else if (elo <= L2) l = medium;
  else if (elo <= L3) l = advanced;
  else l = master;
  
  p->level = l;
}


/* Demanded functions ****************************************************/

/**************************************************************************/
 void init_chess_tournament (tChessTournament *c)
/**************************************************************************/
{
  // Check PRE conditions
  assert(c != NULL);

  // Empty structures
  strcpy(c->name, "OPEN CHESS 2020");
  strcpy(c->location, "SPAIN");
  c->date.day = 30;
  c->date.month = 1;
  c->date.year = 2020;
  c->numPlayers = 0;
  c->numRounds = 0;
}

/**************************************************************************/
void new_player (tChessTournament *c, int id, string name, int age, string nationality, int elo)
/**************************************************************************/
{
  // Check PRE conditions
  assert (c != NULL);
  assert (id > 0);
  assert (strcmp(name, "") != 0);
  assert (age > 0);
  assert (strcmp(nationality, "") != 0);
  assert (elo > 0);

  // Search the player
  if (find_player (*c, id) != NULL)
      printf("ERROR: Player %d is already in the list of players\n", id);
  else {
      // It does not exist, allocate space
      if (c->numPlayers == 0)
		  c->players = (tPlayer *) malloc(sizeof(tPlayer));
      else 
		  c->players = (tPlayer *) realloc(c->players, (c->numPlayers+1)*sizeof(tPlayer));

      // If it is ok, then add the player to the list of players       
      if (c->players == NULL)
	      printf("ERROR: Memory error\n");
      else {	  
		  c->players[c->numPlayers].id = id;
		  strcpy(c->players[c->numPlayers].name, name);
		  c->players[c->numPlayers].age = age;
		  strcpy(c->players[c->numPlayers].nationality, nationality);
		  c->players[c->numPlayers].elo = elo;
		  set_player_level (&c->players[c->numPlayers], elo);
		  c->numPlayers++;
      }
  }
}

/**************************************************************************/
void new_round (tChessTournament *c, int number)
/**************************************************************************/
{
  // Check PRE conditions
  assert (c != NULL);
  assert (number >= 1);
  assert (number <= 9);
	
  c->rounds[number-1].number = number;
  c->rounds[number-1].numPairings = 0;
  c->rounds[number-1].numWhiteWins = 0;
  c->rounds[number-1].numBlackWins = 0;
  c->rounds[number-1].numDraws = 0;
  c->numRounds++;
}

/**************************************************************************/
void add_pairing (tChessTournament *c, int idp, int idw, int idb, int number)
/**************************************************************************/
{
  tPlayer *pw, *pb;
	
  // Check PRE conditions
  assert (c != NULL);
  assert (idp > 0);
  assert (idw > 0);
  assert (idb > 0);
  assert (number >= 1);
  assert (number <= 9);  

  // Search the players
  pw = find_player (*c, idw);
  pb = find_player (*c, idb);
  
  if (pw == NULL)
  	printf("ERROR while pairing player %d. He/she does not appear in the list of players\n", idw);
  if (pb == NULL)
  	printf("ERROR while pairing player %d. He/she does not appear in the list of players\n", idb);
	
  //If both players exist in the list of players we search if players are already in that round	
  if ((pw != NULL) && (pb != NULL)) {	
	pw = find_player_round (*c, number, idw);
	pb = find_player_round (*c, number, idb);
	
	  if (pw != NULL)
		printf("ERROR while pairing player %d. He/she is already paired in round %d\n", idw, number);
	  if (pb != NULL)
		printf("ERROR while pairing player %d. He/she is already paired in round %d\n", idb, number);
	
	  //If both players don't exist in that round and the round is not full of pairings, we add the pairing
	  if ((pw == NULL) && (pb == NULL)) {
			if (c->rounds[number-1].numPairings < MAX_PAIRINGS){
				// Add the pairing to the round								
				c->rounds[number-1].pairings[c->rounds[number-1].numPairings].idPairing = idp;
				c->rounds[number-1].pairings[c->rounds[number-1].numPairings].idWhitePlayer = idw;
				c->rounds[number-1].pairings[c->rounds[number-1].numPairings].idBlackPlayer = idb;
				if (rand()%3+1 == 1) {
					c->rounds[number-1].pairings[c->rounds[number-1].numPairings].result = whiteWins;
					c->rounds[number-1].numWhiteWins++;
				}
				else if (rand()%3+1 == 2) {
					c->rounds[number-1].pairings[c->rounds[number-1].numPairings].result = blackWins;
					c->rounds[number-1].numBlackWins++;
				}
				else {
					c->rounds[number-1].pairings[c->rounds[number-1].numPairings].result = draw;	
					c->rounds[number-1].numDraws++;
				}
				c->rounds[number-1].numPairings++;	
			}else{
				printf("ERROR while adding the pairing %d to round %d. It is already full of pairings\n", idp, number);
			}
		}			
	}
}

/**************************************************************************/
void print_round_pairings (tChessTournament c, int number)
/**************************************************************************/
{  
  tRound r;  
  tPlayer *wp, *bp;
  int i, pai, ww, bw, dr, idp, idw, idb, res;
  
  r = c.rounds[number-1];
  pai = r.numPairings;
  ww = r.numWhiteWins;
  bw = r.numBlackWins;
  dr = r.numDraws;
  
  printf("\n******************************************************************");
  printf("\n%s\t%s\t%d/%d/%d\t(%d players in the tournament)", c.name, c.location, c.date.day, c.date.month, c.date.year, c.numPlayers);
  printf("\n******************************************************************");
  printf("\nROUND %d\n", number);
  printf("------------------------------------------------------------------");
  printf("\nNumber of pairings: %d", pai);
  printf("\nNumber of wins with white pieces: %d", ww);
  printf("\nNumber of wins with black pieces: %d", bw);
  printf("\nNumber of draws: %d\n", dr);  
  
  for (i=0; i<pai; i++){
	  idp = r.pairings[i].idPairing;
	  idw = r.pairings[i].idWhitePlayer;
	  idb = r.pairings[i].idBlackPlayer;
	  wp = find_player (c, idw);
	  bp = find_player (c, idb);
	  res = r.pairings[i].result;	  
	  printf("\nPairing id: %d", idp);
	  printf("\nWhite: %s, %d years old, from %s, %d elo", wp->name, wp->age, wp->nationality, wp->elo);
	  printf("\nBlack: %s, %d years old, from %s, %d elo", bp->name, bp->age, bp->nationality, bp->elo);
	  printf("\nResult: ");
	  if (res == 0) printf("White wins\n");
	  else if (res == 1) printf ("Black wins\n");
	  else printf("Draw\n");
	
  }
  printf("\n******************************************************************\n\n");
}



