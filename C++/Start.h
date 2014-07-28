#ifndef START_HEADER
#define START_HEADER

#define BLANK 0
#define BLACK 1
#define WHITE -1
#define FRAME 10


class Start{
public:
	Start();

	//盤の初期化
	void initilize();

	//ループし現状の番の状況を表示など
	void game();

	//終了処理
	void finish();

private:
	char board[10][10];	//盤
	char turn;	//ターン(1が黒、-1が白)
	char player;	//プレイヤーの色

};

#endif