#include <string.h>
#include "Computer.h"
#include "Start.h"
#include "Check.h"

void Computer::think(int *x, int *y, char turn, char board[10][10]){
	int get = 0;	//取れる石のカウント用(優先度)
	int max = -255;	//取れる石の最大値
	int p_max = 0;	//取られる石の最大値

	Check check;

	for (int i = 1; i < 9; i++){
		for (int j = 1; j < 9; j++){

			memcpy(com_board, board, sizeof(char[10][10]));

			get = check.position(i, j, turn, com_board, true);
			
			if (get > 0){
				if (check.pass(turn, com_board) == 1){
					*x = i;
					*y = j;
					return;
				}

				//角が取れる場合は優先度を上げる
				if ((i == 1 && j == 1) ||	//左角か
					(i == 1 && j == 8) ||	//右角か
					(i == 8 && j == 1) ||	//左角か
					(i == 8 && j == 8)){	//右角で
					get += 20;		//getに20プラスして優先度を上げる(20の根拠はなし)
				}

				//角に隣接した場所に置くときは優先度を下げる
				if ((i <= 2 && j <= 2) ||
					(i <= 2 && j >= 7) ||
					(i >= 7 && j <= 2) ||
					(i >= 7 && j >= 7)){
					get -= 10;		//getに10マイナスして優先度を下げる(10の根拠はなし)
				}

				//次のターン相手に角をとられる場所は優先度を下げる(10の根拠はなし)
				if (corner(turn, board)){
					get -= 10;
				}

				//board[i][j]に置いた場合相手がどこに置くかを計算
				for (int I = 1; I < 9; I++){
					for (int J = 1; J < 9; J++){
						if (p_max < check.position(I, J, -turn, com_board, false)){
							p_max = check.position(I, J, -turn, com_board, false);
						}
					}
				}

				get -= p_max;

				if (get > max){
					max = get;
					*x = i;
					*y = j;
				}
			}
		}
	}
}

bool Computer::corner(char turn, char board[10][10]){
	
	Check check;

	//現状の盤ですでに相手に角をとられる場合はfalse
	for (int i = 1; i < 9; i += 7){
		for (int j = 1; j < 9; j += 7){
			if (check.position(i, j, -turn, board, false)){
				return false;
			}
		}
	}

	//配置後の盤で相手に角をとられる場合はtrue
	for (int i = 1; i < 9; i += 7){
		for (int j = 1; j < 9; j += 7){
			if (check.position(i, j, -turn, com_board, false)){
				return true;
			}
		}
	}

	return false;

}

