# include "Class.h"
# include <thread>

//コンストラクタ
Button::Button(void(*pFunc)(bool*), int  arg_x, int arg_y, String arg_Name) :
Func(pFunc),
x(arg_x),
y(arg_y),
Name(arg_Name),
font(25),
end(true)
{
	RC = font(Name).region(x, y);
}
//アップデート
void Button::Update(){
	if (RC.leftClicked && end){
		end = false;
		std::thread th(Func, &end);
		th.detach();
	}
}
//描画
void Button::Draw(){
	if (!end){
		font(Name).draw(x, y, Color(247, 251, 70));
	}
	else if (RC.mouseOver){
		font(Name).draw(x, y, Color(247, 251, 70));
	}
	else{
		font(Name).draw(x, y, Color(255, 128, 128));
	}
	TextureAsset(L"noise").map(RC.w, RC.h).draw(x, y);
}

//コンストラクタ
GUIout::GUIout() :
fontsize(0, 0, 0, 0)
{
	Buffer.reserve(200);
	status(20);
	lines = 0;
}
//オペレーター
void GUIout::operator<<(String str){
	if (lines >= 9){//10行超えたら消去
		Buffer.clear();
		lines = 0;
	}
	if (str.includes(L"\n")){//改行のカウント
		lines += 1;
	}
	Buffer += str;
	fontsize = status.region(Buffer);
}
//描画
void GUIout::Draw() {
	status(Buffer).draw(400, 60, Palette::White);
	TextureAsset(L"noise").map(fontsize.w, fontsize.h).draw(400, 60);
}

DayDuty::DayDuty():
ipoint(10000000),
str(L"\n 点\n\n\n 個\n\n氏名\n 長\n 野\n 高\n 専\n"),
point(L"不明"),
stone(L"不明")
{
	font(15);
}
bool DayDuty::SetPoint(int arg_point) {
	if (arg_point < ipoint) {
		ipoint = arg_point;
		point = Format(int(ipoint / 1000));
		stone = Format(ipoint % 1000);
		return true;
	}
	else {
		return false;
	}
}
void DayDuty::Draw() {
	font(str).draw(880, 10, Palette::White, 0.8);
	font(point).drawCenter({ 905, 35 });
	font(stone).drawCenter({ 905, 150 });
	TextureAsset(L"noise").map(80, 490).draw(880, 10);
}