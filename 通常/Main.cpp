# include <Siv3D.hpp>
# include "Class.h"
# include "ButtonEvents.h"

GUIout Gout;
DayDuty DD;

void Main()
{
	TextureAsset::Register(L"noise", L"Texture/noise.png");
	//設定の読み込み
	LoadConfig();
	//タイトル
	String Title(L"高専の敷き詰め理論ⅠＢ");
	Point TitlePos(10, 0);
	//ウィンドウスタイルの設定
	Window::SetStyle(WindowStyle::NonFrame);
	Window::Resize(960, 540);
	//フォントの用意
	Font titlefont(30);
	Texture Back(L"Texture/BlackBord.png");
	Rect font_size = titlefont.region(Title);
	//ボタンの用意
	Button Download(download, 20, 100, L"・ダウンロード");
	Button SelectFile(selectfile, 20, 170, L"・ファイルを選択");
	Button ReAnswer(reanswer, 20, 240, L"・再度問題を解く");
	Button Upload(upload, 20, 350, L"・アップロード");

	while (System::Update()){
		//ボタンのアップデート
		if (Download.end && SelectFile.end && Upload.end && ReAnswer.end){
			Download.Update();
			SelectFile.Update();
			Upload.Update();
			ReAnswer.Update();
		}

		//描画
		Back.draw();
		titlefont(Title).draw(TitlePos, Palette::White);
		TextureAsset(L"noise").map(font_size.w, font_size.h).draw(TitlePos);

		Download.Draw();
		SelectFile.Draw();
		ReAnswer.Draw();
		Upload.Draw();

		Gout.Draw();
		DD.Draw();
	}
}
