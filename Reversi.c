#include <stdio.h>

#define BLANK 0
#define BLACK 1
#define WHITE -1
#define FRAME 10

char board[10][10];


//配置可能か判定(最後のboolがtureの場合は配置実行)
int judgment(int, int, char, char);

//石のおける個所があるか判定
int pass_check(char);

//終了処理
void finish(void);

//AI
void thinking(int*, int*, char);

int main(){
	int x = 0;
	int y = 0;
	int i,j;

	char turn = BLACK;
	

	//初期化
	for (i = 0; i < 10; i++){
		for (j = 0; j < 10; j++){
			//フレーム作成
			if ((i == 0 || i == 9) || (j == 0 || j == 9)){
				board[i][j] = FRAME;
				printf("■");
			}
			//白の初期配置
			else if ((i == 4 && j == 4) || (i == 5 && j == 5)){
				board[i][j] = WHITE;
				printf("●");
			}
			//黒の初期配置
			else if ((i == 4 && j == 5) || (i == 5 && j == 4)){
				board[i][j] = BLACK;
				printf("○");
			}
			else {
				board[i][j] = BLANK;
				printf("　");
			}
		}
		printf("\n");
	}

	while (1){

		int final_check = 0;

		//手の入力
		if (turn == BLACK){
			printf("あなたの手番です\n");
			while (1){
				printf("x y(縦スペース横)と入力してください\n");
				scanf("%d %d", &x, &y);
				//thinking(&x, &y, turn);
				//配置可能か判定
				if (judgment(x, y, turn, 1)){
					break;
				}
				printf("そこには置けません\n");
			}

		}
		else{
			printf("Comの手番です\n");
			thinking(&x, &y, turn);
			judgment(x, y, turn, 1);
		}

		for (i = 0; i < 10; i++){
			for (j = 0; j < 10; j++){
				switch (board[i][j]){
				case BLANK:
					printf("　");
					//空白の数を数える
					final_check++;
					break;
				case WHITE:
					printf("●");
					break;
				case BLACK:
					printf("○");
					break;
				case FRAME:
					printf("■");
					break;
				default:
					break;
				}
			}
			printf("\n");
		}
		//空白の数が0の場合終了
		if (final_check == 0){
			break;
		}

		//石のおける個所があるかチェック
		if (pass_check(turn) + pass_check(-turn) == 2){
			break;
		}
		turn *= pass_check(turn);
	}

	finish();
	
	return 0;
}

int judgment(int x, int y, char turn, char flag){

	int check = 0;
	int i,j;

	//指定した個所が空白か判定
	if (board[x][y] != BLANK) {
		return check;
	}

	//左上方向に裏返せる石があるか判定
	if (board[x - 1][y - 1] == -turn){
		i = 2;
		while ((x - i > 0) || (y - i > 0)){
			if ((board[x - i][y - i] == BLANK) || (board[x - i][y - i] == FRAME)){
				break;
			}
			if (board[x - i][y - i] == turn){
				check = 1;
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
				check = 1;
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
				check = 1;
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
				check = 1;
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
				check = 1;
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
				check = 1;
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
				check = 1;
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
				check = 1;
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

	return check;
}

//次の手番で石が置ける場所があるかチェック(ある場合は-1を返し、ない場合は1を返す)
int pass_check(char turn){
	int i,j;
	for (i = 1; i < 9; i++){
		for (j = 1; j < 9; j++){
			if (judgment(i, j, -turn, 0) == 1){
				return -1;

			}
		}
	}
	return 1;
}

void thinking(int *x, int *y, char turn){

	int max = 0;
	int i,j,k;
	int get;

	for (k = 1; k < 9; k++){
		for (j = 1; j < 9; j++){

			get = 0;

			//指定した個所が空白か判定
			if (board[k][j] != BLANK) {
				continue;
			}

			//左上方向に裏返せる石があるか判定
			if (board[k - 1][j - 1] == -turn){
				i = 2;
				while ((k - i > 0) || (j - i > 0)){
					if ((board[k - i][j - i] == BLANK) || (board[k - i][j - i] == FRAME)){
						break;
					}
					if (board[k - i][j - i] == turn){
						get += i;
						break;
					}
					i++;
				}
			}

			//左方向に裏返せる石があるか判定
			if (board[k][j - 1] == -turn){
				i = 2;
				while (j - i > 0){
					if ((board[k][j - i] == BLANK) || (board[k][j - i] == FRAME)){
						break;
					}
					if (board[k][j - i] == turn){
						get += i;
						break;
					}
					i++;
				}
			}

			//左下方向に裏返せる石があるか判定
			if (board[k + 1][j - 1] == -turn){
				i = 2;
				while ((k + i < 9) || (j - i > 0)){
					if ((board[k + i][j - i] == BLANK) || (board[k + i][j - i] == FRAME)){
						break;
					}
					if (board[k + i][j - i] == turn){
						get += i;
						break;
					}
					i++;
				}
			}

			//下方向に裏返せる石があるか判定
			if (board[k + 1][j] == -turn){
				i = 2;
				while (k + i < 9){
					if ((board[k + i][j] == BLANK) || (board[k + i][j] == FRAME)){
						break;
					}
					if (board[k + i][j] == turn){
						get += i;
						break;
					}
					i++;
				}
			}

			//右下方向に裏返せる石があるか判定
			if (board[k + 1][j + 1] == -turn){
				i = 2;
				while ((k + i < 9) || (j + i < 9)){
					if ((board[k + i][j + i] == BLANK) || (board[k + i][j + i] == FRAME)){
						break;
					}
					if (board[k + i][j + i] == turn){
						get += i;
						break;
					}
					i++;
				}
			}

			//右方向に裏返せる石があるか判定
			if (board[k][j + 1] == -turn){
				i = 2;
				while (j + i < 9){
					if ((board[k][j + i] == BLANK) || (board[k][j + i] == FRAME)){
						break;
					}
					if (board[k][j + i] == turn){
						get += i;
						break;
					}
					i++;
				}
			}

			//右上方向に裏返せる石があるか判定
			if (board[k - 1][j + 1] == -turn){
				i = 2;
				while ((k - i > 0) || (j + i < 9)){
					if ((board[k - i][j + i] == BLANK) || (board[k - i][j + i] == FRAME)){
						break;
					}
					if (board[k - i][j + i] == turn){
						get += i;
						break;
					}
					i++;
				}
			}

			//上方向に裏返せる石があるか判定
			if (board[k - 1][j] == -turn){
				i = 2;
				while (k - i > 0){
					if ((board[k - i][j] == BLANK) || (board[k - i][j] == FRAME)){
						break;
					}
					if (board[k - i][j] == turn){
						get += i;
						break;
					}
					i++;
				}
			}

			if (get > max){
				max = get;
				*x = k;
				*y = j;
			}

		}
	}

}

void finish(){

	char shiro = 0;
	char kuro = 0;
	int i,j;

	printf("終了です\n");

	for (i = 0; i < 10; i++){
		for (j = 0; j < 10; j++){
			switch (board[i][j]){
			case WHITE:
				shiro++;
				break;
			case BLACK:
				kuro++;
				break;
			default:
				break;
			}
		}
	}

	if (shiro < kuro){
		printf("黒：%d\t白：%d\n", kuro, shiro);
		printf("黒の勝ちです\n");
	}
	else if (shiro > kuro){
		printf("黒：%d\t白：%d\n", kuro, shiro);
		printf("白の勝ちです\n");
	}
	else {
		printf("黒：%d\t白：%d\n", kuro, shiro);
		printf("引き分けです\n");
	}

}
