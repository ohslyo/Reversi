#ifndef CHECK_HEADER
#define CHECK_HEADER

class Check{
public:
	//配置可能かどうか判断(最後のboolがtrueなら判定後配置実行)
	bool position(int ,int, char, char[10][10], bool);

	//次のターンに相手が石を置くところがあるか判定(ある場合は-1、ない場合は1を返す)
	int pass(char, char[10][10]);

};

#endif