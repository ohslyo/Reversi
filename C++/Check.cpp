#include "Check.h"
#include "Start.h"

int Check::position(int x, int y, char turn, char board[10][10], bool flag){
	int get = 0;	//取れる石のカウント用
	int i, j;

	//指定した個所が空白か判定
	if (board[x][y] != BLANK) {
		return get;
	}

	//左上方向に裏返せる石があるか判定
	if (board[x - 1][y - 1] == -turn){
		i = 2;
		while ((x - i > 0) || (y - i > 0)){
			if ((board[x - i][y - i] == BLANK) || (board[x - i][y - i] == FRAME)){
				break;
			}
			if (board[x - i][y - i] == turn){
				get += i;
				//第4引数がtrueの場合石を配置
				if (flag){
					board[x][y] = turn;
					for (j = 1; j < i; j++){
						board[x - j][y - j] = turn;
					}
				}
				break;
			}
			i++;
		}
	}

	//左方向に裏返せる石があるか判定
	if (board[x][y - 1] == -turn){
		i = 2;
		while (y - i > 0){
			if ((board[x][y - i] == BLANK) || (board[x][y - i] == FRAME)){
				break;
			}
			if (board[x][y - i] == turn){
				get += i;
				//第4引数がtrueの場合石を配置
				if (flag){
					board[x][y] = turn;
					for (j = 1; j < i; j++){
						board[x][y - j] = turn;
					}
				}
				break;
			}
			i++;
		}
	}

	//左下方向に裏返せる石があるか判定
	if (board[x + 1][y - 1] == -turn){
		i = 2;
		while ((x + i < 9) || (y - i > 0)){
			if ((board[x + i][y - i] == BLANK) || (board[x + i][y - i] == FRAME)){
				break;
			}
			if (board[x + i][y - i] == turn){
				get += i;
				//第4引数がtrueの場合石を配置
				if (flag){
					board[x][y] = turn;
					for (j = 1; j < i; j++){
						board[x + j][y - j] = turn;
					}
				}
				break;
			}
			i++;
		}
	}

	//下方向に裏返せる石があるか判定
	if (board[x + 1][y] == -turn){
		i = 2;
		while (x + i < 9){
			if ((board[x + i][y] == BLANK) || (board[x + i][y] == FRAME)){
				break;
			}
			if (board[x + i][y] == turn){
				get += i;
				//第4引数がtrueの場合石を配置
				if (flag){
					board[x][y] = turn;
					for (j = 1; j < i; j++){
						board[x + j][y] = turn;
					}
				}
				break;
			}
			i++;
		}
	}

	//右下方向に裏返せる石があるか判定
	if (board[x + 1][y + 1] == -turn){
		i = 2;
		while ((x + i < 9) || (y + i < 9)){
			if ((board[x + i][y + i] == BLANK) || (board[x + i][y + i] == FRAME)){
				break;
			}
			if (board[x + i][y + i] == turn){
				get += i;
				//第4引数がtrueの場合石を配置
				if (flag){
					board[x][y] = turn;
					for (j = 1; j < i; j++){
						board[x + j][y + j] = turn;
					}
				}
				break;
			}
			i++;
		}
	}

	//右方向に裏返せる石があるか判定
	if (board[x][y + 1] == -turn){
		i = 2;
		while (y + i < 9){
			if ((board[x][y + i] == BLANK) || (board[x][y + i] == FRAME)){
				break;
			}
			if (board[x][y + i] == turn){
				get += i;
				//第4引数がtrueの場合石を配置
				if (flag){
					board[x][y] = turn;
					for (j = 1; j < i; j++){
						board[x][y + j] = turn;
					}
				}
				break;
			}
			i++;
		}
	}

	//右上方向に裏返せる石があるか判定
	if (board[x - 1][y + 1] == -turn){
		i = 2;
		while ((x - i > 0) || (y + i < 9)){
			if ((board[x - i][y + i] == BLANK) || (board[x - i][y + i] == FRAME)) {
				break;
			}
			if (board[x - i][y + i] == turn){
				get += i;
				//第4引数がtrueの場合石を配置
				if (flag){
					board[x][y] = turn;
					for (j = 1; j < i; j++){
						board[x - j][y + j] = turn;
					}
				}
				break;
			}
			i++;
		}
	}

	//上方向に裏返せる石があるか判定
	if (board[x - 1][y] == -turn){
		i = 2;
		while (x - i > 0){
			if ((board[x - i][y] == BLANK) || (board[x - i][y] == FRAME)){
				break;
			}
			if (board[x - i][y] == turn){
				get += i;
				//第4引数がtrueの場合石を配置
				if (flag){
					board[x][y] = turn;
					for (j = 1; j < i; j++){
						board[x - j][y] = turn;
					}
				}
				break;
			}
			i++;
		}
	}

	return get;
}

int Check::pass(char turn, char board[10][10]){
	for (int i = 1; i < 9; i++){
		for (int j = 1; j < 9; j++){
			//一マスづつ相手がおけるかを判定
			if (position(i, j, -turn, board, false) > 0){
				return -1;
			}
		}
	}
	return 1;
}

