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