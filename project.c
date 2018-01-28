#include "physics.h"
#include <math.h>
#include "map.h"
#include "game.h"
#include<stdlib.h>
#include <time.h>
#include <stdio.h>
int Q[10000];
int head , tail ;

int parent[10000];
int distance[10000];

int dx[4] = {+0, +1, +0, -1};
int dy[4] = {+1, +0, -1, +0};



Direction bfs(int home, int dest ,const Map*map , Ghost*ghost) {
    resetQueue();

    push_back(home, 0);

    while(head < tail){

        int v = Q[head ++];

        int x = v % map->width;
        int y = v / map->width;

        for (int j = 0; j < 4; ++j) {

            int neighbouring_x = (x + dx[j] + map->width) % map->width;
            int neighbouring_y = (y + dy[j] + map->height) % map->height;

            int neighbouring_vertex = id(neighbouring_x, neighbouring_y , map);


            if(map->cells[neighbouring_x][neighbouring_y] != CELL_BLOCK && distance[neighbouring_vertex] == -1) {
                parent[neighbouring_vertex] = v;
                push_back(neighbouring_vertex, distance[v] + 1);

            }
        }
    }
    return direct(parent, home, dest, ghost, map);
}

void resetQueue() {
    head = 0;
    tail = 0;
    for(int i = 0 ; i < 10000 ; i++)
        distance[i] = -1;
}

void push_back(int node, int dis) {
    distance[node] = dis;
    Q[tail++] = node;
}

int id(int x, int y, const Map*map){
    x = ((x % map->width) + map->width ) % map->width;
    y = ((y % map->height) + map->height ) % map->height;
    return y*map->width + x;
}
Direction direct(int parent[10000] , int home , int dest , Ghost* ghost , const Map*map){
    while(parent[dest] != home)
        dest = parent[dest];

    if(dest == home)
        return DIR_UP;

    int x = dest % map->width;
    int y = dest / map->width;

    if(((x - 1 + map->width) % map->width) == (int)ghost->x && y == (int)ghost->y){
        return DIR_RIGHT;
    }
    else if(((x + 1 + map->width) % map->width) == (int)ghost->x && y == (int)ghost->y){
        return DIR_LEFT;
    }
    else if(x == (int)ghost->x && (y - 1 + map->height) % map->height == (int)ghost->y){
        return DIR_DOWN;
    }
    else if(x == (int)ghost->x && (y + 1 + map->height) % map->height == (int)ghost->y){
        return DIR_UP;
    }
}
Direction randghost(const Map *map, Ghost *ghost, Pacman *pacman) {
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
Direction decideGhost(const Map *map, Ghost *ghost, Pacman *pacman, Ghost *blinky){
    int x=(int)pacman->x;
    int y=(int)pacman->y;
    if(ghost->type==BLINKY){//Blinky
        int xb=(int)ghost->x;
        int yb=(int)ghost->y;
        int destination=id(x,y,map);
        int startb=id(xb,yb,map);
        return bfs(startb,destination,map,ghost);
    }
    if(ghost->type==PINKY){//Pinky
        int i;
        int xp=(int)ghost->x;
        int yp=(int)ghost->y;
        int startp=id(xp,yp,map);
        for(i=0;i<4;i++){
            if(pacman->dir==DIR_UP){
                if(map->cells[(int)pacman->x][(((int)pacman->y-i)+map->height)%map->height]==CELL_BLOCK){
                    int destination=id(x,(((int)pacman->y-i+1)+map->height)%map->height,map);
                    return bfs(startp,destination,map,ghost);
                }
                else if(i==4){
                    int destination=id(x,((int)pacman->y-4+map->height)%map->height,map);
                    return bfs(startp,destination,map,ghost);
                }
            }
            else if(pacman->dir==DIR_DOWN){
                if(map->cells[(int)pacman->x][(((int)pacman->y+i)+map->height)%map->height]==CELL_BLOCK){
                    int destination=id(x,(((int)pacman->y+i-1)+map->height)%map->height,map);
                    return bfs(startp,destination,map,ghost);
                }
                else if(i==4){
                    int destination=id(x,(((int)pacman->y+4)+map->height)%map->height,map);
                    return bfs(startp,destination,map,ghost);
                }
            }
            else if(pacman->dir==DIR_RIGHT){
                if(map->cells[(((int)pacman->x+i)+map->width)%map->width][(int)pacman->y]==CELL_BLOCK){
                    int destination=id((((int)pacman->x+i-1)+map->width)%map->width,y,map);
                    return bfs(startp,destination,map,ghost);
                }
                else if(i==4){
                    int destination=id((((int)pacman->x+4)+map->width)%map->width,y,map);
                    return bfs(startp,destination,map,ghost);
                }
            }
            else if(pacman->dir==DIR_LEFT){
                if(map->cells[(((int)pacman->x-i)+map->width)%map->width][(int)pacman->y]==CELL_BLOCK){
                    int destination=id((((int)pacman->x-i+1)+map->width)%map->width,y,map);
                    return bfs(startp,destination,map,ghost);
                }
                else if(i==4){
                    int destination=id((((int)pacman->x-4)+map->width)%map->width,y,map);
                    return bfs(startp,destination,map,ghost);
                }
            }
        }
    }
    if(ghost->type==INKY){//inky
        int hx=(int)ghost->x;
        int hy=(int)ghost->y;
        int starti=id(hx,hy,map);
        if(pacman->dir==DIR_UP){
            int xi=(2*((int)pacman->x)-(int)blinky->x)%map->width;
            int yi=(2*((int)pacman->y-2)-(int)blinky->y)%map->height;
            if(map->cells[xi][yi]!=CELL_BLOCK){
                int destination=id(xi,yi,map);
                return bfs(starti,destination,map,ghost);
            }
            else{
                return randghost(map,ghost,pacman);
            }
        }
        else if(pacman->dir==DIR_DOWN){
            int xi=(2*((int)pacman->x)-(int)blinky->x)%map->width;
            int yi=(2*((int)pacman->y+2)-(int)blinky->y)%map->height;
            if(map->cells[xi][yi]!=CELL_BLOCK){
                int destination=id(xi,yi,map);
                return bfs(starti,destination,map,ghost);
            }
            else{
                return randghost(map,ghost,pacman);
            }
        }
        else if(pacman->dir==DIR_RIGHT){
            int xi=(2*((int)pacman->x+2)-(int)blinky->x)%map->width;
            int yi=(2*((int)pacman->y)-(int)blinky->y)%map->height;
            if(map->cells[xi][yi]!=CELL_BLOCK){
                int destination=id(xi,yi,map);
                return bfs(starti,destination,map,ghost);
            }
            else{
                return randghost(map,ghost,pacman);
            }
        }
        else if(pacman->dir==DIR_LEFT){
            int xi=(2*((int)pacman->x-2)-(int)blinky->x)%map->width;
            int yi=(2*((int)pacman->y)-(int)blinky->y)%map->height;
            if(map->cells[xi][yi]!=CELL_BLOCK){
                int destination=id(xi,yi,map);
                return bfs(starti,destination,map,ghost);
            }
            else{
                return randghost(map,ghost,pacman);
            }
        }
    }
    if(ghost->type==CLYDE) {//clyde
        int xc = (int) ghost->x;
        int yc = (int) ghost->y;
        int startc = id(xc, yc, map);
        if (fabs(ghost->x - pacman->x) + fabs(ghost->y - pacman->y) > 8) {
            int destination = id(x, y, map);
            return bfs(startc, destination, map, ghost);
        } else {
            if (map->cells[0][map->height - 1] != CELL_BLOCK) {
                int destination = id(0, map->height - 1, map);
                return bfs(startc, destination, map, ghost);
            } else {
                return randghost(map, ghost, pacman);
            }
        }
    }
}
Direction decidePacman(const Map* Map, Pacman* pacman, Action action) {
    if (action == ACTION_UP && Map->cells[(int) round(pacman->x)][(int) (round(pacman->y)-1 +Map->height)%Map->height] != CELL_BLOCK) {
        return DIR_UP;
    }
    if (action == ACTION_RIGHT && Map->cells[(int) (round(pacman->x)+1+Map->width)%Map->width][(int) round(pacman->y)] != CELL_BLOCK) {
        return DIR_RIGHT;
    }
    if (action == ACTION_DOWN && Map->cells[(int) round(pacman->x)][(int) (round(pacman->y)+1 +Map->height)%Map->height] != CELL_BLOCK) {
        return DIR_DOWN;
    }
    if (action == ACTION_LEFT && Map->cells[(int) (round(pacman->x)-1+Map->width)%Map->width][(int) round(pacman->y)] != CELL_BLOCK) {
        return DIR_LEFT;
    }



    if (pacman->dir== DIR_UP && Map->cells[(int) round(pacman->x)][(int) (round(pacman->y)-1 +Map->height)%Map->height] != CELL_BLOCK) {
        return DIR_UP;
    }
    if (pacman->dir == DIR_RIGHT && Map->cells[(int) (round(pacman->x)+1+Map->width)%Map->width][(int) round(pacman->y)] != CELL_BLOCK) {
        return DIR_RIGHT;
    }
    if (pacman->dir == DIR_DOWN && Map->cells[(int) round(pacman->x)][(int) (round(pacman->y)+1 +Map->height)%Map->height] != CELL_BLOCK) {
        return DIR_DOWN;
    }
    if (pacman->dir == DIR_LEFT && Map->cells[(int) (round(pacman->x)-1+Map->width)%Map->width][(int) round(pacman->y)] != CELL_BLOCK) {
        return DIR_LEFT;
    }

    return DIR_NONE;

}