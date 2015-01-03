#ifndef COMPUTER_HEADER
#define COMPUTER_HEADER

class Computer{
public:
	//優先度：相手がパスする場所>角>=石が多くとれる場所
	void think(int *, int *, char, char[10][10]);

private:

	//相手をパスさせることができるか確認
	bool continuity(int, int, char, char[10][10]);

	//計算用ボード
	char com_board[10][10];
};

#endif