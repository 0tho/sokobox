/*
  Um jogo de sokobox usando a linguagem C e textos para visualizar
  
  Marcelo Lopes Lotufo
  
  secao1: 11/05/2011
  secao2: 13/05/2011
  
  -------- remake --------
  
  secao1: 13/05/2011 16:00 até 18:00 
  secao2: continuar a partir do movimento do personagem corrigir bug do "-" sumir  

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int x,y;	
}ponto;

//No main sera rodado o jogo inteiro
int main(int argc, char *argv[])
{    
	//declaração de variaveis que serão usados durante o jogo
		//variaveis de controle do menu
		int estado = 0;
		int comando = 0;
		int selecionado = 0;
		int telaMudou = 1; // variavel logica
		
		
		//fase guarda a fase atual do jogo
		int totalFases = 3;
		int fase = 0;
		int fim = 0;
				
		//vetor2 da direção do movimento do personagem
		ponto dir;
		dir.x = 0;
		dir.y = 0;
		
		//pos do personagem principal
		ponto pos;
		pos.x = 0;
		pos.y = 0;
		
		//alvos da fase
		ponto alvos[15];
		int alvosUsados = 0;
		
		//achou pos é uma variavel pra quando mudar a fase do jogo achar a posição do char
		int achouPos = 0; // variavel logica
		
		//variaveis uteis
		int i, j;
		
	//declaração dos mapas
		
		char mapas[3][20][50] = {
									{
										" ________________________________________________ ",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|              XXXXXXX                           |",
										"|              X0 + -X                           |",
										"|              XXXXXXX                           |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|        Aperte esc para voltar ao menu          |",
										"|________________________________________________|"
									},
									
									{
										" ________________________________________________ ",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                       XXXXX                    |",
										"|                       X   X                    |",
										"|                       X X X                    |",
										"|                XXXXXXXX X X                    |",
										"|                X0        +X                    |",
										"|                XXX X+XXXX X                    |",
										"|                  X   X  X X                    |",
										"|                  XXXXX  X-X                    |",
										"|                         X-X                    |",
										"|                         XXX                    |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|        Aperte esc para voltar ao menu          |",
										"|________________________________________________|"
									},
									
									{
										" ________________________________________________ ",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                                                |",
										"|                   XXXXXXXX                     |",
										"|                   X   X  X                     |",
										"|                   X X X+-X                     |",
										"|                   X    +-X                     |",
										"|                   X X X+-X                     |",
										"|                   X   X  X                     |",
										"|                   XXXXX0 X                     |",
										"|                       XXXX                     |",
										"|                                                |",
										"|                                                |",										
										"|                                                |",
										"|        Aperte esc para voltar ao menu          |",
										"|________________________________________________|"
									}
								};
		
		
	//declaração de telas
		char telaRenderizada[20][50];
		
		char menuPrincipal[3][20][50] = {
											{
												" ________________________________________________ ",
												"|                                                |",
												"|           XXXXX    XXXXXXX   X    X            |",
												"|           X    X   X     X    X  X             |",
												"|           X   X    X     X     XX              |",
												"|           X XXX    X     X     XX              |",
												"|           X    X   X     X    X  X             |",
												"|           XXXXX    XXXXXXX   X    X            |",
												"|_______________________________________________ |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|        -Jogar-    Creditos      Sair           |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|________________________________________________|"
											},
											
											{
												" ________________________________________________ ",
												"|                                                |",
												"|           XXXXX    XXXXXXX   X    X            |",
												"|           X    X   X     X    X  X             |",
												"|           X   X    X     X     XX              |",
												"|           X XXX    X     X     XX              |",
												"|           X    X   X     X    X  X             |",
												"|           XXXXX    XXXXXXX   X    X            |",
												"|_______________________________________________ |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|         Jogar    -Creditos-     Sair           |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|________________________________________________|"
											},
											
											{
												" ________________________________________________ ",
												"|                                                |",
												"|           XXXXX    XXXXXXX   X    X            |",
												"|           X    X   X     X    X  X             |",
												"|           X   X    X     X     XX              |",
												"|           X XXX    X     X     XX              |",
												"|           X    X   X     X    X  X             |",
												"|           XXXXX    XXXXXXX   X    X            |",
												"|_______________________________________________ |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|         Jogar     Creditos     -Sair-          |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|                                                |",
												"|________________________________________________|"
											}
										};
		
		char creditos[20][50] = {
									" ________________________________________________ ",
									"|                                                |",
									"|           XXXXX    XXXXXXX   X    X            |",
									"|           X    X   X     X    X  X             |",
									"|           X   X    X     X     XX              |",
									"|           X XXX    X     X     XX              |",
									"|           X    X   X     X    X  X             |",
									"|           XXXXX    XXXXXXX   X    X            |",
									"|_______________________________________________ |",
									"|                                                |",
									"|                  -Creditos-                    |",
									"|                                                |",
									"|                                                |",
									"|       Jogo criado como estudo em C por         |",
									"|                                                |",
									"|                     MLL                        |",
									"|                                                |",
									"|                                                |",
									"|        Aperte esc para voltar ao menu          |",
									"|________________________________________________|"
								};
								
		char fimDeJogo[20][50] = {
									" ________________________________________________ ",
									"|                                                |",
									"|           XXXXX    XXXXXXX   X    X            |",
									"|           X    X   X     X    X  X             |",
									"|           X   X    X     X     XX              |",
									"|           X XXX    X     X     XX              |",
									"|           X    X   X     X    X  X             |",
									"|           XXXXX    XXXXXXX   X    X            |",
									"|_______________________________________________ |",
									"|                                                |",
									"|                  !Parabens!                    |",
									"|                     voce                       |",
									"|                    ganhou                      |",
									"|                                                |",
									"|                                                |",
									"|                     MLL                        |",
									"|                                                |",
									"|                                                |",
									"|        Aperte esc para voltar ao menu          |",
									"|________________________________________________|"
								};
		for(i=0;i<20;i++){
              for(j=0;j<50;j++){
                   telaRenderizada[i][j] = menuPrincipal[selecionado][i][j];            
              }
        }									
		
	//loop do jogo sendo que o jogo só termina quando sair do jogo pelo menu principal
		while(estado != -1) {
        //Limpar tela e desenhar tela do jogo caso a tela tenha mudado			
		if(telaMudou) {
			system("cls");
			for(i=0; i<20; i++){
				for(j=0; j<50; j++){
					printf("%c", telaRenderizada[i][j]); 
				}
				printf("\n");
			}
			telaMudou=0;
		}                    
		//se o jogo estiver no menu principal
			if(estado == 0) {
			//checar tecla apertada
				comando = getche();
				//printf("%d : %c", comando, comando);
				//se for a ou esquerda
					if(comando == 75 || comando == 'a'){ 
					//mova seleção para esquerda
						if(selecionado > 0){
							selecionado -=1;
							telaMudou =1;
							for(i=0;i<20;i++){
								for(j=0;j<50;j++){
									telaRenderizada[i][j] = menuPrincipal[selecionado][i][j];
								}
							}	
						}
					}
				//se for d ou direira
					if(comando == 77 || comando == 'd'){ 
					//mova seleção para direita
						if(selecionado < 3){
							selecionado +=1;
							telaMudou =1;
							for(i=0;i<20;i++){
								for(j=0;j<50;j++){
									telaRenderizada[i][j] = menuPrincipal[selecionado][i][j];
								}
							}	
						}
					}
				//se for enter
					//selecione atual
					if(comando == 13){                               
					           
						//se for jogar
						if(selecionado == 0){
                            //tela que sera desenhada copia os dados do mapa atual
							for(i=0;i<20;i++){
                                 for(j=0;j<50;j++){
                                      telaRenderizada[i][j] = mapas[fase][i][j];            
                                 }
                                              
                            }           
							//estado = 1 (jogo rodando)
														
							for(i=0;i<20;i++){
                                 for(j=0;j<50;j++){
                                      if(telaRenderizada[i][j] == '0'){
                                          pos.x = j;
                                          pos.y = i;
                                          achouPos = 1;                     
                                      }
                                      if(telaRenderizada[i][j] == '-'){
                                          alvos[alvosUsados].x = j;
                                          alvos[alvosUsados].y = i;
                                          alvosUsados += 1;                     
                                      }               
                                 }
                                              
                            }
                            estado = 1;
                            telaMudou = 1;
							//
														
						}
						//se for créditos
						if(selecionado == 1){
							//estado = 2 (creditos)
							estado = 2;
							telaMudou = 1;
							for(i=0;i<20;i++){
                                  for(j=0;j<50;j++){
                                     telaRenderizada[i][j] = creditos[i][j];  
                                  }
                            }	
						}
						//se for sair						
						if(selecionado == 2){
							//estado = -1 (sair do jogo)
							estado = -1;							
						}					   
					}
			}else if(estado == 2) {
		//se o jogo estiver nos créditos			
			//checar tecla apertada
				comando = getche();
				//se for esc
				if(comando == 27){
					//estado = 0 (volta pro menu)
					estado = 0;
					telaMudou =1;
					for(i=0;i<20;i++){
						for(j=0;j<50;j++){
							telaRenderizada[i][j] = menuPrincipal[selecionado][i][j];
						}
					}	
                }				
				
			}else if(estado == 1) {			
		//se o jogo estiver rodando			
			//checar tecla apertada
				comando = getche();
				
				//se for esc
					if(comando == 27){
						//estado = 0 (volta pro menu)
						estado = 0;
						telaMudou =1;
						for(i=0;i<20;i++){
							for(j=0;j<50;j++){
								telaRenderizada[i][j] = menuPrincipal[selecionado][i][j];
							}
						}	
					}					
				//se for w ou cima
					if(comando == 72 || comando == 'w'){ 
					//dir = (0,-1)
						dir.x = 0;
						dir.y = -1;
					}
				
				//se for s ou baixo
					if(comando == 80 || comando == 's'){ 
					//dir = (0,1)
						dir.x = 0;
						dir.y = 1;
					}
				
				//se for d ou direita
					if(comando == 77 || comando == 'd'){ 
					//dir = (1,0)
						dir.x = 1;
						dir.y = 0;
					}
				
				//se for a ou esquerda
					if(comando == 75 || comando == 'a'){
					//dir = (-1, 0)
						dir.x = -1;
						dir.y = 0;
					}
					//printf("\n%d,%d dir", dir.x, dir.y);
					//printf("\n%d,%d pos", pos.x, pos.y);
					
				//se dir.x != 0 ou dir.y !=0
					if(dir.x !=0 || dir.y !=0){
                            // printf("era diferente");
					//se posição do personagem + dir = caixa e pos + dir*2 = vazio
						if(telaRenderizada[pos.y+dir.y][pos.x+dir.x] == '+' && (telaRenderizada[pos.y+dir.y*2][pos.x+dir.x*2] == '-' || telaRenderizada[pos.y+dir.y*2][pos.x+dir.x*2] == ' ')){
						//mova caixa e personagem
					//	printf("tinha caixa");
						    telaRenderizada[pos.y+dir.y*2][pos.x+dir.x*2] = telaRenderizada[pos.y+dir.y][pos.x+dir.x];  
							telaRenderizada[pos.y+dir.y][pos.x+dir.x] = telaRenderizada[pos.y][pos.x];
							if(mapas[fase][pos.y][pos.x] == '-'){
                                  telaRenderizada[pos.y][pos.x] = mapas[fase][pos.y][pos.x];
                            }else{
                                  telaRenderizada[pos.y][pos.x] = ' ';
                            }
							pos.x += dir.x;
							pos.y += dir.y;
                            telaMudou =1;							
						//senao se pos + dir != parede
						}else if(telaRenderizada[pos.y+dir.y][pos.x+dir.x] == ' ' || telaRenderizada[pos.y+dir.y][pos.x+dir.x] == '-'){
						//mova personagem
                        //printf("tinha nada");						      
							telaRenderizada[pos.y+dir.y][pos.x+dir.x] = telaRenderizada[pos.y][pos.x];
							if(mapas[fase][pos.y][pos.x] == '-'){
                                  telaRenderizada[pos.y][pos.x] = mapas[fase][pos.y][pos.x];
                            }else{
                                  telaRenderizada[pos.y][pos.x] = ' ';
                            }							
							pos.x += dir.x;
							pos.y += dir.y;
							telaMudou = 1;
						}	
                        //printf("termino");				
					}				
				//dir = (0,0) {acho que é desnecessario}
				dir.x = 0;
				dir.y = 0;				
					
				//cheque fim de fase
				for(i=0;i<alvosUsados;i++){
                    if(telaRenderizada[alvos[i].y][alvos[i].x] == '+') {
                       fim += 1;                                        
                    }                  
                }
                //printf("fim: %d alvos: %d", fim, alvosUsados);
                if(fim == alvosUsados){
                    alvosUsados = 0;
                    fase+=1;
					if(fase < totalFases){
						for(i=0;i<20;i++){
							for(j=0;j<50;j++){
								telaRenderizada[i][j] = mapas[fase][i][j];            
							}                                              
						}           
							//estado = 1 (jogo rodando)													
						for(i=0;i<20;i++){
							for(j=0;j<50;j++){
								if(telaRenderizada[i][j] == '0'){
									pos.x = j;
									pos.y = i;
									achouPos = 1;                     
								}
								if(telaRenderizada[i][j] == '-'){
									alvos[alvosUsados].x = j;
									alvos[alvosUsados].y = i;
									alvosUsados += 1;                     
								}               
							}									  
						}
					}else{
						for(i=0;i<20;i++){
							for(j=0;j<50;j++){
								telaRenderizada[i][j] = fimDeJogo[i][j];            
							}                                              
						}
						estado = 3;
						fase = 0;
                        fim = 0;						
					}                      
                }else{
                   fim=0;      
                }
                //fim da checagem				
			}else if(estado == 3) {		
		//se ja tiverem acabado as fase			
			//checar tecla apertada
				comando = getche();
				//se for esc
				if(comando == 27){
					//estado = 0 (volta pro menu)
					estado = 0;
					telaMudou = 1;
					selecionado = 1;
					for(i=0;i<20;i++){
						for(j=0;j<50;j++){
							telaRenderizada[i][j] = menuPrincipal[selecionado][i][j];
						}
					}	
                }				
				
			}
		}	
		//fim do loop principal
	return 0;
}


