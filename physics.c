#include "physics.h"
#include "map.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Direction decideGhost(const Map* map, Ghost* ghost) {

    int x=rand()%4+1;
    if(x==1 &&  (map->cells[(int)ghost->x][(int) (ghost->y-1 +map->height)% map->height])!= CELL_BLOCK ){
        return DIR_UP;
    }

    if(x==2 && (map->cells[(int)(ghost->x+1 +map->width)%map->width][(int) ghost->y])!= CELL_BLOCK){
        return DIR_RIGHT;
    }

    if(x==3 && (map->cells[(int)ghost->x][(int) (ghost->y+1 +map->height)%map->height])!= CELL_BLOCK){
        return DIR_DOWN;
    }
    if(x==4 && (map->cells[(int)(ghost->x-1+map->width)%map->width][(int) ghost->y])!= CELL_BLOCK){
        return DIR_LEFT;
    }

    return DIR_NONE;
    }

Direction decidePacman(const Map* map, Pacman* pacman, Action action) {

        if (action == ACTION_UP && map->cells[(int) round(pacman->x)][(int) (round(pacman->y)-1 +map->height)%map->height] != CELL_BLOCK) {
            return DIR_UP;
        }
        if (action == ACTION_RIGHT && map->cells[(int) (round(pacman->x)+1+map->width)%map->width][(int) round(pacman->y)] != CELL_BLOCK) {
            return DIR_RIGHT;
        }
        if (action == ACTION_DOWN && map->cells[(int) round(pacman->x)][(int) (round(pacman->y)+1 +map->height)%map->height] != CELL_BLOCK) {
            return DIR_DOWN;
        }
        if (action == ACTION_LEFT && map->cells[(int) (round(pacman->x)-1+map->width)%map->width][(int) round(pacman->y)] != CELL_BLOCK) {
            return DIR_LEFT;
        }



    if (pacman->dir== DIR_UP && map->cells[(int) round(pacman->x)][(int) (round(pacman->y)-1 +map->height)%map->height] != CELL_BLOCK) {
        return DIR_UP;
    }
    if (pacman->dir == DIR_RIGHT && map->cells[(int) (round(pacman->x)+1+map->width)%map->width][(int) round(pacman->y)] != CELL_BLOCK) {
        return DIR_RIGHT;
    }
    if (pacman->dir == DIR_DOWN && map->cells[(int) round(pacman->x)][(int) (round(pacman->y)+1 +map->height)%map->height] != CELL_BLOCK) {
        return DIR_DOWN;
    }
    if (pacman->dir == DIR_LEFT && map->cells[(int) (round(pacman->x)-1+map->width)%map->width][(int) round(pacman->y)] != CELL_BLOCK) {
        return DIR_LEFT;
    }





    return DIR_NONE;
}




