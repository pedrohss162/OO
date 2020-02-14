#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "gea.h"

#define VERDE 		printf("\033[1;32m");
#define AMARELO 	printf("\033[1;33m");
#define AZUL 		printf("\033[1;34m");
#define VERMELHO	printf("\033[1;31m");

#define TITULO 		printf("██████████████████████████████████████████████████\n███     ██████████████████████████████████████████\n███ ████ ███████████████████████   ███████████████\n███ ████ ██████████████████████ ███ ███ ██████████\n███ ████ ███ ██ ██ █ ████  ████     ██ █ ██ █ ████\n███ ████ ███ ██ ██  █ ██ ██ ███ █████ ███ █  █ ███\n███     █████  ███ ██ ███  █ ███    ██ █ ██ ██ ███\n████████████████████████████ ██████████ ██████████\n█████████████████████████   ██████████████████████\n██████████████████████████████████████████████████\n███                                            ███\n"); 

#define TAM 		100
#define PAREDE 		1
#define VAZIO		2
#define ENTRADA		3
#define SAIDA		4
#define CHAVE		5
#define INIMIGO		6


#define PEDRA		1
#define PAPEL		2
#define TESOURA		3


int main(){

	srand(time(NULL));

	int passo, op, sair, col = 15, lin = 15, dif = 1, andar = 0, mapa[50][TAM][TAM], NovaDungeon, final, total_andar, px, py, flagi, flagf, ix, iy, fx, fy, vx, vy,fimapa, vp, vi, ap, ai, dp, di;
	int ataque, ini, bost, bosti, pontos, Rp[10], pxn;
	char resp, jogada, Rn[10][100], player[100], aux[100];
	float esp;
	for(int i = 0; i<10; i++){
		for(int j = 0; j < 3; j++){
			Rn[i][j] = i + 65;
		}
		Rp[i] = 1000 - i*10;
	}

	while(sair!=1){
		sair = 0;
		system("clear");
		AMARELO
		TITULO
		printf("███ 1. Jogar                                   ███\n");
		printf("███ 2. Configurações                           ███\n");
		printf("███ 3. Ranking                                 ███\n");
		printf("███ 0. Sair                                    ███\n");
		printf("███                                            ███\n");
		printf("██████████████████████████████████████████████████\n");
		printf("███ Tamanho mapa: %ix%i\t\t", lin, col);
		if(lin==100&&col==100){printf("       ███\n");}
		else if(lin==100||col==100){printf("       ███\n");}
		else{printf("\t       ███\n");}
		printf("███ Dificuldade: ");
		if(dif == 1){printf("Fácil   \t\t       ███\n");}
		else if(dif == 2){printf("Médio   \t\t       ███\n");}
		else{printf("Difícil\t\t       ███\n");}
		printf("███                                            ███\n");
		printf("███                                            ███\n");
		printf("██████████████████████████████████████████████████\n");
		printf("    >");
		scanf("%i", &op);
		__fpurge(stdin);

		switch(op){
			case 1:
				final = 0;
				NovaDungeon = 1;
				andar = total_andar = 0;
				jogada = ' ';
				passo = 0;
				pontos = 0;
				if(dif == 1){
					vp = 100;
					ap = 10;
					bost = 1;
					pxn = 50;
				}
				else if(dif==2){
					vp = 50;
					ap = 15;
					bost = 1;
					pxn = 100;
				}
				else if(dif==3){
					vp = 25;
					ap = 15;
					bost = 0;
					pxn = 200;
				}

				system("clear");
				printf("Digite seu nome: ");
				__fpurge(stdin);
				gets(player);
				while(final!=1){
					
					if(andar<15){
						dif = 1;
					}
					else if(andar<30){
						dif = 2;
					}
					else if(andar<50){
						dif = 3;
					}

					if(NovaDungeon==1){
						flagi = flagf = 0;	
						//seta parede
						for (int i = 0; i < lin; ++i){
							for (int j = 0; j < col; ++j){
								mapa[total_andar][i][j] = PAREDE;
							}
						}

						//inicio aleatorio
						while(flagi!=1){
							ix=rand()%lin;
							iy=rand()%col;
							if((ix==0||ix==lin-1)||(iy==0||iy==col-1)){
								if((ix!=iy)||ix+iy!=lin-1){
									flagi=1;
									px = ix;
									py = iy;	
								}
							}
						}
						//fim aleatorio
						while(flagf!=1){
							fx=rand()%lin;
							fy=rand()%col;
							if((fx==0||fx==lin-1)||(fy==0||fy==col-1)){
								if((fx!=fy)||fx+fy!=lin-1){
									flagf = 1;
									if((fx>ix-5&&fx<ix+5)&&iy==fy){
										flagf = 0;
									}
									else if((fy>iy-5&&fy<iy+5)&&ix==fx){
										flagf = 0;
									}
								}
							}
						}
						
						mapa[total_andar][ix][iy] = ENTRADA;
						mapa[total_andar][fx][fy] = SAIDA;
						fimapa = 0;

						do{
							if(ix==0){for(ix++;ix<lin/2; ix++){mapa[total_andar][ix][iy]= VAZIO;}}
							else if(ix==lin-1){for(ix--;ix>lin/2; ix--){mapa[total_andar][ix][iy]= VAZIO;}}
							else if(iy==0){for(iy++;iy<col/2; iy++){mapa[total_andar][ix][iy]= VAZIO;}}
							else if(iy==col-1){for(iy--;iy>col/2; iy--){mapa[total_andar][ix][iy]= VAZIO;}}
							else if(ix<lin/2){for(;ix<lin/2; ix++){mapa[total_andar][ix][iy]= VAZIO;}}
							else if(ix>lin/2){for(;ix>lin/2; ix--){mapa[total_andar][ix][iy]= VAZIO;}}
							else if(iy<col/2){for(;iy<col/2; iy++){mapa[total_andar][ix][iy]= VAZIO;}}
							else if(iy>col/2){for(;iy>col/2; iy--){mapa[total_andar][ix][iy]= VAZIO;}}
							 
							if(fx==0){for(fx++;fx<lin/2; fx++){mapa[total_andar][fx][fy]= VAZIO;}}
							else if(fx==lin-1){for(fx--;fx>lin/2; fx--){mapa[total_andar][fx][fy]= VAZIO;}}
							else if(fy==0){for(fy++;fy<col/2; fy++){mapa[total_andar][fx][fy]= VAZIO;}}
							else if(fy==col-1){for(fy--;fy>col/2; fy--){mapa[total_andar][fx][fy]= VAZIO;}}
							else if(fx<lin/2){for(;fx<lin/2; fx++){mapa[total_andar][fx][fy]= VAZIO;}}
							else if(fx>lin/2){for(;fx>lin/2; fx--){mapa[total_andar][fx][fy]= VAZIO;}}
							else if(fy<col/2){for(;fy<col/2; fy++){mapa[total_andar][fx][fy]= VAZIO;}}
							else if(fy>col/2){for(;fy>col/2; fy--){mapa[total_andar][fx][fy]= VAZIO;}}
							mapa[total_andar][ix][iy]=VAZIO;
							mapa[total_andar][fx][fy]=VAZIO;
							if(ix==fx&&iy==fy){
								if(dif==1)
									esp = 0.95;
								else if(dif==2)
									esp = 0.7;
								else if(dif==3)
									esp = 0.5;
								for (int i = 0; i < (lin*col)*esp; )
								{
									vx = rand()%lin;
									vy = rand()%col;

									if(mapa[total_andar][vx][vy]!= ENTRADA&&mapa[total_andar][vx][vy]!= SAIDA){
										mapa[total_andar][vx][vy] = VAZIO;
										++i;
									}
								}
								for(int i = 0; i < dif*2 +1;){
									vx = rand()%lin;
									vy = rand()%col;

									if(mapa[total_andar][vx][vy]==VAZIO&&(vx==lin/2||vy==col/2)){
										mapa[total_andar][vx][vy] = INIMIGO;
										++i;
									}
								}
								fimapa = 1;
							}
						}while(fimapa!=1);
						NovaDungeon = 0;
						total_andar++;
						final = 0;
					}
					else{
						
						while(final!=2){
							system("clear");
							for(int i= 0;i<col+2;i++){
								printf("█");
							}
							printf("\n");
							for(int i=0;i<lin;i++){
								printf("█");
								for(int j=0; j<col; j++){
									
									if(i==px&j==py){
										VERMELHO
										printf("G");
										AMARELO
									}
									else if(mapa[andar][i][j]==PAREDE){printf("#");}
									else if(mapa[andar][i][j]==VAZIO){printf(" ");}
									else if(mapa[andar][i][j]==ENTRADA){
										AZUL
										printf("◎");
										AMARELO
									}
									else if(mapa[andar][i][j]==SAIDA){
										AZUL
										printf("◉");
										AMARELO
									}
									else if(mapa[andar][i][j]==CHAVE){
										VERDE
										printf("▣");
										AMARELO
									}
									else if(mapa[andar][i][j]==INIMIGO){
										VERMELHO
										printf("☠");
										AMARELO
									}
									
								}
								printf("█");
								if(i==2){
									printf("\t\tAndar: %i", andar);
								}
								else if(i==4){
									printf("\tPV: %i", vp);
								}
								else if(i==5){
									printf("\tPontos: %i", pontos);
								}
								printf("\n");
							}
							for(int i = 0; i<col+2;i++){
								printf("█");
							}
							// CAPTURA TECLA
							jogada = getch();
							// TECLA ESPECIAL
							if(jogada == 27) {
								jogada = getch(); 
								if(jogada == 91) {      
									jogada = getch();
									// CIMA
									if(jogada == 65) {
										if(px > 0 && mapa[andar][px-1][py]!=PAREDE) {
											px--;
											if(passo==5){
												pontos++;
												passo = 0;
											}
											else{
												passo++;
											}
											if(mapa[andar][px][py]==SAIDA){
												andar++;
												final = 2;
												if(andar == total_andar){
													NovaDungeon = 1;
												}
											}
											else if(mapa[andar][px][py]==ENTRADA){
												andar--;
												final = 2;
											}

											else if(mapa[andar][px][py]==INIMIGO){
												final = 2;
											}
										}
									}		
						  			// BAIXO
									else if(jogada == 66 && mapa[andar][px+1][py]!=PAREDE) {
							    			if(px < lin-1) {
											px++;
											if(passo==5){
												pontos++;
												passo = 0;
											}
											else{
												passo++;
											}
											if(mapa[andar][px][py]==SAIDA){
												andar++;
												final = 2;
												if(andar == total_andar){
													NovaDungeon = 1;
												}
											}
											else if(mapa[andar][px][py]==ENTRADA){
												andar--;
												final = 2;
											}
											else if(mapa[andar][px][py]==INIMIGO){
												final = 2;
											}
										}
									}
									// DIREITA
									else if(jogada == 67 && mapa[andar][px][py+1]!=PAREDE) {
										if(py < col-1) {
											py++;
											if(passo==5){
												pontos++;
												passo = 0;
											}
											else{
												passo++;
											}
											if(mapa[andar][px][py]==SAIDA){
												andar++;
												final = 2;
												if(andar == total_andar){
													NovaDungeon = 1;
												}
											}
											else if(mapa[andar][px][py]==ENTRADA){
												andar--;
												final = 2;
											}
											else if(mapa[andar][px][py]==INIMIGO){
												final = 2;
											}
										}
								    }
									// ESQUERDA
									else if(jogada == 68) {
										if(py > 0 && mapa[andar][px][py-1]!=PAREDE) {
											py--;
											if(passo==5){
												pontos++;
												passo = 0;
											}
											else{
												passo++;
											}
											if(mapa[andar][px][py]==SAIDA){
												andar++;
												final = 2;
												if(andar == total_andar){
													NovaDungeon = 1;
												}
											}
											else if(mapa[andar][px][py]==ENTRADA){
												andar--;
												final = 2;
											}
											else if(mapa[andar][px][py]==INIMIGO){
												final = 2;
											}
										}
									}
								}
							}
							else if(jogada=='o'||jogada=='O'){
								final = 2;
							}

						//fim while
						}
					}

					

					if(mapa[andar+1][px][py]==ENTRADA){
						for(int i =0; i<lin; i++){
							for(int j = 0; j<col; j++){
								if(mapa[andar][i][j]==SAIDA){
									px = i;
									py = j;
								}
							}
						}
						final = 0;
						if (andar==-1){
							printf("\ndeseja sair? S/n\n");
							__fpurge(stdin);
							resp=getchar();
							if(resp=='S'||resp=='s'){
								final = 1;
							}
							else{andar = 0;}
						}
					}
					else if(mapa[andar-1][px][py]==SAIDA){
						for(int i =0; i<lin; i++){
							for(int j = 0; j<col; j++){
								if(mapa[andar][i][j]==ENTRADA){
									px = i;
									py = j;
								}
							}
						}
						final = 0;
					}
					else if(mapa[andar][px][py]==INIMIGO){
						final = 3;
						bost = 1;
						if(dif==1){
							//inimigo
							vi = 25;
							ai = 10;
							bosti = 1;
						}
						else if(dif==2){
							vi = 50;
							ai = 12;
							bosti = 1;
						}
						else if(dif==3){
							vi = 75;
							ai = 15;
							bosti = 1;
						}

						else if(dif==2){
							
						}
						else if(dif==3){
							
						}
						while(final==3){
							system("clear");
							printf("\t\t\tBATALHA\n");
							printf("\t%s\t\t\tINIMIGO\n", player);
							printf("\t%i\t\t\t%i\n", vp, vi);
							if(ataque==1){
								printf("\tataque leve");
							}
							else if(ataque==2){
								printf("\tdefesa");
							}
							else if(ataque==3){
								
								printf("\tataque pesado");
							}

							if(ini==1){
								printf("\t\tataque leve\n");
							}
							else if(ini==2){
								printf("\t\tdefesa\n");
							}
							else if(ini==3){
								
								printf("\t\tataque pesado\n");
							}
							printf("\tbost: %i\t\tbost: %i", bost, bosti);
							printf("\n\t1) ataque leve  2) defesa  3) ataque pesado");
							scanf("%i", &ataque);

							if(dif==1){
								ini = rand()%2+1;
							}
							else if(dif==2){
								ini = rand()%3+1;
							}
							else if(dif==3){
								ini = rand()%2+2;
							}


							if(ataque==PEDRA&&ini==TESOURA){
								vi -= ap*bost/2;
								bost = 1;
							}
							else if(ataque==TESOURA&&ini==PAPEL){
								vi -= ap*bost;
								bost = 1;
							}
							else if(ataque==PAPEL&&ini==PEDRA){
								if(bost < 3)
								bost ++;
							}
							else if(ini==PEDRA&&ataque==TESOURA){
								vp -= ai*bosti/2;
								bosti = 1;
							}
							else if(ini==TESOURA&&ataque==PAPEL){
								vp -= ai*bosti;
								bosti = 1;
							}
							else if(ini==PAPEL&&ataque==PEDRA){
								if(bosti < dif+2)
								bosti ++;
							}
	
							if(vp<=0){
								final = 2;
								jogada = 'o';
								for(int i = 0; i< 10; i++){
									if(pontos>Rp[i]){
										for(int j = 9; j>i; j--){
											Rp[j] = Rp[j-1];
											for(int c = 0; Rn[j-1][c]!='\0';c++){
												Rn[j][c] = Rn[j-1][c];
											}
										}
										Rp[i] = pontos;
										for(int c = 0; player[c]!='\0';c++){
												Rn[i][c] = player[c];
										}
										break;
									}
								}
								
							}
							else if(vi<=0){
								final = 0;
								mapa[andar][px][py] = VAZIO;
								ini  =0;
								while(ini<1){
									vx = rand()%lin;
									vy = rand()%col;
									if(mapa[andar][vx][vy]==VAZIO&&(vx==lin/2||vy==col/2)){
										mapa[andar][vx][vy] = INIMIGO;
										ini++;
									}
								}

								if(dif==1){
									pontos += 10;
									vi += vi*0.75;
								}
								else if(dif==2){
									pontos += 50;
									vi += vi*0.5;
								}
								else if(dif==3){
									pontos += 100;
									vi += vi*0.25;
								}

								if(pontos>pxn){
									ap += pontos/100;
									pxn *=2;
								}
							}
						}
								
						
					}

					if(jogada=='o'||jogada=='O')
						final = 1;
				}
			break;
			case 2:
				
				while(sair!=2){
					system("clear");
					TITULO
					printf("███\t\tConfigurações\t\t       ███\n");
					printf("███\t\t\t\t\t       ███\n███\t1. Tamanho da matriz\t\t       ███");
					printf("\n███\t2. Dificuldade\t\t\t       ███");
					printf("\n███\t3. Informativos(em breve)\t       ███");
					printf("\n███\t4. Desbloqueaveis(em breve)\t       ███");
					printf("\n███\t0. Voltar\t\t\t       ███\n");
					printf("███                                            ███\n");
					printf("██████████████████████████████████████████████████\n\t>");
					scanf("%i", &op);

					switch(op){
						case 1:
							system("clear");
							TITULO
							printf("███\t\tTamanho do mapa\t\t       ███\n");
							printf("███\t\t\t\t\t       ███\n███\t1. 15x15\t\t\t       ███");
							printf("\n███\t2. 30x50\t\t\t       ███");
							printf("\n███\t3. 37x100\t\t\t       ███");
							printf("\n███\t4. personalizado\t\t       ███\n");
							printf("███                                            ███\n");
							printf("██████████████████████████████████████████████████\n\t>");
							scanf("%i", &op);

							switch(op){
								case 1:
									col = lin = 15;
								break;
								case 2:
									col = 50;
									lin = 30;
								break;
								case 3:
									col = 100;
									lin = 36;
								break;
								case 4:

									while(sair!=3){
										system("clear");
										TITULO
										printf("███\t\tPersonalizado\t\t       ███\n███\t   (valores entre 15 e 100)\t       ███\n███                                            ███\n███  linha: ?\t\t\t\t       ███\n");
										printf("███                                            ███\n");
										printf("██████████████████████████████████████████████████\n\t>");
										scanf("%i", &lin);
										if(lin>=15&&lin<=100){
											sair = 3;
										}
									}
									while(sair!=4){
										system("clear");
										TITULO
										printf("███\t\tPersonalizado\t\t       ███\n███\t   (valores entre 15 e 100)\t       ███\n███                                            ███\n███  linha: %i\t\t\t\t       ███\n███  coluna: ?\t\t\t\t       ███\n", lin);
										printf("███                                            ███\n");
										printf("██████████████████████████████████████████████████\n\t>");
										scanf("%i", &col);
										if(col>=15&&col<=100){
											sair = 4;
										}
									}
								break;
							}							
							VERDE
							printf("\tTamanho definido com sucesso\n");
							AMARELO
							sleep(1);

						break;
						case 2:
							system("clear");
							TITULO
							printf("███\t\tDificuldade\t\t       ███\n");
							printf("███                                            ███\n");
							printf("███\t1. Fácil\t\t\t       ███");
							printf("\n███\t2. Médio\t\t\t       ███");
							printf("\n███\t3. Dificil\t\t\t       ███\n");
							printf("███                                            ███\n");
							printf("██████████████████████████████████████████████████\n\t>");
							scanf("%i", &op);

							switch(op){
								case 1:
									dif = 1;
								break;
								case 2:
									dif = 2;
								break;
								case 3:
									dif = 3;
								break;
							}
						break;
						case 3:

						break;
						case 4:

						break;
						case 0:
							sair = 2;
						break;

					}

				}
			break;
			case 3: 
				while(resp!='s'){
					system("clear");
					TITULO
					printf("███\t\tRanking\t\t\t       ███\n");
					printf("███\t\t\t\t\t       ███\n");
					for(int i = ini; i< ini+5; i++){
						printf("███\t%i.", i+1);
						for(int j = 0; j < 15 && Rn[i][j]!='\0'; j++){
							printf("%c", Rn[i][j]);
						}
						printf("\t\t\t%i\t       ███\n", Rp[i]);
						
					}
					printf("███                                            ███\n");
					printf("███\ts: Sair\t\t\t\t       ███\n");
					printf("███                                            ███\n");
					printf("██████████████████████████████████████████████████\n");
					// CAPTURA TECLA
						resp = getch();
						// TECLA ESPECIAL
						if(resp == 27) {
							resp = getch(); 
							if(resp == 91) {      
								resp = getch();
								// CIMA
								if(resp == 65) {
									if(ini>0)
										ini-- ;
								}		
					  			// BAIXO
								else if(resp == 66) {
						    		if(ini<5)
										ini++;
								}
							}
						}
				}

				resp = ' ';
			break;
			case 0:


				printf("    Deseja realmente sair? S/n\n    ");
				__fpurge(stdin);
				resp = getchar();

				if(resp=='S'|| resp=='s'){
					system("clear");
					printf("Te esperamos de volta para os desafios da Dungeon.\n");
					sair = 1;
				}
			break;
		}
	}

	return 0;
}