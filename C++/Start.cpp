#include <stdio.h>
#include "Start.h"
#include "Check.h"
#include "Computer.h"

Start::Start(){
	turn = 1;

}
void Start::initilize(){

	//盤作成
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
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
	
	int x = 0;

	//手番決定
	while (1){

		printf("あなたは先攻(1)：後攻(2)?");
		scanf_s("%d", &x);
		if (x == 1){
			player = BLACK;
			break;
		}
		else if (x == 2){
			player = WHITE;
			break;
		}
		else{
			printf("1(先攻)か2(後攻)を入力してください\n");
		}
	}
}

void Start::game(){

	Check check;
	Computer com;

	int x = 0;	//縦位置
	int y = 0;	//横位置

	while (1){

		int final_check = 0;	//BLANKの数を監視

		//手の入力
		if (turn == player){
			printf("あなたの手番です\n");
			while (1){
				printf("x y(縦スペース横)と入力してください\n");
				
				//デバック用
				//com.think(&x, &y, turn, board);
				scanf_s("%d %d", &x, &y);

				//配置可能か判定
				if (check.position(x, y, turn, board, true) > 0){
					break;
				}
				printf("そこには置けません\n");
			}

		}
		else{
			printf("Comの手番です\n");

			//コンピュータの手をx,yで受け取る
			com.think(&x, &y, turn, board);
			check.position(x, y, turn, board, true);
		}

		for (int i = 0; i < 10; i++){
			for (int j = 0; j < 10; j++){
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
		if (check.pass(turn, board) + check.pass(-turn, board) == 2){
			break;
		}

		turn *= check.pass(turn, board);
	}
	finish();
}

void Start::finish(){

	char shiro = 0;
	char kuro = 0;

	printf("終了です\n");

	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
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
