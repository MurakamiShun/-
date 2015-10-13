# ifndef DEF_CLASS_H
# define DEF_CLASS_H
# include <Siv3D.hpp>
# include <iostream>
# include <string>

//ボタン
class Button{
private:
	int* phase;
	int x, y;
	String Name;
	Rect RC;
	const Font font;
	void (*Func)(bool*);
public:
	Button(void (*pFunc)(bool*), int x, int y, String arg_Name);
	void Update();
	void Draw();
	bool end;
};

//ステータスの表示用
class GUIout{
private:
	String Buffer;
	Font status;
	short int lines;
	Rect fontsize;
public:
	GUIout();
	void operator<<(String);
	void Draw();
};

class DayDuty {
private:
	int ipoint;
	Font font;
	String str;
	String stone;
	String point;
public:
	DayDuty();
	bool SetPoint(int arg_point);
	void Draw();
};

# endif