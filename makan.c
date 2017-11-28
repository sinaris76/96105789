#include <stdio.h>

struct Ghost{
    int jahat;
    char name[20];
    int halat;
    int rtime;
    int XGstart;
    int YGstart;
    int XGnow;
    int YGnow;
};
void Makan( int m , int n , char array[100][100] , int Jahat , int *Xpnow,int *Ypnow,int Xpstart,int Ypstart, struct Ghost rooh[4]);
void Score(char array[100][100] , int score  , int Xpnow , int Ypnow,struct Ghost rooh[4]);
void Win(int n , struct Ghost rooh[4], int m , int heart, char array[100][100], int Xpnow, int Ypnow);

int main(){
    struct Ghost rooh[4];
    int n , m , i , j , second , Hsecond , score;
    int Jahat , Xpstart , Ypstart , Xpnow , Ypnow , heart;
    scanf("%d%d\n", &n , &m);
    char array[100][100];
    for(i=0 ; i<n ; i++){
        for(j=0 ; j<m+1 ; j++){
            scanf("%c", &array[i][j]);
        }

    }


    scanf("%02d:%02d %d", &second , &Hsecond , &score);
    scanf("%*s%d %d (%d,%d) (%d,%d)", &Jahat , &heart , &Xpstart , &Ypstart , &Xpnow , &Ypnow);

    int counter;
    for(counter=0;counter<4 ; counter++){
        scanf("%*s%d %d", &rooh[counter].jahat , &rooh[counter].halat);
        if(rooh[counter].halat==0)
        scanf(" %d", &rooh[counter].rtime);
        scanf(" (%d,%d) (%d,%d)", &rooh[counter].XGstart , &rooh[counter].YGstart , &rooh[counter].XGnow , &rooh[counter].YGnow);
    }
    Makan(m , n , array , Jahat , &Xpnow , &Ypnow , Xpstart,Ypstart , rooh);
    Score(array,score,Xpnow,Ypnow,rooh);
    Win(n,rooh,m,heart,array,Xpnow,Ypnow);
}

void Makan( int m , int n , char array[100][100] , int Jahat , int *Xpnow,int *Ypnow,int Xpstart,int Ypstart, struct Ghost rooh[4]){
    int counter;

    if(Jahat==1){
        if(*Xpnow==0 && array[n-1][*Ypnow]!='#'){
            *Xpnow=n-1;
        }
        else if(*Xpnow>0 && array[*Xpnow-1][*Ypnow]!='#')

        *Xpnow-=1;

    }
    else if(Jahat==2){
        if(*Ypnow==m-1 && array[*Xpnow][0]!='#'){
            *Ypnow=0;
        }
        else if(*Ypnow<m-1 && array[*Xpnow][*Ypnow+1]!='#')
        *Ypnow+=1;
    }
    else if(Jahat==3){
        if(*Xpnow==n-1 && array[0][*Ypnow]!='#'){
            *Xpnow=0;
        }
        else if(*Xpnow<n-1 && array[*Xpnow+1][*Ypnow]!='#')
        *Xpnow+=1;
    }
    else if(Jahat==4) {
        if (*Ypnow == 0 && array[*Xpnow][m - 1] != '#') {
            *Ypnow =m - 1;
        } else if (*Ypnow > 0 && array[*Xpnow][*Ypnow - 1] != '#')
            *Ypnow -= 1;

    }
        for(counter=0;counter<4;counter++){
            if(array[*Xpnow][*Ypnow]=='O'){
                break;
            }

            else if(rooh[counter].halat==1 && *Ypnow==rooh[counter].YGnow && *Xpnow==rooh[counter].XGnow){

                //*Xpnow=Xpstart;
                //*Ypnow=Ypstart;
                printf("(%d,%d)\n", Xpstart, Ypstart);
                return;
                }
        }



    printf("(%d,%d)\n", *Xpnow, *Ypnow);

}
