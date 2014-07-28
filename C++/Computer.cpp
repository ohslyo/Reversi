#include <string.h>
#include "Computer.h"
#include "Start.h"
#include "Check.h"

void Computer::think(int *x, int *y, char turn, char board[10][10]){
	int i, j, k;
	int get;	//取れる石のカウント用
	int max = 0;	//取れる石の最大値

	for (i = 1; i < 9; i++){
		for (j = 1; j < 9; j++){
			get = 0;

			//指定した個所が空白か判定
			if (board[i][j] != BLANK) {
				continue;
			}

			//左上方向に裏返せる石があるか判定
			if (board[i - 1][j - 1] == -turn){
				k = 2;
				while ((i - k > 0) || (j - k > 0)){
					if ((board[i - k][j - k] == BLANK) || (board[i - k][j - k] == FRAME)){
						break;
					}
					if (board[i - k][j - k] == turn){

						//ここに配置した場合相手が次の番パスするかチェック
						if (continuity(i, j, turn, board)){
							*x = i;
							*y = j;
							return;
						}
						get += k;
						break;
					}
					k++;
				}
			}

			//左方向に裏返せる石があるか判定
			if (board[i][j - 1] == -turn){
				k = 2;
				while (j - k > 0){
					if ((board[i][j - k] == BLANK) || (board[i][j - k] == FRAME)){
						break;
					}
					if (board[i][j - k] == turn){

						//ここに配置した場合相手が次の番パスするかチェック
						if (continuity(i, j, turn, board)){
							*x = i;
							*y = j;
							return;
						}
						get += k;
						break;
					}
					k++;
				}
			}

			//左下方向に裏返せる石があるか判定
			if (board[i + 1][j - 1] == -turn){
				k = 2;
				while ((i + k < 9) || (j - k > 0)){
					if ((board[i + k][j - k] == BLANK) || (board[i + k][j - k] == FRAME)){
						break;
					}
					if (board[i + k][j - k] == turn){

						//ここに配置した場合相手が次の番パスするかチェック
						if (continuity(i, j, turn, board)){
							*x = i;
							*y = j;
							return;
						}
						get += k;
						break;
					}
					k++;
				}
			}

			//下方向に裏返せる石があるか判定
			if (board[i + 1][j] == -turn){
				k = 2;
				while (i + k < 9){
					if ((board[i + k][j] == BLANK) || (board[i + k][j] == FRAME)){
						break;
					}
					if (board[i + k][j] == turn){

						//ここに配置した場合相手が次の番パスするかチェック
						if (continuity(i, j, turn, board)){
							*x = i;
							*y = j;
							return;
						}
						get += k;
						break;
					}
					k++;
				}
			}

			//右下方向に裏返せる石があるか判定
			if (board[i + 1][j + 1] == -turn){
				k = 2;
				while ((i + k < 9) || (j + k < 9)){
					if ((board[i + k][j + k] == BLANK) || (board[i + k][j + k] == FRAME)){
						break;
					}
					if (board[i + k][j + k] == turn){

						//ここに配置した場合相手が次の番パスするかチェック
						if (continuity(i, j, turn, board)){
							*x = i;
							*y = j;
							return;
						}
						get += k;
						break;
					}
					k++;
				}
			}

			//右方向に裏返せる石があるか判定
			if (board[i][j + 1] == -turn){
				k = 2;
				while (j + k < 9){
					if ((board[i][j + k] == BLANK) || (board[i][j + k] == FRAME)){
						break;
					}
					if (board[i][j + k] == turn){

						//ここに配置した場合相手が次の番パスするかチェック
						if (continuity(i, j, turn, board)){
							*x = i;
							*y = j;
							return;
						}
						get += k;
						break;
					}
					k++;
				}
			}

			//右上方向に裏返せる石があるか判定
			if (board[i - 1][j + 1] == -turn){
				k = 2;
				while ((i - k > 0) || (j + k < 9)){
					if ((board[i - k][j + k] == BLANK) || (board[i - k][j + k] == FRAME)){
						break;
					}
					if (board[i - k][j + k] == turn){

						//ここに配置した場合相手が次の番パスするかチェック
						if (continuity(i, j, turn, board)){
							*x = i;
							*y = j;
							return;
						}
						get += k;
						break;
					}
					k++;
				}
			}

			//上方向に裏返せる石があるか判定
			if (board[i - 1][j] == -turn){
				k = 2;
				while (i - k > 0){
					if ((board[i - k][j] == BLANK) || (board[i - k][j] == FRAME)){
						break;
					}
					if (board[i - k][j] == turn){

						//ここに配置した場合相手が次の番パスするかチェック
						if (continuity(i, j, turn, board)){
							*x = i;
							*y = j;
							return;
						}
						get += k;
						break;
					}
					k++;
				}
			}

			if ((board[1][1] ||	//左角か
				board[1][9] ||	//右角か
				board[9][1] ||	//左角か
				board[9][9]) &&	//右角で
				(get > 1)){		//石が取れる場合
				get += 10;		//getに10プラスして優先度を上げる(10の根拠はなし)
			}

			if (get > max){
				max = get;
				*x = i;
				*y = j;
			}

		}
	}
}

bool Computer::continuity(int x, int y, char turn, char board[10][10]){
	
	Check check;
	
	memcpy(com_board, board, sizeof(char[10][10]));

	//com_boardに仮配置
	check.position(x, y, turn, com_board, true);

	//そこに置いた場合次のターン相手がパスするか確認
	if (check.pass(turn, com_board) == 1){

		//パスしない場合は否
		return true;
	}
	//パスする場合は正
	return false;
}