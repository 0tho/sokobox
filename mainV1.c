/*
  Um jogo de sokobox usando a linguagem C e textos para visualizar
  
  Marcelo Lopes Lotufo
  
  secao1: 11/05/2011
  

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*typedef struct map {
        int mapSize, numTargets;
                
        char data[mapSize][mapSize];
        int targets[numTargets];
        int charPos[2];    
        
}*/
int tam =20;
//declaraçao dos tile do mapa
    char parede = 'X';
    char persona = '0';
    char objeto = '+';
    char alvo = '-';
    char vazio = ' ' ;
    //Mapa1
    char mapa[20][20];
  
    
    int mapaAtual =1;
    int tamanho1 = 30;    
    int targets1[2][2];
    int objs1[2][2];
    int pos[2];
    


//No main sera rodado o jogo inteiro
int main(int argc, char *argv[])
{    
    
    char comando; 
    int jogo;
    //enquanto jogo nao tiver acabado continue
    
    //se o jogo não tiver começado, inicie{exiba o mapa} {inicie pos do char}
    
    //senao cheque movimento pelas teclas(w,a,s,d){cheque colisão){mova} ... cheque fim de jogo
    
    pos[0] = 5;
    pos[1] = 3;
    targets1[0][0] = 3;
    targets1[0][1] = 3;
    targets1[1][0] = 10;
    targets1[1][1] = 15;
    objs1[0][0] = 10;
    objs1[0][1] = 3;
    objs1[1][0] = 17;
    objs1[1][1] = 2;
    
    initMap();
    drawMap();
    
    while(jogo != 0){
        comando = getche(); 
        //printf("/n Comando=: %d  \n", comando);        
        if(comando == 77 || comando == 'd'){ 
              if(mapa[pos[0]][pos[1]+1] != parede){            
              pos[1] +=1;
              comando = ' ';               
              }               
        }
        if(comando == 75 || comando == 'a'){ 
              if(mapa[pos[0]][pos[1]-1] != parede){             
              pos[1] -=1;
              comando = ' ';  
              }              
        } 
        if(comando == 72 || comando == 'w'){ 
              if(mapa[pos[0]+1][pos[1]] != parede){            
              pos[0] -=1;
              comando = ' '; 
              }               
        } 
        if(comando == 80 || comando == 's'){ 
             if(mapa[pos[0]-1][pos[1]] != parede){            
              pos[0] +=1; 
              comando = ' '; 
              }              
        }
         
        
        system("cls");
        initMap();
        drawMap();            
    }
    
  
  printf("\n");
  system("PAUSE");	
  return 0;
}

int initMap() {
     //Desenha o mapa
     int i,j;
     for(i=0; i<tam; i++){
              for(j=0;j<tam;j++){
                    if(i==0 || i==tam-1 || j==0|| j==tam-1){
                            mapa[i][j] = parede; 
                    } else {
                           mapa[i][j] = vazio;
                    }                        
              }         
     }
     
     mapa[targets1[0][0]][targets1[0][1]] = alvo;
     mapa[targets1[1][0]][targets1[1][1]] = alvo; 
     
     mapa[objs1[0][0]][objs1[0][1]] = objeto;
     mapa[objs1[1][0]][objs1[1][1]] = objeto;  
     
     mapa[pos[0]][pos[1]] = persona;
}
int drawMap() {
     //Desenha o mapa
     int i,j;
     for(i=0; i<tam; i++){
              for(j=0;j<tam;j++){
                   printf("%c", mapa[i][j]);                  
              } 
              printf("\n");        
     }     
}
void iniciar() {
     //Define todas as variaveis com os valores dela no começo do mapa dependendo do mapa     
}
