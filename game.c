#include "game.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <physics.h>

void initiateGame(char* filename, Map* outMap, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {

    int i , j , k , temp;
    FILE* Pacy;

    Pacy=fopen("/Users/sara/Desktop/project/cmake-build-debug/res/reality.txt","r+");
    fscanf(Pacy, "%d%d\n", &outMap->height , &outMap->width);
    char c;

    outGame->cheeses=0;
    outGame->cherries=0;
    outGame->pineapples=0;
   char temp1;


    for(j=0;j<outMap->height;j++){
         for(i=0;i<outMap->width;i++){
            fscanf(Pacy,"%c", &temp1);
                 outMap->cells[i][j]=temp1;


        if(outMap->cells[i][j]==CELL_CHEESE)
            outGame->cheeses++;
        else if(outMap->cells[i][j]==CELL_PINEAPPLE)
            outGame->pineapples++;
        else if(outMap->cells[i][j]==CELL_CHERRY)
            outGame->cherries++;


    }
        fscanf(Pacy,"%c",&c);
    }

    fscanf(Pacy,"%d\n", &outGame->score);
    fscanf(Pacy,"%*s%d %d (%d,%d) (%lf,%lf)",&outPacman->dir,&outPacman->health, &outPacman->startY , &outPacman->startX , &outPacman->y, &outPacman->x);


    outPacman->speed=PACMAN_DEFAULT_SPEED;
    outGame->ghosts=4;

    for(k=0;k<4;k++) {
        outGhosts[k].blueCounterDown=0;
        outGhosts[k].type=k;
        outGhosts[k].speed=GHOST_DEFAULT_SPEED;

        fscanf(Pacy, "%*s %d %d ", &outGhosts[k].dir, &temp);
        if (temp == 0) {
            outGhosts[k].blue=1;
            fscanf(Pacy, "%d ", &outGhosts[k].blueCounterDown);
            outGhosts[k].blueCounterDown*=CYCLES_PER_SEC;
        }
        fscanf(Pacy, "(%d,%d) (%lf,%lf)", &outGhosts[k].startY, &outGhosts[k].startX, &outGhosts[k].y, &outGhosts[k].x);

    }




}


void checkEatables(Map* map, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    int i;
    if(map->cells[(int) round(outPacman->x)][(int)round((outPacman->y))]==CELL_CHEESE){
        outGame->score+=CHEESE_SCORE;
        map->cells[(int)round(outPacman->x)][(int)round((outPacman->y))]=CELL_EMPTY;
    }
    if(map->cells[(int)round(outPacman->x)][(int)round((outPacman->y))]==CELL_CHERRY){
        outGame->score+=CHERRY_SCORE;
        map->cells[(int)round(outPacman->x)][(int)round((outPacman->y))]=CELL_EMPTY;
    }
    if(map->cells[(int)round(outPacman->x)][(int)round((outPacman->y))]==CELL_PINEAPPLE) {
        outGame->score += PINEAPPLE_SCORE;
        map->cells[(int)round(outPacman->x)][(int)round((outPacman->y))] = CELL_EMPTY;
        for (i=0; i<4 ; i++){
            outGhosts[i].blue=1;
            outGhosts->blueCounterDown=BLUE_DURATION;

        }
    }

}

void checkGhostCollision(Pacman* outPacman, Ghost* outGhost) {
    if(abs(outPacman->x-outGhost->x)<0.5 && abs(outPacman->y-outGhost->y)<0.5 && outGhost->blue){
        outGhost->x=outGhost->startX;
        outGhost->y=outGhost->startY;
        outGhost->blue=0;
    }
    else if(abs(outPacman->x-outGhost->x)<0.5 && abs(outPacman->y-outGhost->y)<0.5 && outGhost->blue==0){
        outPacman->x=outPacman->startX;
        outPacman->y=outPacman->startY;
        outPacman->health--;
    }
}

bool isGameFinished(Game* game, Pacman* pacman) {

    if(pacman->health==0 || (game->cheeses==0 && game->pineapples==0)){
        return 1;
    } else
        return 0;

}

void checkGhostState(Ghost* ghost) {

    if(ghost->blue==1) {
        ghost->blueCounterDown -= 1;
    } else if(ghost->blueCounterDown==0) {
            ghost->blue = 0;
        }


}
