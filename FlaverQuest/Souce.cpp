/*----------ヘッダーファイル----------*/
#include "DxLib.h"

/*----------マクロ定義----------*/
#define GAME_WIDTH	1024	//画面の横の大きさ
#define GAME_HEIGHT	576	//画面の縦の大きさ
#define GAME_COLOR	32	//画面のカラービット

#define GAME_WINDOW_BAR	0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"Flavor Quest"	//ウィンドウのタイトル

#define ERR -1			//-1をエラー

//FPS設定
#define GAME_FPS			60	//FPSの数値	

//パスの長さ
#define PATH_MAX			255	//255文字まで
#define NAME_MAX			255	//255文字まで

//画像
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")		//画像読み込みエラーメッセージ
#define IMAGE_TITLE_BK_PATH		TEXT(".\\IMAGE\\TitleBack.png") //タイトル背景のパス
#define IMAGE_TITLE_ROGO_PATH	TEXT(".\\IMAGE\\titlerogo.png")	//タイトルロゴのパス
#define	IMAGE_TITLE_ROGO_ROTA	0.25		//タイトルロゴ拡大率
#define IMAGE_TITLE_START_PATH		TEXT(".\\IMAGE\\title_start.png")	//タイトルスタートの画像
#define IMAGE_TITLE_START_ROTA	1
//音楽
#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")		//音楽読み込みエラーメッセージ
#define MUSIC_START_PATH		TEXT(".\\MUSIC\\start.mp3")		//タイトルBGM

/*----------プロトタイプ宣言----------*/
//スタート画面
VOID MY_START(VOID);		//スタート画面
VOID MY_START_PROC(VOID);	//スタート画面の処理
VOID MY_START_DRAW(VOID);	//スタート画面の描画

//プレイ画面
VOID MY_PLAY(VOID);			//プレイ画面
VOID MY_PLAY_PROC(VOID);	//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);	//プレイ画面の描画
VOID MY_PLAY_RESET(VOID);	//プレイ画面の初期化

//エンド画面
VOID MY_END(VOID);			//エンド画面
VOID MY_END_PROC(VOID);		//エンド画面の処理
VOID MY_END_DRAW(VOID);		//エンド画面の描画

//キー入力処理
VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//キーの入力状態を更新する
BOOL MY_KEY_DOWN(int);				//キーを押しているか、キーコードで判断する
BOOL MY_KEY_UP(int);				//キーを押し上げたか、キーコードで判断する
BOOL MY_KEYDOWN_KEEP(int, int);		//キーを押し続けているか、キーコードで判断する

//FPS関連
VOID MY_FPS_UPDATE(VOID);			//FPS値を計測、更新する関数
VOID MY_FPS_DRAW(VOID);				//FPS値を描画する関数
VOID MY_FPS_WAIT(VOID);				//FPS値を計測し、待つ関数

//画像読み込み処理
BOOL MY_LOAD_IMAGE(VOID);		//画像をまとめて読み込む関数
VOID MY_DELETE_IMAGE(VOID);		//画像をまとめて削除する関数

//音楽
BOOL MY_LOAD_MUSIC(VOID);		//音楽読み込み
VOID MY_DELETE_MUSIC(VOID);		//音楽削除

/*----------グローバル変数----------*/
//シーンの追加
enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END
};

//画像構造体
typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
}IMAGE;

//回転拡大する画像の構造体
typedef struct STRUCT_IMAGE_ROTA
{
	IMAGE image;		//IMAGE構造体
	double angle;		//回転率
	double rate;		//拡大率

}IMAGE_ROTA;

//プレイヤー
typedef struct STRUCT_CHARA
{
	IMAGE image;				//IMAGE構造体
	int speed = 1;					//速さ

	RECT coll;					//当たり判定
	int PlayerStartPosX = 30;
	int PlayerStartPosY = 300;
}CHARA;	//キャラクター構造体

//音楽構造体
typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
}MUSIC;

//シーン
int GameScene;

//キーボードの入力を取得
char AllKeyState[256] = { '\0' };			//すべてのキーの状態が入る
char OldAllKeyState[256] = { '\0' };	//すべてのキーの状態(直前)が入力
int StartTimeFps;						//測定開始時刻
int CountFps;							//カウンタ
float CalcFps;							//計算結果
int SampleNumFps = GAME_FPS;		//平均を取るサンプル数

//画像
IMAGE ImageTitleBK;					//タイトル背景
IMAGE_ROTA ImageTitleRogo;			//タイトルロゴ
IMAGE_ROTA ImageTitleStart;			//タイトルスタートの画像

//音楽
MUSIC musicStart;		//スタート画面の音楽


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);		//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));	//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);						//非アクティブでも実行する
	SetMouseDispFlag(FALSE);					//マウスカーソル非表示

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	int DrawX = 0;	//表示位置X
	int DrawY = 0;	//表示位置Y

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

	//画像読み込み
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//音楽読み込み
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	GameScene = GAME_SCENE_START;//最初はスタート画面から

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != FALSE) { break; }	//メッセージ処理の結果がエラーのとき、強制終了

		if (ClearDrawScreen() != FALSE) { break; }	//画面を消去できなかったとき、強制終了

		MY_FPS_UPDATE();	//FPSの処理[更新]
		MY_FPS_DRAW();		//FPSの処理[描画]
		MY_FPS_WAIT();		//FPSの処理[待つ]

		MY_ALL_KEYDOWN_UPDATE();				//押しているキー状態を取得

		//シーンごとに処理を行う
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//スタート画面
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//プレイ画面
			break;
		case GAME_SCENE_END:
			MY_END();	//エンド画面
			break;
		}

		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画
	}

	//画像ハンドルを破棄
	MY_DELETE_IMAGE();

	//音楽削除
	MY_DELETE_MUSIC();
	DxLib_End();	//ＤＸライブラリ使用の終了処理

	return 0;
}

/*----------スタート画面----------*/
VOID MY_START(VOID)
{
	MY_START_PROC();	//スタート画面の処理
	MY_START_DRAW();	//スタート画面の描画

	return;
}

//スタート画面の処理
VOID MY_START_PROC(VOID)
{
	//BGM再生
	if (CheckSoundMem(musicStart.handle) == 0) {					//正しく読み取れていたら
		ChangeVolumeSoundMem(255 * 50 / 100, musicStart.handle);	//音量変更
		PlaySoundMem(musicStart.handle, DX_PLAYTYPE_LOOP);			//再生
	}
	//エンターキーを押したら、プレイシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		//BGM停止
		if (CheckSoundMem(musicStart.handle) != 0) {
			StopSoundMem(musicStart.handle);
		}
		GameScene = GAME_SCENE_PLAY;
	}

	return;
}

//スタート画面の描画
VOID MY_START_DRAW(VOID)
{
	//背景
	DrawGraph(0, 0, ImageTitleBK.handle, TRUE);

	//ロゴ
	DrawRotaGraph(
		ImageTitleRogo.image.x,
		ImageTitleRogo.image.y,
		ImageTitleRogo.rate,
		ImageTitleRogo.angle,
		ImageTitleRogo.image.handle,
		TRUE
	);

	//スタート表示
	DrawRotaGraph(
		ImageTitleStart.image.x,
		ImageTitleStart.image.y,
		ImageTitleStart.rate,
		ImageTitleStart.angle,
		ImageTitleStart.image.handle,
		TRUE);

	DrawString(0, 0, "スタート画面", GetColor(255, 255, 255));
	return;
}

/*----------プレイ画面----------*/
VOID MY_PLAY(VOID) {
	MY_PLAY_PROC();
	MY_PLAY_DRAW();
}

VOID MY_PLAY_PROC(VOID)
{
	//スペースキーを押したら、エンドシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		GameScene = GAME_SCENE_END;
	}

	return;
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	//緑の四角を描画
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 255, 0), TRUE);

	DrawString(0, 0, "プレイ画面(スペースキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

/*----------エンド画面----------*/
VOID MY_END(VOID)
{
	MY_END_PROC();	//エンド画面の処理
	MY_END_DRAW();	//エンド画面の描画
	return;
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{
	//エスケープキーを押したら、スタートシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		GameScene = GAME_SCENE_START;
	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	//青の四角を描画
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);

	DrawString(0, 0, "エンド画面(エスケープキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

/*------------FPS----------*/
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1フレーム目なら時刻を記憶
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60フレーム目なら平均を計算
	{
		int now = GetNowCount();
		//現在の時間から、0フレーム目の時間を引き、FPSの数値で割る＝1FPS辺りの平均時間が計算される
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}


VOID MY_FPS_DRAW(VOID)
{
	//文字列を描画
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}


VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//待つべき時間

	if (waitTime > 0)		//指定のFPS値よりも早い場合
	{
		WaitTimer(waitTime);	//待つ
	}
	return;
}

/*------------------キー入力処理関数-----------------------------*/
//キー入力の状態を維持
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[256];	//一時的に、現在のキーの入力状態を格納する

	//直前のキー入力をとっておく
	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//押されているキーのキーコードを押しているとき
		{
			AllKeyState[i]++;	//押されている
		}
		else
		{
			AllKeyState[i] = 0;	//押されていない
		}
	}
	return;
}

//キーを押しているか、キーコードで判断する
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//キーコードのキーを押している時
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//キーを押している
	}
	else
	{
		return FALSE;	//キーを押していない
	}
}

//キーを押し上げたか、キーコードで判断する
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//直前は押していて
		&& AllKeyState[KEY_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//キーを押し上げている
	}
	else
	{
		return FALSE;	//キーを押し上げていない
	}
}

//キーを押し続けているか、キーコードで判断する
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}

/*----------画像読み込み処理----------*/
BOOL MY_LOAD_IMAGE(VOID) {
	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);
	if (ImageTitleBK.handle == ERR) {
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);	//画像の幅と高さを取得
	ImageTitleBK.x = GAME_WIDTH / 2 - ImageTitleBK.x / 2;
	ImageTitleBK.y = GAME_HEIGHT / 2 - ImageTitleBK.y / 2;

	strcpy_s(ImageTitleRogo.image.path, IMAGE_TITLE_ROGO_PATH);
	ImageTitleRogo.image.handle = LoadGraph(ImageTitleRogo.image.path);
	if (ImageTitleRogo.image.handle == ERR) {
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	ImageTitleRogo.image.x = GAME_WIDTH / 2 - ImageTitleRogo.image.x / 2;
	ImageTitleRogo.image.y = GAME_HEIGHT / 2.5;
	ImageTitleRogo.angle = 0;
	ImageTitleRogo.rate = IMAGE_TITLE_ROGO_ROTA;

	//スタート表記
	strcpy_s(ImageTitleStart.image.path, IMAGE_TITLE_START_PATH);			//パスの設定
	ImageTitleStart.image.handle = LoadGraph(ImageTitleStart.image.path);			//読み込み
	if (ImageTitleStart.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleStart.image.handle, &ImageTitleStart.image.width, &ImageTitleStart.image.height);	//画像の幅と高さを取得
	ImageTitleStart.image.x = GAME_WIDTH / 2 - ImageTitleStart.image.x / 2;		//左右中央揃え
	ImageTitleStart.image.y = GAME_HEIGHT/1.2;		//上下中央揃え
	ImageTitleStart.angle = 0;
	ImageTitleStart.rate = IMAGE_TITLE_START_ROTA;

	return TRUE;
}

VOID MY_DELETE_IMAGE(VOID) {
	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleRogo.image.handle);
	DeleteGraph(ImageTitleStart.image.handle);
}

/*----------音楽読み込み処理----------*/
BOOL MY_LOAD_MUSIC(VOID) {
	//スタート画面のBGM
	strcpy_s(musicStart.path, MUSIC_START_PATH);
	musicStart.handle = LoadSoundMem(musicStart.path);
	if (musicStart.handle == ERR) {
		MessageBox(GetMainWindowHandle(), MUSIC_START_PATH,MUSIC_LOAD_ERR_TITLE , MB_OK);
		return FALSE;
	}

	return TRUE;
}

VOID MY_DELETE_MUSIC(VOID) {
	DeleteSoundMem(musicStart.handle);
}