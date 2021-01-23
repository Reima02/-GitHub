/*----------ヘッダーファイル----------*/
#include "DxLib.h"
#include "game.h"
#include "mapChip.h"

/*----------マクロ定義----------*/
#define GAME_WIDTH	1024	//画面の横の大きさ
#define GAME_HEIGHT	576	//画面の縦の大きさ
#define GAME_COLOR	32	//画面のカラービット

#define GAME_WINDOW_BAR	0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"Flavor Quest"	//ウィンドウのタイトル

#define ERR -1			//-1をエラー

//FPS設定
#define GAME_FPS			60	//FPSの数値	

//プレイヤー画像
#define PLAYER_CHANGE_NUM	3	//プレイヤー画像変更回数
#define PLAYER_WIDTH	32		//プレイヤー画像横
#define PLAYER_HEIGHT	32		//プレイヤー画像縦
#define PLAYER_DIV_TATE		4	//プレイヤー画像縦分割数
#define	PLAYER_DIV_YOKO		3	//プレイヤー画像横分割数
#define PLAYER_DIV_NUM		PLAYER_DIV_TATE*PLAYER_DIV_YOKO		//プレイヤー画像総分割数
#define PLAYER_ROTA			2.0		//プレイヤー拡大率
#define PLAYER_ACTWAIT		100	//プレイヤーアニメーション待ち時間
#define PLAYER_LEFT			3//左向き
#define PLAYER_LEFT_MAX		5//左最大
#define PLAYER_RIGHT		6//右向き
#define	PLAYER_RIGHT_MAX	8//右最大
#define PLAYER_BACK			9//後ろ向き
#define PLAYER_BACK_MAX		11//後ろ最大
#define PLAYER_RIGHT_STAY	7//右向き待ち
#define PLAYER_LEFT_STAY	4//左向き待ち

//画像
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")		//画像読み込みエラーメッセージ
#define IMAGE_TITLE_BK_PATH		TEXT(".\\IMAGE\\TitleBack.png") //タイトル背景のパス
#define IMAGE_TITLE_ROGO_PATH	TEXT(".\\IMAGE\\titlerogo.png")	//タイトルロゴのパス
#define	IMAGE_TITLE_ROGO_ROTA	0.25		//タイトルロゴ拡大率
#define IMAGE_TITLE_START_PATH		TEXT(".\\IMAGE\\title_start.png")	//タイトルスタートの画像
#define IMAGE_TITLE_START_ROTA	0.8			//スタート拡大率
#define IMAGE_OPERATING_PATH	TEXT(".\\IMAGE\\Operation.png")		//操作説明画像
#define IMAGE_OPERATING_ROTA	2.15
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\player.png")		//プレイヤー画像パス

//音楽
#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")		//音楽読み込みエラーメッセージ
#define MUSIC_START_PATH		TEXT(".\\MUSIC\\start.mp3")		//タイトルBGM
#define MUSIC_PLAY_PATH			TEXT(".\\MUSIC\\play.mp3")		//プレイBGM

//色
#define FONT_COLOR_BLACK	GetColor(0,0,0)			//色：黒
#define FONT_COLOR_RED		GetColor(255,0,0)		//色：赤
#define FONT_COLOR_WHITE	GetColor(255,255,255)	//色：白


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
VOID FIRST_FONT_DRAW(VOID);	//冒頭テキスト表示
VOID OPERATING_DRAW(VOID);	//操作方法表示
VOID PLAYER_SETTING(VOID);	//プレイヤー設定（PROC内）　モーション切り替えなど

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

//デバック用
void DrawBoxRect(RECT, unsigned int, bool);

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

//プレイヤー構造体
typedef struct STRUCT_CHARA
{
	char path[PATH_MAX];
	int handle[PLAYER_DIV_NUM];
	int x;
	int y;
	int width;
	int height;
	int nowImageKind;			//現在のキャラクター状態
	int changeImageCnt;			//変更したい画像		[0]～[2]：正面　[3]～[5]左	[6]～[8]右	[9]～[11]：背面
	int ChangeImageCntMax;		//変更したい画像ラスト	例：正面→2		左→5
	int keyState;
	int keyStateMax;
	int speed;
	double angle;
	double rate;

	int mapX;	//マップ左上（0）にしたとき、どのくらいのｘ位置にいるか
	int mapY;	//上のY版

	RECT coll;

}CHARA;	//キャラクター構造体

//当たり判定
VOID MY_CHECK_MAP_DOWN(CHARA*);

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
IMAGE_ROTA ImageOperating;				//操作説明
IMAGE_ROTA ImageTitleRogo;			//タイトルロゴ
IMAGE_ROTA ImageTitleStart;			//タイトルスタートの画像

//音楽
MUSIC musicStart;		//スタート画面の音楽
MUSIC musicPlay;		//プレイ画面の音楽

//冒頭
int fontX = GAME_WIDTH / 6;
int fontY = GAME_HEIGHT / 4;
int fontNum = 1;
BOOL inGameMain = FALSE;		//判定：ゲーム本編
BOOL isFontNext = TRUE;		//判定：冒頭テキスト次に進む

//プレイヤー
CHARA player;
int playerState = 0;
bool isChange = true;
float playerYspeed = 2;
int playerStartPosX = 450;

//MAP
MAP_CHIP mapChip;

MAP map_jimen[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
MAP mapInit_jimen[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

MAP map_sora[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
MAP mapInit_sora[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

MAP map_sousyoku[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
MAP mapInit_sousyoku[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

int MapKabeID[MAP_KABE_KIND] = {10,11,42,43};
int MapGuildID[MAP_GUILD_KIND] = { 202,203,234,235 };
int Sora1ID = 1;
int MapNoneID = 264;
int MapKanbanID = 257;
//マップ動かす
BOOL isMapMove = TRUE;
int mapYokoKijun;
int mapYokoLoopStart;
int mapYokoLoopEnd;

BOOL isStopMapLeft = TRUE;
BOOL isStopMapRight = TRUE;

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

	//画像読み込み
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//音楽読み込み
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	GameScene = GAME_SCENE_START;//最初はスタート画面から

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

	//マップチップを読み込む
	if (MY_LOAD_MAPCHIP() == FALSE) { return -1; }

	//CSVを読み込む
	if (MY_LOAD_CSV_MAP(GAME_CSV_PATH_MAP1_SORA, &map_sora[0][0], &mapInit_sora[0][0]) == FALSE) { return -1; }
	if (MY_LOAD_CSV_MAP(GAME_CSV_PATH_MAP1_JIMEN, &map_jimen[0][0], &mapInit_jimen[0][0]) == FALSE) { return -1; }
	if (MY_LOAD_CSV_MAP(GAME_CSV_PATH_MAP1_SOUSHOKU, &map_sousyoku[0][0], &mapInit_sousyoku[0][0]) == FALSE) { return -1; }

	//文字にアンチエイリアスをかける
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != FALSE) { break; }	//メッセージ処理の結果がエラーのとき、強制終了

		if (ClearDrawScreen() != FALSE) { break; }	//画面を消去できなかったとき、強制終了

		MY_FPS_UPDATE();	//FPSの処理[更新]
		

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
		MY_FPS_DRAW();
		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画
		MY_FPS_WAIT();		//FPSの処理[待つ]
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
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
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
	//テキスト冒頭処理
	if (!inGameMain) {
		SetFontSize(26);
		if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
		{
			if (isFontNext) {
				++fontNum;
				if (fontNum >= 8) {
					inGameMain = TRUE;
				}
			}
			isFontNext = false;
		}
		if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE)
		{
			isFontNext = TRUE;
		}
	}

	if (inGameMain) {
		SetFontSize(16);
		//BGM再生
		if (CheckSoundMem(musicPlay.handle) == 0) {					//正しく読み取れていたら
			ChangeVolumeSoundMem(255 * 50 / 100, musicPlay.handle);	//音量変更
			PlaySoundMem(musicPlay.handle, DX_PLAYTYPE_LOOP);			//再生
		}

		//プレイヤー設定
		PLAYER_SETTING();

		//当たり判定
		MY_CHECK_MAP_DOWN(&player);
		player.coll.left = player.x - player.width / 2;
		player.coll.top = player.y - player.height;
		player.coll.right = player.coll.left + player.width;
		player.coll.bottom = player.coll.top + player.height * 2;
		
		//スペースキーを押したら、エンドシーンへ移動する
	    if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
		{
			//BGM停止
			if (CheckSoundMem(musicPlay.handle) != 0) {
				StopSoundMem(musicPlay.handle);
			}

			GameScene = GAME_SCENE_END;
		}
	}

	return;
}

/*----------プレイヤー設定----------*/
VOID PLAYER_SETTING()
{
	if (MY_KEY_DOWN(KEY_INPUT_D) == TRUE) {
		playerState = 2;

	}
	else if (MY_KEY_UP(KEY_INPUT_D) == TRUE) {
		playerState = 0;
	}
	else if (MY_KEY_DOWN(KEY_INPUT_A) == TRUE) {
		playerState = 3;

	}
	else if (MY_KEY_UP(KEY_INPUT_A) == TRUE) {
		playerState = 1;
	}
	else {
		;
	}

	switch (playerState)
	{
	case 0:
		player.keyState = PLAYER_RIGHT_STAY;
		player.keyStateMax = PLAYER_RIGHT_STAY;
		player.ChangeImageCntMax = PLAYER_RIGHT_STAY;
		break;
	case 1:
		player.keyState = PLAYER_LEFT_STAY;
		player.keyStateMax = PLAYER_LEFT_STAY;
		player.ChangeImageCntMax = PLAYER_LEFT_STAY;
		break;
	case 2:
		player.keyState = PLAYER_RIGHT;
		player.keyStateMax = PLAYER_RIGHT_MAX;
		player.ChangeImageCntMax = PLAYER_RIGHT_MAX;
		break;
	case 3:
		player.keyState = PLAYER_LEFT;
		player.keyStateMax = PLAYER_LEFT_MAX;
		player.ChangeImageCntMax = PLAYER_LEFT_MAX;
		break;
	default:
		break;
	}
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	//冒頭部分
	if (!inGameMain) {
		FIRST_FONT_DRAW();		//関数：冒頭テキスト表示
	}

	//メイン部分
	else {
		//マップを動かせるとき
		if (isMapMove == TRUE)
		{
			//左入力
			if (MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
			{
				//左に行けるとき
				if (isStopMapLeft == TRUE) {
					for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
					{
						for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
						{
							//マップ移動
							map_sora[tate][yoko].x += player.speed;
							map_jimen[tate][yoko].x += player.speed;
							map_sousyoku[tate][yoko].x += player.speed;

							//当たり判定移動
							map_jimen[tate][yoko].coll.left += player.speed;
							map_jimen[tate][yoko].coll.right += player.speed;
						}
					}
				}
			}

			//右入力
			if (MY_KEY_DOWN(KEY_INPUT_D) == TRUE)
			{
				//右に動かせるとき
				if (isStopMapRight == TRUE)
				{
					for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
					{
						for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
						{
							//マップ移動
							map_sora[tate][yoko].x -= player.speed;
							map_jimen[tate][yoko].x -= player.speed;
							map_sousyoku[tate][yoko].x -= player.speed;

							//当たり判定移動
							map_jimen[tate][yoko].coll.left -= player.speed;
							map_jimen[tate][yoko].coll.right -= player.speed;
						}
					}

				}
			}

			//マップ下
			for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
			{
				for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
				{
					//マップ移動
					map_sora[tate][yoko].y -= player.speed;
					map_jimen[tate][yoko].y -= player.speed;
					map_sousyoku[tate][yoko].y -= player.speed;

					//当たり判定移動
					map_jimen[tate][yoko].coll.top -= player.speed;
					map_jimen[tate][yoko].coll.bottom -= player.speed;
				}
			}

			//マップの基準
			mapYokoKijun = player.mapX / MAP_DIV_WIDTH;
			mapYokoLoopStart = mapYokoKijun - GAME_YOKO_CENTER;
			mapYokoLoopEnd = mapYokoKijun + GAME_YOKO_CENTER + 1;

			//マップの端は固定（領域設定）
			if (mapYokoLoopStart < 0) { mapYokoLoopStart = 0; mapYokoLoopEnd = GAME_YOKO_CENTER * 2; }
			if (mapYokoLoopStart > GAME_MAP_YOKO_MAX) { mapYokoLoopStart = GAME_MAP_YOKO_MAX - GAME_YOKO_CENTER * 2; mapYokoLoopEnd = GAME_MAP_YOKO_MAX + 1; }

			//MAP表示
			for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
			{
				for (int yoko = mapYokoLoopStart; yoko < mapYokoLoopEnd; yoko++)
				{
					//空（下）
					DrawGraph(
						map_sora[tate][yoko].x,
						map_sora[tate][yoko].y,
						mapChip.handle[map_sora[tate][yoko].value],
						TRUE);

					//地面（中）
					DrawGraph(
						map_jimen[tate][yoko].x,
						map_jimen[tate][yoko].y,
						mapChip.handle[map_jimen[tate][yoko].value],
						TRUE);

					//装飾(上)
					DrawGraph(
						map_sousyoku[tate][yoko].x,
						map_sousyoku[tate][yoko].y,
						mapChip.handle[map_sousyoku[tate][yoko].value],
						TRUE);
				}
			}

			//プレイヤー表示
			DrawRotaGraph(
				player.x,
				player.y,
				player.rate,
				player.angle,
				player.handle[player.nowImageKind],
				TRUE
			);

			if (player.changeImageCnt < player.ChangeImageCntMax) {
				++player.changeImageCnt;
				player.nowImageKind = player.changeImageCnt;
			}
			else {
				player.nowImageKind = player.keyState;
				player.changeImageCnt = player.keyState;
			}

			//デバック用（当たり判定表示）
			for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++) {
				for (int yoko = mapYokoLoopStart; yoko < mapYokoLoopEnd; yoko++) {
					switch (map_jimen[tate][yoko].kind) {
					case MAP_KIND_KABE:
						DrawBoxRect(map_jimen[tate][yoko].coll, GetColor(0, 0, 255), FALSE);
						break;

					case MAP_KIND_TURO:
						DrawBoxRect(map_jimen[tate][yoko].coll, GetColor(0, 255, 0), FALSE);
						break;
					}
				}
			}

			DrawBoxRect(player.coll, GetColor(255, 0, 0), FALSE);


			DrawString(0, 0, "メインゲーム", FONT_COLOR_WHITE);
		}
		return;
	}
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
	ImageTitleRogo.image.y = GAME_HEIGHT / 2 - 50;
	ImageTitleRogo.angle = 0;
	ImageTitleRogo.rate = IMAGE_TITLE_ROGO_ROTA;

	//スタート表記
	strcpy_s(ImageTitleStart.image.path, IMAGE_TITLE_START_PATH);			//パスの設定
	ImageTitleStart.image.handle = LoadGraph(ImageTitleStart.image.path);			//読み込み
	if (ImageTitleStart.image.handle == ERR)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleStart.image.handle, &ImageTitleStart.image.width, &ImageTitleStart.image.height);	//画像の幅と高さを取得
	ImageTitleStart.image.x = GAME_WIDTH / 2 - ImageTitleStart.image.x / 2;		//左右中央揃え
	ImageTitleStart.image.y = GAME_HEIGHT / 2 + 200;		//上下中央揃え
	ImageTitleStart.angle = 0;
	ImageTitleStart.rate = IMAGE_TITLE_START_ROTA;

	//操作説明
	strcpy_s(ImageOperating.image.path, IMAGE_OPERATING_PATH);
	ImageOperating.image.handle = LoadGraph(ImageOperating.image.path);
	if (ImageOperating.image.handle == ERR) {
		MessageBox(GetMainWindowHandle(), IMAGE_OPERATING_PATH, IMAGE_LOAD_ERR_TITLE,MB_OK);
		return FALSE;
	}
	ImageOperating.image.x = GAME_WIDTH / 2 - ImageOperating.image.x / 2;
	ImageOperating.image.y = GAME_HEIGHT / 2 - ImageOperating.image.y / 2;
	ImageOperating.angle = 0;
	ImageOperating.rate = IMAGE_OPERATING_ROTA;

	//プレイヤー画像
	int playerRes = LoadDivGraph(
		IMAGE_PLAYER_PATH,
		PLAYER_DIV_NUM, PLAYER_DIV_YOKO, PLAYER_DIV_TATE,
		PLAYER_WIDTH, PLAYER_HEIGHT,
		player.handle);

	if (playerRes == ERR) {
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	player.x = GAME_WIDTH / 2 - player.x / 2;
	player.y = GAME_HEIGHT / 2 - player.y / 2;
	player.speed = 1;
	player.angle = 0;
	player.changeImageCnt = PLAYER_RIGHT_STAY;
	player.ChangeImageCntMax = PLAYER_RIGHT_STAY;
	player.rate = PLAYER_ROTA;


	GetGraphSize(player.handle[0], &player.width, &player.height);

	return TRUE;
}

VOID MY_DELETE_IMAGE(VOID) {
	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleRogo.image.handle);
	DeleteGraph(ImageTitleStart.image.handle);
	DeleteGraph(ImageOperating.image.handle);
	for (int cnt = 0; cnt < PLAYER_DIV_NUM; cnt++) { DeleteGraph(player.handle[cnt]); }
	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }
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

	strcpy_s(musicPlay.path, MUSIC_PLAY_PATH);
	musicPlay.handle = LoadSoundMem(musicPlay.path);
	if (musicPlay.handle == ERR) {
		MessageBox(GetMainWindowHandle(), MUSIC_PLAY_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

VOID MY_DELETE_MUSIC(VOID) {
	DeleteSoundMem(musicStart.handle);
	DeleteSoundMem(musicPlay.handle);
}

/*----------冒頭テキスト表示----------*/
VOID FIRST_FONT_DRAW() {
	//背景
	DrawGraph(0, 0, ImageTitleBK.handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(fontX - 10, fontY - 10, GAME_WIDTH / 2 + 400, GAME_HEIGHT / 2 + 150, GetColor(200, 200, 200), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawString(GAME_WIDTH - 100, GAME_HEIGHT - 50, "Enter→", FONT_COLOR_WHITE);

	switch (fontNum)
	{
	case 1:
		DrawString(fontX, fontY, "ギルドから依頼が届きました！", FONT_COLOR_BLACK);
		break;
	case 2:
		DrawString(fontX, fontY, "とあるものを取ってきてほしい、という依頼が届いた。\n厄介なことになぞなぞになっていて、\n依頼の品が何なのかわからない状態だ。", FONT_COLOR_BLACK);
		break;
	case 3:
		DrawString(fontX, fontY, "そこで、あなたには謎を解き指定されたものを届けてほしい。\n聡明なあなたならできるはずだ。", FONT_COLOR_BLACK);
		break;
	case 4:
		DrawString(fontX, fontY, "届いた謎は・・・", FONT_COLOR_BLACK);
		break;
	case 5:
		DrawString(fontX, fontY, """緑と黒の柄をもつ。\n割ると、中から赤い身が飛び散る。\n水に関係しているとか…。""", FONT_COLOR_RED);
		break;
	case 6:
		DrawString(fontX, fontY, "難しいかもしれないが頼んだぞ！", FONT_COLOR_BLACK);
		break;

	case 7:
		OPERATING_DRAW();
		DrawString(GAME_WIDTH - 100, GAME_HEIGHT -50, "Enter→", FONT_COLOR_WHITE);
		break;
	default:
		break;
	}
}

/*----------操作説明----------*/
VOID OPERATING_DRAW() {
	DrawRotaGraph(
		ImageOperating.image.x,
		ImageOperating.image.y,
		ImageOperating.rate,
		ImageOperating.angle,
		ImageOperating.image.handle,
		TRUE);
}

/*--------MAP---------*/
BOOL MY_LOAD_MAPCHIP(VOID)
{
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,
		MAP_DIV_NUM, MAP_DIV_YOKO, MAP_DIV_TATE,
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
		&mapChip.handle[0]);

	if (mapRes == -1) {
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK); 
		return FALSE;
	}

	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	return TRUE;
}

BOOL MY_LOAD_CSV_MAP(const char* path, MAP* m, MAP* mInit)
{
	FILE* fp;

	if ((fp = fopen(path,"r")) == NULL) {
		return FALSE;
	}

	int result = 0;
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++) {
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++) {
			MAP* p = m + tate * GAME_MAP_YOKO_MAX + yoko;

			result = fscanf(fp, "%d,", &p->value);

			if (result == EOF) { break; }
		}
		if (result == EOF) { break; }
	}

	fclose(fp);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++) {
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++) {
			MAP* p = m + tate * GAME_MAP_YOKO_MAX + yoko;
			MAP* pInit = mInit + tate * GAME_MAP_YOKO_MAX + yoko;

			p->kind = MAP_KIND_TURO;

			for (int cnt = 0; cnt < MAP_KABE_KIND; cnt++) {
				if (p->value == MapKabeID[cnt]) {
					p->kind = MAP_KIND_KABE;
					break;
				}
			}

			for (int cnt = 0; cnt < MAP_GUILD_KIND; cnt++) {
				if (p->value == MapGuildID[cnt]) {
					p->kind = MAP_KIND_GUILD;
					break;
				}
			}

			if (p->value == MapKanbanID)
			{
				p->kind = MAP_KIND_KANBAN;
			}

			//マップ位置処理
			p->x = yoko * MAP_DIV_WIDTH;
			p->y = tate * MAP_DIV_HEIGHT;
			p->width = MAP_DIV_WIDTH;
			p->height = MAP_DIV_HEIGHT;

			//マップの当たり判定の処理
			p->coll.left = p->x + 1;
			p->coll.top = p->y + 1;
			p->coll.right = p->coll.left + p->width - 1;
			p->coll.bottom = p->coll.top + p->height - 1;

			pInit = p;
		}
	}

	return TRUE;

}

VOID MY_CHECK_MAP_DOWN(CHARA* c) {
	int charaX_L = (c->mapX) / MAP_DIV_WIDTH;
	int charaX_R = (c->mapY + c->width) / MAP_DIV_WIDTH;
	int charaY = (c->mapY + c->height) / MAP_DIV_HEIGHT;

	if (charaX_L < 0) { charaX_L = 0; }
	if (charaX_R >= GAME_MAP_YOKO_MAX) { charaX_R = GAME_MAP_YOKO_MAX - 1; }

	if (map_jimen[charaY][charaX_L].kind == MAP_KIND_KABE || map_jimen[charaY][charaX_R].kind == MAP_KIND_KABE) {
		while (map_jimen[charaY][charaX_L].kind==MAP_KIND_KABE||map_jimen[charaY][charaX_R].kind==MAP_KIND_KABE)
		{
			c->y--;

			c->mapY--;

			charaY = (c->mapY + c->height) / MAP_DIV_HEIGHT;
		}
		
	}
	return;
}

//デバック用RECTを利用して四角を描画
void DrawBoxRect(RECT r, unsigned int color, bool b)
{
	//引数を基に描画
	DrawBox(r.left, r.top, r.right, r.bottom, color, b);
	return;
}
