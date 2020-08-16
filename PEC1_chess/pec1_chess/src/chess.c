#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "chess.h"


/* Auxiliary functions ****************************************************/

/**************************************************************************/
tPlayer *find_Player (tChessTournament c, int idPlayer)
/**************************************************************************/
{
	
	tPlayer *res;
  int  i;

  i   = 0;
  res = NULL;
  
  while ((i < c.playersNum) && (res == NULL)) {
        if (c.playerList[i].idPlayer == idPlayer)
           res = &(c.playerList[i]);
        else
           i++;
  }

  return res;
}


tPairing *find_Pairing (tChessTournament c, int idPairing)
/**************************************************************************/
{
	
	tPairing *res;
  int  i;

  i   = 0;
  res = NULL;
  
  while ((i < c.rounds[i].pairingNum) && (res == NULL)) {
        if (c.rounds[i].paring[i].idPairing == idPairing)
           res = &(c.rounds[i].paring[i]);
        else
           i++;
  }

  return res;
}

tRound *find_Round (tChessTournament c, int roundId)
/**************************************************************************/
{
	
	tRound *res;
  int  i;

  i   = 0;
  res = NULL;
  
  while ((i < c.roundsNum) && (res == NULL)) {
        if (c.rounds[i].roundId == roundId)
           res = &(c.rounds[i]);
        else
           i++;
  }

  return res;
}





void *elo_level ( int elo)
/**************************************************************************/


{
	
		
	if ((elo > 0) && (elo <= 1800)){
		  elo = novice;
		  
	if ((elo > 1800) && (elo <= 2000)){
		  elo = medium;
	
	if ((elo > 2000) && (elo <= 2400)){
		  elo = advanced;
	
	if (elo > 2400){
		  elo = master;
		  
				}	
		
			}
		}
	}
		
}	

  

/* Demanded functions ****************************************************/

/**************************************************************************/
  void init_chess_tournament (tChessTournament *c)
/**************************************************************************/
{
/* Check PRE conditions */
	assert(c != NULL);
	
  /* Structures */
  strcpy((*c).chessTournamentName,"OPEN CHESS 2020");
  strcpy((*c).location,"SPAIN");
  c->date = 3012020;
  c->playersNum = 0;
  c->roundsNum = 0;
}

/**************************************************************************/
  void new_player (tChessTournament *c, int idPlayer, string namePlayer, int age, string nationality, int elo)
/**************************************************************************/
{
	
	tTypeLevel level;
	
		/* Check PRE conditions */ 
  assert(c != NULL);
  assert(idPlayer > 0);

  /* Search the player */
  
  if (find_Player(*c, idPlayer) != NULL){
  printf("NO PLAYER FOUND \n");
 
 }else{
	  
	  
	  /* it does not exist, allocate space */
	  
	  if (c->playersNum == 0){
		  
		  c->playerList = (tPlayer *) malloc(sizeof(tPlayer));
		  
	  }else{
		  
		c->playerList = (tPlayer*)realloc(c->playerList, (c->playersNum+1)* sizeof(tPlayer));
		  
	  }
	  
	  	  /* if it is ok, then add the player */

		if (c->playerList == NULL){
		printf ("Error");
		}else{
		
		
		c->playerList[c->playersNum].idPlayer = idPlayer;
		strcpy(c->playerList[c->playersNum].namePlayer, namePlayer);
		c->playerList[c->playersNum].age = age;
		strcpy(c->playerList[c->playersNum].nationality, nationality);
		c->playerList[c->playersNum].elo = elo;
		elo_level( c->playerList[c->playersNum].elo) == level ;
		c->playersNum++;
		
	  
	}
	
	  
  }


}

/**************************************************************************/

void new_round (tChessTournament *c, int roundId)

{
	
		int i;
		
		i = c->roundsNum;
		
		c->rounds[i].roundId = roundId;
		c->rounds[i].pairingNum = 0;
		c->rounds[i].whiteWinsNum = 0;
		c->rounds[i].blackWinsNum = 0;
		c->rounds[i].drawWinsNum = 0;
		c->roundsNum++;
		

}
	


/**************************************************************************/

/**************************************************************************/

void add_pairing (tChessTournament *c, int idPairing, int idPlayer1, int idPlayer2, int roundId){
	
tPlayer *one;
tPlayer *two;
tPairing *par;
tRound *round;
int i;



/* Search the round */
round = find_Round (*c, roundId);
  
/* Search the player */
one = find_Player(*c, idPlayer1);
two = find_Player(*c, idPlayer2);

/* Search the par */
par= find_Pairing (*c, idPairing);

  
if (round == NULL){
	printf("ERROR, round not found \n");
	} else { 
	  
for (i=0; round->pairingNum <= 5; i++){
		

  
if ((one == NULL) && (one != c->playerList))  {

printf("Error \n");
	} else{
		
		
		//match_player_par ( one->idPlayer, par->idWhite);
		
	}
	
if ((two == NULL) && (two != c->playerList))  {

printf("Error \n");
	} else{
		
		//t = s->idBlack;
	}
	
      round->pairingNum = round->pairingNum + 1;

	}
	
  }

		
}	  

/**************************************************************************/

/**************************************************************************/
void print_round_pairings (tChessTournament c, int roundsNum)
  
{


tRound r;
int i;
printf("\n");
  

  for (i=0; i < c.roundsNum; i++) {
	  
	  r = c.rounds[i];
	
      
	printf ("************************************** \n"); 
	printf ("************************************** \n");
printf ("Chess Tournament Name: %s \n",c.chessTournamentName);
printf ("Location: %s \n", c.location);
printf ("Date: %d \n", c.date);
printf ("Players Num: %d \n", c.playersNum);
	printf ("************************************** \n");
printf("ROUND:%d \n", r.roundId);
	printf ("************************************** \n");
printf("White Wins Num:%d \n", r.whiteWinsNum);
printf("Black Wins Num:%d \n", r.blackWinsNum);
printf("Draw Num:%d \n", r.drawWinsNum);
printf ("************************************** \n");
printf("Pairing ID:%d \n", r.paring[i].idPairing);
printf("Number of pairing :%d \n", r.pairingNum);
printf("Name :%s \n", c.playerList[i].namePlayer);
printf("Age :%d \n", c.playerList[i].age);
printf("Nationality :%s \n", c.playerList[i].nationality);
printf("Elo :%d \n", c.playerList[i].elo);

	}
  

}


/**************************************************************************/
