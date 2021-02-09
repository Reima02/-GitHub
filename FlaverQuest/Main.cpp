/*----------ヘッダーファイル----------*/
#include "DxLib.h"
#include "game.h"
#include "mapChip.h"
#include "resource.h"

/*----------マクロ定義----------*/
#define GAME_WIDTH	1024	//画面の横の大きさ
#define GAME_HEIGHT	576		//画面の縦の大きさ
#define GAME_COLOR	32		//画面のカラービット

#define GAME_WINDOW_BAR		0				//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"Flavor Quest"	//ウィンドウのタイトル

#define ERR		-1	//-1をエラー

//FPS設定
#define GAME_FPS			60	//FPSの数値	

//プレイヤー画像
#define PLAYER_CHANGE_NUM	3	//プレイヤー画像変更回数
#define PLAYER_WIDTH		32	//プレイヤー画像横
#define PLAYER_HEIGHT		32	//プレイヤー画像縦
#define PLAYER_DIV_TATE		4	//プレイヤー画像縦分割数
#define	PLAYER_DIV_YOKO		3	//プレイヤー画像横分割数
#define PLAYER_DIV_NUM		PLAYER_DIV_TATE*PLAYER_DIV_YOKO		//プレイヤー画像総分割数
#define PLAYER_ROTA			2.0	//プレイヤー拡大率
#define PLAYER_ACTWAIT		100	//プレイヤーアニメーション待ち時間
#define PLAYER_LEFT			3	//左向き
#define PLAYER_LEFT_MAX		5	//左最大
#define PLAYER_RIGHT		6	//右向き
#define	PLAYER_RIGHT_MAX	8	//右最大
#define PLAYER_BACK			9	//後ろ向き
#define PLAYER_BACK_MAX		11	//後ろ最大
#define PLAYER_RIGHT_STAY	7	//右向き待ち
#define PLAYER_LEFT_STAY	4	//左向き待ち
//画像	
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")			//画像読み込みエラーメッセージ
#define IMAGE_TITLE_BK_PATH		TEXT(".\\IMAGE\\TitleBack.png")		//タイトル背景のパス
#define IMAGE_TITLE_ROGO_PATH	TEXT(".\\IMAGE\\titlerogo.png")		//タイトルロゴのパス
#define	IMAGE_TITLE_ROGO_ROTA	0.25								//タイトルロゴ拡大率
#define IMAGE_TITLE_START_PATH	TEXT(".\\IMAGE\\title_start.png")	//タイトルスタートの画像
#define IMAGE_TITLE_START_ROTA	0.8									//スタート拡大率
#define IMAGE_OPERATING_PATH	TEXT(".\\IMAGE\\sousasetumei.png")	//操作説明画像
#define IMAGE_OPERATING_ROTA	2.15
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\player.png")		//プレイヤー画像パス
#define IMAGE_END_BK_PATH		TEXT(".\\IMAGE\\guild_back.jpg")	//エンド画面背景パス
#define IMAGE_END_CLEAR_ROGO_PATH	TEXT(".\\IMAGE\\GameClear.png")	//エンド画面クリアロゴ
#define IMAGE_END_FAILED_PATH	TEXT(".\\IMAGE\\MissionFailed.png")	//エンド画面　ミッション失敗
#define IMAGE_MERON_PATH		TEXT(".\\IMAGE\\meron.png")			//メロンパス
#define IMAGE_SUICA_PATH		TEXT(".\\IMAGE\\suica.png")			//スイカパス

//音楽（ＢＧＭ）
#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")		//音楽読み込みエラーメッセージ
#define MUSIC_START_PATH		TEXT(".\\MUSIC\\start.mp3")		//タイトルBGM
#define MUSIC_PLAY_PATH			TEXT(".\\MUSIC\\play.mp3")		//プレイBGM
#define MUSIC_END_CLEAR_PATH	TEXT(".\\MUSIC\\clear.mp3")		//クリア画面ＢＧＭ
#define MUSIC_END_OVER_PATH		TEXT(".\\MUSIC\\over.mp3")		//ゲームオーバー画面ＢＧＭ
#define MUSIC_END_FAILED_PATH	TEXT(".\\MUSIC\\failed.mp3")	//アイテムが違う時ＢＧＭ

//音楽効果音
#define MUSIC_ITEM_SELECT_PATH	TEXT(".\\MUSIC\\item_select.mp3")	//アイテムを選択するときの効果音
#define MUSIC_SELECT_PATH		TEXT(".\\MUSIC\\select.mp3")		//フォントが進む時の効果音
#define MUSIC_RUN_PATH			TEXT(".\\MUSIC\\run.mp3")			//プレイヤーが走るときの効果音

//色
#define FONT_COLOR_BLACK	GetColor(0,0,0)			//色：黒
#define FONT_COLOR_RED		GetColor(255,0,0)		//色：赤
#define FONT_COLOR_WHITE	GetColor(255,255,255)	//色：白
#define FONT_COLOR_BLUE		GetColor(0,0,255)		//色：青

#define MAP_GAME_TATE	GAME_HEIGHT/MAP_DIV_HEIGHT
#define MAP_GAME_YOKO	GAME_WIDTH/MAP_DIV_WIDTH

//フォント
#define FONT_PATH		TEXT(".\\FONT\\smartphone.otf")	//スマートフォンフォントのパス
#define FONT_NAME		TEXT("03スマートフォンUI")		//フォント名

#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")	//エラーメッセージ
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")	//エラーメッセージ

/*----------プロトタイプ宣言----------*/
//スタート画面
VOID MY_START_INIT(VOID);	//スタート画面初期化
VOID MY_START(VOID);		//スタート画面
VOID MY_START_PROC(VOID);	//スタート画面の処理
VOID MY_START_DRAW(VOID);	//スタート画面の描画

//プレイ画面
VOID MY_PLAY_INIT(VOID);	//プレイ画面初期化
VOID MY_PLAY(VOID);			//プレイ画面
VOID MY_PLAY_PROC(VOID);	//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);	//プレイ画面の描画
VOID MY_FIRST_FONT_DRAW(VOID);	//冒頭テキスト表示
VOID MY_OPERATING_DRAW(VOID);	//操作方法表示
VOID MY_PLAYER_SETTING(VOID);	//プレイヤー設定（PROC内）　モーション切り替えなど
VOID MY_ITEM_TEXT_DRAW(VOID);	//アイテム選択テキスト表示
VOID MY_PROCESS_GOAL(VOID);	//ゴールの処理
VOID MY_MOVESET_DOWN_MAP(VOID);	//マップ下端
VOID MY_MOVE_DOWN_BOTTOM_PLAYER(VOID);	//マップが下端に行ったときにプレイヤーを動かす
VOID MY_TRANS_END(VOID);	//エンド画面への遷移

//エンド画面
VOID MY_END_INIT(VOID);		//エンド画面初期化
VOID MY_END(VOID);			//エンド画面
VOID MY_END_PROC(VOID);		//エンド画面の処理
VOID MY_END_DRAW(VOID);		//エンド画面の描画
VOID MY_END_TYPE(VOID);		//エンド画面種類
VOID MY_CLEAR_PROC(VOID);	//クリア画面の処理
VOID MY_OVER_PROC(VOID);	//ゲームオーバー画面の処理
VOID MY_MISS_PROC(VOID);	//違うアイテムを持ってきたときの処理

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

//フォント
BOOL MY_FONT_INSTALL_ONCE(VOID);	//フォントをこのソフト用に、一時的にインストール
VOID MY_FONT_UNINSTALL_ONCE(VOID);	//フォントをこのソフト用に、一時的にアンインストール
BOOL MY_FONT_CREATE(VOID);			//フォントを作成する
VOID MY_FONT_DELETE(VOID);			//フォントを削除する

//当たり判定
BOOL MY_CHECK_RECT_COLL(RECT, RECT);
VOID MY_CHECK_DOWN(int, int);		//当たり判定（下）
VOID MY_CHECK_RIGHT(int, int);		//当たり判定（右）
VOID MY_CHECK_LEFT(int, int);		//当たり判定（左）
VOID MY_CHECK_TOP(int, int);		//当たり判定（上）
VOID MY_CHECK_MAP(int, int);		//当たり判定（プレイヤー周辺）

//重力を下に動かす
VOID MY_MAP_DOWN(VOID);

//プレイヤー移動
VOID MY_MOVE_PLAYER(VOID);

//アイテム取得
VOID MY_SELECT_ITEM(VOID);

//デバック用
VOID MY_DRAW_BOX_REXT(RECT, unsigned int, bool);

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
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
	int nowImageKind;			//現在のキャラクター状態
	int changeImageCnt;			//変更したい画像		[0]～[2]：正面　[3]～[5]左	[6]～[8]右	[9]～[11]：背面
	int ChangeImageCntMax;		//変更したい画像ラスト	例：正面→2		左→5
	int keyState;				//キーボード何が押されているか
	int keyStateMax;			
	int speed;					//スピード
	double angle;				//回転率
	double rate;				//拡大率

	RECT coll;					//全体の当たり判定
	RECT collTop;				//上の当たり判定
	RECT collBottom;			//下の当たり判定
	RECT collRightHead;			//右側頭の当たり判定
	RECT collRightBody;			//右側体の当たり判定
	RECT collLeftHead;			//左側頭の当たり判定
	RECT collLeftBody;			//左側体の当たり判定

}CHARA;	//キャラクター構造体


//音楽構造体
typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
}MUSIC;

//フォント構造体
typedef struct STRUCT_FONT
{
	char path[PATH_MAX];	//フォントパス格納
	char name[MAX_PATH];	//フォント名格納
	int handle;				
	int size;
	int bold;
	int type;
}FONT;

//ゴールタイプ
enum goalType
{
	Clear,	//クリア(アイテムがあっているとき)
	Miss,	//ミッション失敗（アイテムが間違っているとき）
	Over,	//ゲームオーバー（落下したとき）
};

//ゴールタイプ
goalType goal_type;

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
IMAGE imageTitleBK;					//タイトル背景
IMAGE_ROTA imageOperating;			//操作説明
IMAGE_ROTA imageTitleRogo;			//タイトルロゴ
IMAGE_ROTA imageTitleStart;			//タイトルスタートの画像
IMAGE imageEndBk;					//エンド画面背景
IMAGE_ROTA imageEndClearRogo;		//クリアロゴ
IMAGE_ROTA imageEndMissionFailed;	//ミッション失敗
IMAGE_ROTA imageSuica;				//スイカ
IMAGE_ROTA imageMeron;				//メロン

//音楽
MUSIC musicStart;		//スタート画面の音楽
MUSIC musicPlay;		//プレイ画面の音楽
MUSIC musicEndClear;	//クリア画面の音楽
MUSIC musicEndOver;		//ゲームオーバー画面の音楽
MUSIC musicEndFailed;	//アイテムが違う時の音楽
MUSIC musicRun;			//走る効果音
MUSIC musicItemSelect;	//アイテム選択時の効果音
MUSIC musicSelect;		//テキストを進めるときなどの効果音	

//フォント
FONT fontSmart;	

//冒頭
int	fontNum = 1;			//テキストのナンバー
BOOL inGameMain = FALSE;	//判定：ゲーム本編
BOOL isFontNext = TRUE;		//判定：冒頭テキスト次に進む

//プレイヤー
CHARA player;
int playerState = 0;		//アニメーションの状態

//MAP
MAP_CHIP mapChip;	//マップチップ(画像)

MAP map_jimen[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];		//地面
MAP mapInit_jimen[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];	//地面

MAP map_sora[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];			//空
MAP mapInit_sora[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];		//空

MAP map_sousyoku[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];		//装飾
MAP mapInit_sousyoku[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];	//装飾

int mapInitY = 32 * 15;										//マップ初期位置設定Ｙ軸

//ＩＤ管理
int MapJimenID[MAP_JIMEN_KIND] = { 10,11,42,43 };			//地面ＩＤ
int MapGuildID[MAP_GUILD_KIND] = { 202,203,234,235 };		//ギルドＩＤ
int MapKanbanID = 257;										//看板ＩＤ

//マップ動かす
BOOL isMoveMapYoko = FALSE;	//左横移動可能なとき
BOOL isMoveMapYoko2 = TRUE;	//右移動可能なとき
BOOL isDownMap = TRUE;		//重力で落ちていくかどうか
BOOL isMoveMapLeft = TRUE;	//マップ左移動
BOOL isMoveMapRight = TRUE;	//マップ右移動
BOOL isJump = FALSE;		//ジャンプ可能かどうか
BOOL isJumpNow = FALSE;		//ジャンプ中かどうか
int jumpCnt = 0;			//滞空時間を数えるためのＣｏｕｎｔ
int jumpCntMax = 50;		//滞空時間の最大時間
int jumpSpeed = 2;			//ジャンプのスピード
BOOL isNotMapDown = FALSE;	//マップを下に動かすかどうか	T:止める	F:動かす

//プレイヤーを動かす
BOOL isMovePlayerX = TRUE;
BOOL isMovePlayerRight = TRUE;
BOOL isMovePlayerLeft = TRUE;

//プレイヤーと看板
BOOL isSelectKanban = FALSE;	//アイテム選択看板に触れているか	T:触れている　F:触れていない
BOOL isCheckItem = TRUE;		//アイテムを選択画面で選択したか	T:アイテムを選択した	F:選択しない

//プレイヤーとギルド
BOOL isCheckGoal = FALSE;

//エンド画面からスタート画面へ
BOOL isMoveStart = FALSE;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);		//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));	//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);						//非アクティブでも実行する
	SetMouseDispFlag(FALSE);					//マウスカーソル非表示

	SetWindowIconID(IDI_ICON1);

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	int DrawX = 0;	//表示位置X
	int DrawY = 0;	//表示位置Y

	//画像読み込み
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//音楽読み込み
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	//フォントを一時的にインストール
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }

	//フォントハンドルを作成
	if (MY_FONT_CREATE() == FALSE) { return -1; }

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
		//MY_FPS_DRAW();
		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画
		MY_FPS_WAIT();		//FPSの処理[待つ]
	}

	//画像ハンドルを破棄
	MY_DELETE_IMAGE();

	//音楽削除
	MY_DELETE_MUSIC();

	//フォントハンドルを破棄
	MY_FONT_DELETE();

	//一時的にインストールしたフォントをアンインストール
	MY_FONT_UNINSTALL_ONCE();

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

	//タイトルロゴを移動させる
	if (imageTitleRogo.image.y <= GAME_HEIGHT / 2 - imageTitleRogo.image.height / 2 - 50)
	{
		imageTitleRogo.image.y += 2;
	}

	//エンターキーを押したら、プレイシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		//タイトルロゴを中央へ持ってくる
		imageTitleRogo.image.y = GAME_HEIGHT / 2 - imageTitleRogo.image.height / 2;

		//BGM停止
		if (CheckSoundMem(musicStart.handle) != 0) 
		{
			StopSoundMem(musicStart.handle);
		}

		if (CheckSoundMem(musicItemSelect.handle) == 0) {
			PlaySoundMem(musicItemSelect.handle, DX_PLAYTYPE_NORMAL);
		}

		MY_PLAY_INIT();	//プレイ画面初期化
		GameScene = GAME_SCENE_PLAY;
	}

	return;
}

//スタート画面の描画
VOID MY_START_DRAW(VOID)
{
	//背景
	DrawGraph(0, 0, imageTitleBK.handle, TRUE);

	//ロゴ
	DrawRotaGraph(
		imageTitleRogo.image.x,
		imageTitleRogo.image.y,
		imageTitleRogo.rate,
		imageTitleRogo.angle,
		imageTitleRogo.image.handle,
		TRUE
	);

	//スタート表示
	DrawRotaGraph(
		imageTitleStart.image.x,
		imageTitleStart.image.y,
		imageTitleStart.rate,
		imageTitleStart.angle,
		imageTitleStart.image.handle,
		TRUE);

	//DrawString(0, 0, "スタート画面", GetColor(255, 255, 255));

	return;
}

//プレイ画面初期化
VOID MY_PLAY_INIT()
{
	//プレイヤーを初期位置に戻す
	player.x = GAME_WIDTH / 10;
	player.y = GAME_HEIGHT / 2;
	player.changeImageCnt = PLAYER_RIGHT_STAY;
	player.ChangeImageCntMax = PLAYER_RIGHT_STAY;

	//マップを初期位置に戻す
	MY_LOAD_CSV_MAP(GAME_CSV_PATH_MAP1_SORA, &map_sora[0][0], &mapInit_sora[0][0]);
	MY_LOAD_CSV_MAP(GAME_CSV_PATH_MAP1_JIMEN, &map_jimen[0][0], &mapInit_jimen[0][0]);
	MY_LOAD_CSV_MAP(GAME_CSV_PATH_MAP1_SOUSHOKU, &map_sousyoku[0][0], &mapInit_sousyoku[0][0]);


	//マップを動かすかのトリガーの初期化
	isMoveMapYoko = FALSE;	//横移動可能なとき
	isDownMap = TRUE;	//重力で落ちていくかどうか
	isMoveMapLeft = TRUE;
	isMoveMapRight = TRUE;

	//マップＹ軸調整 -mapInitだけ移動させた状態でスタートする
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
		{
			//マップ移動
			map_sora[tate][yoko].y -= mapInitY;
			map_jimen[tate][yoko].y -= mapInitY;
			map_sousyoku[tate][yoko].y -= mapInitY;

			//当たり判定移動
			map_jimen[tate][yoko].coll.top -= mapInitY;
			map_jimen[tate][yoko].coll.bottom -= mapInitY;
		}
	}

	//プレイヤーを動かすトリガーの初期化
	isMovePlayerRight = TRUE;
	isMovePlayerLeft = TRUE;
	isNotMapDown = FALSE;

	//冒頭テキストをはじめから
	fontNum = 1;

	//テキストから始めるようにする
	inGameMain = FALSE;

	//ゴールにあたっているかを判定
	isCheckGoal = FALSE;

	isSelectKanban = FALSE;	//アイテム選択看板に触れているか	T:触れている　F:触れていない
	isCheckItem = TRUE;		//アイテムを選択画面で選択したか	T:アイテムを選択した	F:選択しない

	//ゴールの判定をもどす
	goal_type = Over;
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
			//効果音を鳴らす
			if (CheckSoundMem(musicSelect.handle) == 0) {
				PlaySoundMem(musicSelect.handle, DX_PLAYTYPE_NORMAL);
			}

			//テキストを進める
			if (isFontNext) {
				++fontNum;
				if (fontNum >= 10) {
					inGameMain = TRUE;
				}
			}
			isFontNext = false;
		}

		//連続で進まないように
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

		//当たり判定(計算)
		//全体
		player.coll.left = player.x - player.width / 2;
		player.coll.top = player.y - player.height;
		player.coll.right = player.coll.left + player.width;
		player.coll.bottom = player.coll.top + player.height * 2;

		//プレイヤー上
		player.collTop.left = player.x - player.width / 2 + 5;
		player.collTop.top = player.y - player.height;
		player.collTop.right = player.collTop.left + player.width - 10;
		player.collTop.bottom = player.collTop.top + player.height / 2;

		//プレイヤー下
		player.collBottom.left = player.x - player.width / 2 + 5;
		player.collBottom.top = player.y + player.height / 2;
		player.collBottom.right = player.collBottom.left + player.width / 2;
		player.collBottom.bottom = player.collBottom.top + player.height / 2;

		//プレイヤー右（頭）
		player.collRightHead.left = player.collRightHead.right - player.width / 2;
		player.collRightHead.top = player.y - player.height + 5;
		player.collRightHead.right = player.x + player.width / 2;
		player.collRightHead.bottom = player.collRightHead.top + player.height - 5;

		//プレイヤー右（体）
		player.collRightBody.left = player.collRightBody.right - player.width / 2;
		player.collRightBody.top = player.y;
		player.collRightBody.right = player.x + player.width / 2;
		player.collRightBody.bottom = player.collRightBody.top + player.height - 5;

		//プレイヤー左（頭）
		player.collLeftHead.left = player.x - player.width / 2 - player. width / 2;
		player.collLeftHead.top = player.y - player.height + 5;
		player.collLeftHead.right = player.collLeftHead.left + player.width / 2;
		player.collLeftHead.bottom = player.collLeftHead.top + player.height - 5;

		//プレイヤー左（体)
		player.collLeftBody.left = player.x - player.width / 2;
		player.collLeftBody.top = player.y;
		player.collLeftBody.right = player.collLeftBody.left + player.width / 2;
		player.collLeftBody.bottom = player.collLeftBody.top + player.height - 5;

		//プレイヤー移動準備関数
		if (isSelectKanban && isCheckItem)
		{
			MY_SELECT_ITEM();	//アイテム選択　１：正解　２：不正解
		}

		else
		{
			//プレイヤー設定
			MY_PLAYER_SETTING();

			//プレイヤーを動かす
			MY_MOVE_PLAYER();

			//マップが一番下に入った
			MY_MOVESET_DOWN_MAP();
		}

		//ゴールの処理
		MY_PROCESS_GOAL();

		//デバック用　： スペースキーを押したら、エンドシーンへ移動する
		//if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
		//{
		//	//BGM停止
		//	if (CheckSoundMem(musicPlay.handle) != 0) {
		//		StopSoundMem(musicPlay.handle);
		//	}

		//	//エンド画面へ遷移
		//	GameScene = GAME_SCENE_END;
		//}
	}

	return;
}

//マップ下まで行った時の処理
VOID MY_MOVESET_DOWN_MAP(VOID)
{
	if (map_jimen[GAME_MAP_TATE_MAX - 1] -> y <= GAME_HEIGHT)
	{
		DrawBox(10, 10, 20, 20, GetColor(0, 255, 255), TRUE);
		isNotMapDown = TRUE;
	}

	if (isNotMapDown)
	{
		MY_MOVE_DOWN_BOTTOM_PLAYER();
	}
}

//落下したとき画面下端までプレイヤーを移動する
VOID MY_MOVE_DOWN_BOTTOM_PLAYER()
{
	player.y += player.speed;
	//落下したときゲームオーバーへ
	if (player.y >= GAME_HEIGHT)
	{
		goal_type = Over;
		MY_TRANS_END();
	}
}


//ゴールの処理をする関数
VOID MY_PROCESS_GOAL(VOID)
{
	if (isCheckGoal)
	{
		MY_TRANS_END();
	}
}

VOID MY_TRANS_END(VOID)
{
	//BGM停止
	if (CheckSoundMem(musicPlay.handle) != 0) {
		StopSoundMem(musicPlay.handle);
	}

	//BGM停止
	if (CheckSoundMem(musicRun.handle) != 0)
	{
		StopSoundMem(musicRun.handle);
	}

	MY_END_INIT();	//エンド画面初期化

	//エンド画面へ遷移
	GameScene = GAME_SCENE_END;
}

//アイテムを選択する関数
VOID MY_SELECT_ITEM(VOID)
{
	if (MY_KEY_DOWN(KEY_INPUT_1))
	{
		//効果音を鳴らす
		if (CheckSoundMem(musicItemSelect.handle) == 0) {
			PlaySoundMem(musicItemSelect.handle, DX_PLAYTYPE_NORMAL);
		}

		isSelectKanban = FALSE;
		isCheckItem = FALSE;
		goal_type = Clear;
	}

	else if (MY_KEY_DOWN(KEY_INPUT_2))
	{
		//効果音を鳴らす
		if (CheckSoundMem(musicItemSelect.handle) == 0) {
			PlaySoundMem(musicItemSelect.handle, DX_PLAYTYPE_NORMAL);
		}

		isSelectKanban = FALSE;
		isCheckItem = FALSE;
		goal_type = Miss;
	}
}

//当たり判定（プレイヤー周辺）　引数：マップ配列の添え字
VOID MY_CHECK_MAP(int tate, int yoko)
{
	//当たり判定　プレイヤー：看板
	if (MY_CHECK_RECT_COLL(player.coll, map_jimen[tate][yoko].coll) == TRUE && map_jimen[tate][yoko].kind == MAP_KIND_KANBAN)
	{
		isSelectKanban = TRUE;
	}

	//当たり判定　プレイヤー：ギルド
	if (MY_CHECK_RECT_COLL(player.coll, map_jimen[tate][yoko].coll) == TRUE && map_jimen[tate][yoko].kind == MAP_KIND_GUILD)
	{
		isCheckGoal = TRUE;
	}
}

//当たり判定（下）　引数：マップ配列の添え字
VOID MY_CHECK_DOWN(int tate, int yoko)
{
	//当たり判定下
	if (MY_CHECK_RECT_COLL(player.collBottom, map_jimen[tate][yoko].coll) == TRUE && map_jimen[tate][yoko].kind == MAP_KIND_KABE)
	{
		//着地判定がTRUEの時マップを動かさない
		isDownMap = FALSE;
		isJump = TRUE;
		jumpCnt = 0;
	}
	//着地してないとき重力を加える（マップを下に動かす）
	else if (map_jimen[tate][yoko].kind != MAP_JIMEN_KIND && MY_CHECK_RECT_COLL(player.collBottom, map_jimen[tate][yoko].coll) == TRUE) {
		isDownMap = TRUE;
		isJump = FALSE;
	}
}

//当たり判定（上）　引数：マップ配列の添え字
VOID MY_CHECK_TOP(int tate, int yoko)
{
	if (MY_CHECK_RECT_COLL(player.collTop, map_jimen[tate][yoko].coll) == TRUE && map_jimen[tate][yoko].kind == MAP_KIND_KABE)
	{
		isJump = FALSE;
		isJumpNow = FALSE;
	}
}

//当たり判定（右）　引数：マップ配列の添え字
VOID MY_CHECK_RIGHT(int tate, int yoko)
{
	if (MY_CHECK_RECT_COLL(player.collRightHead, map_jimen[tate][yoko].coll) == TRUE && map_jimen[tate][yoko].kind == MAP_KIND_KABE
		|| MY_CHECK_RECT_COLL(player.collRightBody, map_jimen[tate][yoko].coll) == TRUE && map_jimen[tate][yoko].kind == MAP_KIND_KABE
		)
	{
		isMoveMapRight = FALSE;
		isMovePlayerRight = FALSE;
	}
	else if (map_jimen[tate][yoko].kind != MAP_JIMEN_KIND && MY_CHECK_RECT_COLL(player.collRightHead, map_jimen[tate][yoko].coll) == TRUE) {
		isMoveMapRight = TRUE;
		isMovePlayerRight = TRUE;
	}
}

//当たり判定（左）　引数：マップ配列の添え字
VOID MY_CHECK_LEFT(int tate, int yoko)
{
	if (MY_CHECK_RECT_COLL(player.collLeftHead, map_jimen[tate][yoko].coll) == TRUE && map_jimen[tate][yoko].kind == MAP_KIND_KABE
		|| MY_CHECK_RECT_COLL(player.collLeftBody, map_jimen[tate][yoko].coll) == TRUE && map_jimen[tate][yoko].kind == MAP_KIND_KABE
		)
	{
		isMoveMapLeft = FALSE;
		isMovePlayerLeft = FALSE;
	}
	else if (map_jimen[tate][yoko].kind != MAP_JIMEN_KIND && MY_CHECK_RECT_COLL(player.collLeftHead, map_jimen[tate][yoko].coll) == TRUE) {
		isMoveMapLeft = TRUE;
		isMovePlayerLeft = TRUE;
	}
}

/*----------プレイヤー設定----------*/
VOID MY_PLAYER_SETTING()
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

//プレイヤー移動準備
VOID MY_MOVE_PLAYER(VOID)
{
	//当たり判定処理
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
		{
			MY_CHECK_MAP(tate, yoko);	//キャラクター：マップ　（キャラクター周辺）
			MY_CHECK_TOP(tate, yoko);	//キャラクター：マップ　（上）
			MY_CHECK_DOWN(tate, yoko);	//キャラクター：マップ　（下）
			MY_CHECK_RIGHT(tate, yoko);	//キャラクター：マップ　（右）
			MY_CHECK_LEFT(tate, yoko);	//キャラクター：マップ　（左）
		}
	}

	//効果音(走る)
	if (MY_KEY_DOWN(KEY_INPUT_A) || MY_KEY_DOWN(KEY_INPUT_D))
	{
		if (CheckSoundMem(musicRun.handle) == 0) {					//正しく読み取れていたら
			PlaySoundMem(musicRun.handle, DX_PLAYTYPE_LOOP);			//再生
		}
	}
	
	if(!isJump)
	{
		//BGM停止
		if (CheckSoundMem(musicRun.handle) != 0)
		{
			StopSoundMem(musicRun.handle);
		}
	}

	if (isMoveMapYoko && isMoveMapYoko2)
	{
		//左入力
		if (MY_KEY_DOWN(KEY_INPUT_A))
		{
			//左に行けるとき
			if (isMoveMapLeft) {
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
		if (MY_KEY_DOWN(KEY_INPUT_D))
		{
			//右に動かせるとき
			if (isMoveMapRight)
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
		//画面端にいったらキャラクターが動くように切り替える
		if (map_jimen[0]->x >= 0)
		{
			isMoveMapYoko = FALSE;
		}

		if (map_jimen[0][GAME_MAP_YOKO_MAX - 1].x <= GAME_WIDTH - player.width )
		{
			isMoveMapYoko2 = FALSE;
		}
	}



	//キャラクターを端まで動かす
	else
	{
		if (player.x >= player.width)	//画面端までいったら左に行くことを止める
		{
			if (MY_KEY_DOWN(KEY_INPUT_A))
			{
				if (isMovePlayerLeft)
				{
					//プレイヤーを移動する (左)
					player.x -= player.speed;

					//当たり判定移動
					player.coll.left -= player.speed;
					player.coll.right -= player.speed;
				}
			}
		}

		if (player.x <= GAME_WIDTH - player.width)	//画面端までいったら右に行くことを止める
		{
			//右入力
			if (MY_KEY_DOWN(KEY_INPUT_D))
			{
				if (isMovePlayerRight) {
					//プレイヤーを移動する
					player.x += player.speed;

					//当たり判定移動
					player.coll.left += player.speed;
					player.coll.right += player.speed;
				}
			}
		}

		if (player.x == GAME_WIDTH / 2 - player.width / 2)
		{
			isMoveMapYoko = TRUE;
			isMoveMapYoko2 = TRUE;
		}

	}

	//ジャンプ処理
	if (MY_KEY_DOWN(KEY_INPUT_SPACE))
	{
		if (isJump || isJumpNow) {
			isJump = FALSE;
			isJumpNow = TRUE;

			jumpCnt++;
			for (int tate = 0; tate < GAME_MAP_TATE_MAX; ++tate)
			{
				for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; ++yoko)
				{
					//マップ移動
					map_sora[tate][yoko].y += jumpSpeed;
					map_jimen[tate][yoko].y += jumpSpeed;
					map_sousyoku[tate][yoko].y += jumpSpeed;

					//当たり判定移動
					map_jimen[tate][yoko].coll.top += jumpSpeed;
					map_jimen[tate][yoko].coll.bottom += jumpSpeed;
				}
			}

			if (jumpCnt >= jumpCntMax)
			{
				isJump = FALSE;
				isJumpNow = FALSE;
			}
		}
	}

	else if (MY_KEY_UP(KEY_INPUT_SPACE))
	{
		isJumpNow = FALSE;
	}

	if (isJumpNow)
	{
		isDownMap = FALSE;
	}

	//TRUEの時マップを下に動かす
	if (isDownMap && !isNotMapDown)
	{
		MY_MAP_DOWN();
	}
}



//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	//冒頭部分
	if (!inGameMain) {
		MY_FIRST_FONT_DRAW();		//関数：冒頭テキスト表示
	}

	//メイン部分
	else 
	{
		//MAP表示
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
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

		//プレイヤーの状態を変化
		if (player.changeImageCnt < player.ChangeImageCntMax) {
			++player.changeImageCnt;
			player.nowImageKind = player.changeImageCnt;
		}
		else {
			player.nowImageKind = player.keyState;
			player.changeImageCnt = player.keyState;
		}

		//アイテム選択を表示
		if (isSelectKanban && isCheckItem)
		{
			MY_ITEM_TEXT_DRAW();
		}

		//獲得アイテムの表示
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);	//表示を半透明にする
		DrawBox(GAME_WIDTH - 100, 0, GAME_WIDTH, 100, GetColor(128, 128, 128), TRUE);	//UI表示場所にマスクをかける
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);	//表示を不透明に戻す
		 
		if (goal_type == Clear)
		{
			//スイカを表示
			DrawRotaGraph(
				imageSuica.image.x,
				imageSuica.image.y,
				imageSuica.rate,
				imageSuica.angle,
				imageSuica.image.handle,
				TRUE
			);
		}

		else if (goal_type == Miss)
		{
			//メロンを表示
			DrawRotaGraph(
				imageMeron.image.x,
				imageMeron.image.y,
				imageMeron.rate,
				imageMeron.angle,
				imageMeron.image.handle,
				TRUE
			);
		}

		else 
		{
			SetFontSize(40);
			DrawString(GAME_WIDTH - 90, 30, "ITEM", FONT_COLOR_WHITE, TRUE);
		}


		//デバック用（当たり判定表示）
		/*for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++) {
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++) {
				switch (map_jimen[tate][yoko].kind) {
				case MAP_KIND_KABE:
					DrawBoxRect(map_jimen[tate][yoko].coll, GetColor(0, 0, 255), FALSE);
					break;

				case MAP_KIND_TURO:
					DrawBoxRect(map_jimen[tate][yoko].coll, GetColor(0, 255, 0), FALSE);
					break;
				}
			}
		}*/

		//デバッグ当たり判定描画
		//DrawBoxRect(player.coll, GetColor(255, 0, 0), FALSE);
		/*DrawBoxRect(player.collTop, GetColor(0, 0, 0), FALSE);
		DrawBoxRect(player.collBottom, GetColor(255, 255, 0), FALSE);
		DrawBoxRect(player.collLeftHead, GetColor(255, 0, 255), FALSE);
		DrawBoxRect(player.collRightHead, GetColor(255, 255, 255), FALSE);
		DrawBoxRect(player.collLeftBody, GetColor(255, 255, 255), FALSE);
		DrawBoxRect(player.collRightBody, GetColor(255, 0, 255), FALSE);*/

		//DrawString(0, 0, "メインゲーム", FONT_COLOR_WHITE);
	}
}

//マップを下に動かす(重力)
VOID MY_MAP_DOWN(VOID)
{
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
}

VOID MY_END_INIT()
{
	fontNum = 1;
	isMoveStart = FALSE;
}

/*----------エンド画面----------*/
VOID MY_END(VOID)
{
	MY_END_PROC();	//エンド画面の処理
	MY_END_DRAW();	//エンド画面の描画
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{
	//ゴールを判断する(BGMを鳴らす)
	switch (goal_type)
	{
	case Clear:
		//効果音を鳴らす
		if (CheckSoundMem(musicEndClear.handle) == 0) {
			ChangeVolumeSoundMem(255 * 50 / 100, musicEndClear.handle);	//音量変更
			PlaySoundMem(musicEndClear.handle, DX_PLAYTYPE_LOOP);
		}
		break;
	case Over:
		//効果音を鳴らす
		if (CheckSoundMem(musicEndOver.handle) == 0) {
			ChangeVolumeSoundMem(255 * 50 / 100, musicEndOver.handle);	//音量変更
			PlaySoundMem(musicEndOver.handle, DX_PLAYTYPE_LOOP);
		}
		break;
	case Miss:
		//効果音を鳴らす
		if (CheckSoundMem(musicEndFailed.handle) == 0) {
			ChangeVolumeSoundMem(255 * 50 / 100, musicEndFailed.handle);	//音量変更
			PlaySoundMem(musicEndFailed.handle, DX_PLAYTYPE_LOOP);
		}

		break;
	default:
		break;
	}

	//テキストを進める
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		//効果音を鳴らす
		if (CheckSoundMem(musicSelect.handle) == 0) {
			PlaySoundMem(musicSelect.handle, DX_PLAYTYPE_NORMAL);
		}

		if (isFontNext && fontNum < 2) {
			fontNum++;
		}
		isFontNext = false;
	}
	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE)
	{
		isFontNext = TRUE;
	}

	//エスケープキーを押したら、スタートシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE && isMoveStart)
	{
		//クリアBGM停止
		if (CheckSoundMem(musicEndClear.handle) != 0)
		{
			StopSoundMem(musicEndClear.handle);
		}

		//ゲームオーバーBGM停止
		if (CheckSoundMem(musicEndOver.handle) != 0)
		{
			StopSoundMem(musicEndOver.handle);
		}

		//ミッション失敗BGM停止
		if (CheckSoundMem(musicEndFailed.handle) != 0)
		{
			StopSoundMem(musicEndFailed.handle);
		}

		MY_START_INIT();	//スタート画面の初期化

		GameScene = GAME_SCENE_START;	//スタート画面へ遷移
	}
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	//ゴールを判断する
	switch (goal_type)
	{
	case Clear:
		MY_CLEAR_PROC();
		break;
	case Over:
		MY_OVER_PROC();
		break;
	case Miss:
		MY_MISS_PROC();
		break;
	default:
		break;
	}
}

//ゲームクリア画面処理
VOID MY_CLEAR_PROC()
{
	//背景
	DrawGraph(0, 0, imageEndBk.handle, TRUE);

	//テキスト
	switch (fontNum)
	{
	case 1:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(GAME_WIDTH / 2 - 400, GAME_HEIGHT / 2 - 200, GAME_WIDTH / 2 + 400, GAME_HEIGHT / 2 + 200, GetColor(200, 200, 200), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetFontSize(50);
		DrawString(GAME_WIDTH / 3, GAME_HEIGHT / 3, "依頼達成です！",FONT_COLOR_BLACK);
		DrawString(GAME_WIDTH / 4, GAME_HEIGHT / 1.5, "おめでとうございます",FONT_COLOR_BLACK);
		break;
	case 2:
		//クリアロゴ表示
		DrawRotaGraph(
			imageEndClearRogo.image.x,
			imageEndClearRogo.image.y,
			imageEndClearRogo.rate,
			imageEndClearRogo.angle,
			imageEndClearRogo.image.handle,
			TRUE
		);

		//ＰＵＳＨ　ＥＳＣの表示
		DrawString(GAME_WIDTH / 3.2, GAME_HEIGHT / 1.5, "PUSH ESC : タイトルへ", FONT_COLOR_WHITE, TRUE);

		isMoveStart = TRUE;	//スタート画面へ遷移するためのフラグ

		break;
	}
}

//ゲームオーバー画面処理
VOID MY_OVER_PROC()
{
	static int cnt = 0;
	
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(10, 10, 10), TRUE);
	SetFontSize(120);
	cnt = (cnt + 1) % 5;
	if (cnt < 2)
	{
		DrawString(GAME_WIDTH / 4.2, GAME_HEIGHT / 3, "GAME OVER", FONT_COLOR_RED, TRUE);
	}
	SetFontSize(40);
	DrawString(GAME_WIDTH / 3.2, GAME_HEIGHT / 1.5, "PUSH ESC : タイトルへ", FONT_COLOR_WHITE, TRUE);

	isMoveStart = TRUE;	//スタート画面へ遷移するためのフラグ
}

//違うアイテムを持ってきたときの処理
VOID MY_MISS_PROC()
{
	//背景
	DrawGraph(0, 0, imageEndBk.handle, TRUE);

	switch (fontNum)
	{
	case 1:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(GAME_WIDTH / 10, GAME_HEIGHT / 2 - 200, GAME_WIDTH / 1.1, GAME_HEIGHT / 2 + 200, GetColor(200, 200, 200), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetFontSize(40);
		DrawString(GAME_WIDTH / 7, GAME_HEIGHT / 3, "残念ながらアイテムが違うようです…。", FONT_COLOR_BLACK);
		DrawString(GAME_WIDTH / 7, GAME_HEIGHT / 1.7, "また、次の機会に期待していますm(__)m", FONT_COLOR_BLACK);
		break;

	case 2:
		//ミッション失敗画像表示
		DrawRotaGraph(
			imageEndMissionFailed.image.x,
			imageEndMissionFailed.image.y,
			imageEndMissionFailed.rate,
			imageEndMissionFailed.angle,
			imageEndMissionFailed.image.handle,
			TRUE
		);

		DrawString(GAME_WIDTH / 3.2, GAME_HEIGHT / 1.5, "PUSH ESC : タイトルへ", FONT_COLOR_WHITE, TRUE);

		isMoveStart = TRUE;	//スタート画面へ遷移するためのフラグ

		break;

	default:
		break;
	}
}

//スタート画面の初期化
VOID MY_START_INIT()
{
	imageTitleRogo.image.y = imageTitleRogo.image.height;
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
}


VOID MY_FPS_DRAW(VOID)
{
	//文字列を描画
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
}


VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//待つべき時間

	if (waitTime > 0)		//指定のFPS値よりも早い場合
	{
		WaitTimer(waitTime);	//待つ
	}
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
	//タイトル背景
	strcpy_s(imageTitleBK.path, IMAGE_TITLE_BK_PATH);
	imageTitleBK.handle = LoadGraph(imageTitleBK.path);
	if (imageTitleBK.handle == ERR) {
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(imageTitleBK.handle, &imageTitleBK.width, &imageTitleBK.height);	//画像の幅と高さを取得
	imageTitleBK.x = GAME_WIDTH / 2 - imageTitleBK.x / 2;
	imageTitleBK.y = GAME_HEIGHT / 2 - imageTitleBK.y / 2;

	//タイトルロゴ
	strcpy_s(imageTitleRogo.image.path, IMAGE_TITLE_ROGO_PATH);
	imageTitleRogo.image.handle = LoadGraph(imageTitleRogo.image.path);
	if (imageTitleRogo.image.handle == ERR) {
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	imageTitleRogo.image.x = GAME_WIDTH / 2 - imageTitleRogo.image.x / 2;
	imageTitleRogo.image.y = imageTitleRogo.image.height / 2;
	imageTitleRogo.angle = 0;
	imageTitleRogo.rate = IMAGE_TITLE_ROGO_ROTA;

	//スタート表記
	strcpy_s(imageTitleStart.image.path, IMAGE_TITLE_START_PATH);			//パスの設定
	imageTitleStart.image.handle = LoadGraph(imageTitleStart.image.path);			//読み込み
	if (imageTitleStart.image.handle == ERR)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(imageTitleStart.image.handle, &imageTitleStart.image.width, &imageTitleStart.image.height);	//画像の幅と高さを取得
	imageTitleStart.image.x = GAME_WIDTH / 2 - imageTitleStart.image.x / 2;		//左右中央揃え
	imageTitleStart.image.y = GAME_HEIGHT / 2 + 200;		//上下中央揃え
	imageTitleStart.angle = 0;
	imageTitleStart.rate = IMAGE_TITLE_START_ROTA;

	//操作説明
	strcpy_s(imageOperating.image.path, IMAGE_OPERATING_PATH);
	imageOperating.image.handle = LoadGraph(imageOperating.image.path);
	if (imageOperating.image.handle == ERR) {
		MessageBox(GetMainWindowHandle(), IMAGE_OPERATING_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	imageOperating.image.x = GAME_WIDTH / 2 - imageOperating.image.x / 2;
	imageOperating.image.y = GAME_HEIGHT / 2 - imageOperating.image.y / 2;
	imageOperating.angle = 0;
	imageOperating.rate = IMAGE_OPERATING_ROTA;

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

	player.x = GAME_WIDTH / 4 - player.x / 2;
	player.y = GAME_HEIGHT / 2 - player.y / 2;
	player.speed = 2;
	player.angle = 0;
	player.changeImageCnt = PLAYER_RIGHT_STAY;
	player.ChangeImageCntMax = PLAYER_RIGHT_STAY;
	player.rate = PLAYER_ROTA;


	GetGraphSize(player.handle[0], &player.width, &player.height);

	//エンド画面背景
	strcpy_s(imageEndBk.path, IMAGE_END_BK_PATH);
	imageEndBk.handle = LoadGraph(imageEndBk.path);
	if (imageEndBk.handle == ERR) {
		MessageBox(GetMainWindowHandle(), IMAGE_END_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(imageEndBk.handle, &imageEndBk.width, &imageEndBk.height);	//画像の幅と高さを取得
	imageEndBk.x = GAME_WIDTH / 2 - imageEndBk.x / 2;
	imageEndBk.y = GAME_HEIGHT / 2 - imageEndBk.y / 2;

	//クリアロゴ
	strcpy_s(imageEndClearRogo.image.path, IMAGE_END_CLEAR_ROGO_PATH);
	imageEndClearRogo.image.handle = LoadGraph(imageEndClearRogo.image.path);
	if (imageEndClearRogo.image.handle == ERR) {
		MessageBox(GetMainWindowHandle(), IMAGE_END_CLEAR_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	imageEndClearRogo.image.x = GAME_WIDTH / 2 - imageEndClearRogo.image.x / 2;
	imageEndClearRogo.image.y = GAME_HEIGHT / 2 - 50;
	imageEndClearRogo.angle = 0;
	imageEndClearRogo.rate = 1;

	//失敗ロゴ
	strcpy_s(imageEndMissionFailed.image.path, IMAGE_END_FAILED_PATH);
	imageEndMissionFailed.image.handle = LoadGraph(imageEndMissionFailed.image.path);
	if (imageEndMissionFailed.image.handle == ERR) {
		MessageBox(GetMainWindowHandle(), IMAGE_END_FAILED_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	imageEndMissionFailed.image.x = GAME_WIDTH / 2 - imageEndMissionFailed.image.x / 2;
	imageEndMissionFailed.image.y = GAME_HEIGHT / 2 - 50;
	imageEndMissionFailed.angle = 0;
	imageEndMissionFailed.rate = 0.9;

	//スイカ
	strcpy_s(imageSuica.image.path, IMAGE_SUICA_PATH);
	imageSuica.image.handle = LoadGraph(imageSuica.image.path);
	if (imageSuica.image.handle == ERR) {
		MessageBox(GetMainWindowHandle(), IMAGE_SUICA_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	imageSuica.image.x = GAME_WIDTH - 50;
	imageSuica.image.y = 50;
	imageSuica.angle = 0;
	imageSuica.rate = 0.2;

	//メロン
	strcpy_s(imageMeron.image.path, IMAGE_MERON_PATH);
	imageMeron.image.handle = LoadGraph(imageMeron.image.path);
	if (imageMeron.image.handle == ERR) {
		MessageBox(GetMainWindowHandle(), IMAGE_MERON_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	imageMeron.image.x = GAME_WIDTH - 50;
	imageMeron.image.y = 50;
	imageMeron.angle = 0;
	imageMeron.rate = 0.2;

	return TRUE;
}

//画像の削除
VOID MY_DELETE_IMAGE(VOID) {
	DeleteGraph(imageTitleBK.handle);
	DeleteGraph(imageTitleRogo.image.handle);
	DeleteGraph(imageTitleStart.image.handle);
	DeleteGraph(imageOperating.image.handle);
	for (int cnt = 0; cnt < PLAYER_DIV_NUM; cnt++) { DeleteGraph(player.handle[cnt]); }
	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }
	DeleteGraph(imageEndBk.handle);
	DeleteGraph(imageEndClearRogo.image.handle);
	DeleteGraph(imageEndMissionFailed.image.handle);
	DeleteGraph(imageSuica.image.handle);
	DeleteGraph(imageMeron.image.handle);
}

/*----------音楽読み込み処理----------*/
BOOL MY_LOAD_MUSIC(VOID) {
	//スタート画面のBGM
	strcpy_s(musicStart.path, MUSIC_START_PATH);
	musicStart.handle = LoadSoundMem(musicStart.path);
	if (musicStart.handle == ERR) {
		MessageBox(GetMainWindowHandle(), MUSIC_START_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//プレイ画面のＢＧＭ
	strcpy_s(musicPlay.path, MUSIC_PLAY_PATH);
	musicPlay.handle = LoadSoundMem(musicPlay.path);
	if (musicPlay.handle == ERR) {
		MessageBox(GetMainWindowHandle(), MUSIC_PLAY_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//クリア画面のＢＧＭ
	strcpy_s(musicEndClear.path, MUSIC_END_CLEAR_PATH);
	musicEndClear.handle = LoadSoundMem(musicEndClear.path);
	if (musicEndClear.handle == ERR) {
		MessageBox(GetMainWindowHandle(), MUSIC_END_CLEAR_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//ミッション失敗画面のＢＧＭ
	strcpy_s(musicEndFailed.path, MUSIC_END_FAILED_PATH);
	musicEndFailed.handle = LoadSoundMem(musicEndFailed.path);
	if (musicEndFailed.handle == ERR) {
		MessageBox(GetMainWindowHandle(), MUSIC_END_FAILED_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//ゲームオーバー画面のＢＧＭ
	strcpy_s(musicEndOver.path, MUSIC_END_OVER_PATH);
	musicEndOver.handle = LoadSoundMem(musicEndOver.path);
	if (musicEndOver.handle == ERR) {
		MessageBox(GetMainWindowHandle(), MUSIC_END_OVER_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//走る効果音
	strcpy_s(musicRun.path, MUSIC_RUN_PATH);
	musicRun.handle = LoadSoundMem(musicRun.path);
	if (musicRun.handle == ERR) {
		MessageBox(GetMainWindowHandle(), MUSIC_RUN_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//アイテム選択の効果音
	strcpy_s(musicItemSelect.path, MUSIC_ITEM_SELECT_PATH);
	musicItemSelect.handle = LoadSoundMem(musicItemSelect.path);
	if (musicItemSelect.handle == ERR) {
		MessageBox(GetMainWindowHandle(), MUSIC_ITEM_SELECT_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//その他選択の効果音
	strcpy_s(musicSelect.path, MUSIC_SELECT_PATH);
	musicSelect.handle = LoadSoundMem(musicSelect.path);
	if (musicSelect.handle == ERR) {
		MessageBox(GetMainWindowHandle(), MUSIC_SELECT_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

VOID MY_DELETE_MUSIC(VOID) {
	DeleteSoundMem(musicStart.handle);
	DeleteSoundMem(musicPlay.handle);
	DeleteSoundMem(musicEndOver.handle);
	DeleteSoundMem(musicEndClear.handle);
	DeleteSoundMem(musicEndFailed.handle);
	DeleteSoundMem(musicRun.handle);
	DeleteSoundMem(musicSelect.handle);
	DeleteSoundMem(musicItemSelect.handle);
}

/*----------フォント処理--------------------*/
//フォント一時的にインストールインストール
BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	//フォントを一時的に読み込み(WinAPI)
	if (AddFontResourceEx(FONT_PATH, FR_PRIVATE, NULL) == 0)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), FONT_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//フォントインストールしたものを削除
VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	//一時的に読み込んだフォントを削除(WinAPI)
	RemoveFontResourceEx(FONT_PATH, FR_PRIVATE, NULL);

	return;
}

//フォントの読み込み
BOOL MY_FONT_CREATE(VOID)
{
	//フォントデータを作成
	strcpy_s(fontSmart.path, sizeof(fontSmart.path), FONT_PATH);	//パスをコピー
	strcpy_s(fontSmart.name, sizeof(fontSmart.name), FONT_PATH);	//フォント名をコピー
	fontSmart.handle = -1;								//ハンドルを初期化
	fontSmart.size = 32;								//サイズは32
	fontSmart.bold = 1;								//太さ1
	fontSmart.type = DX_FONTTYPE_ANTIALIASING_EDGE;	//アンチエイリアシング付きのフォント

	//フォントハンドル作成
	fontSmart.handle = CreateFontToHandle(fontSmart.name, fontSmart.size, fontSmart.bold, fontSmart.type);
	//フォントハンドル作成できないとき、エラー
	if (fontSmart.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }

	return TRUE;
}

//フォントの削除
VOID MY_FONT_DELETE(VOID)
{
	//フォントデータを削除
	DeleteFontToHandle(fontSmart.handle);	//フォントのハンドルを削除

	return;
}

/*----------冒頭テキスト表示----------*/
VOID MY_FIRST_FONT_DRAW() 
{
	static int fontX = GAME_WIDTH / 6;
	static int fontY = GAME_HEIGHT / 4;

	//背景
	DrawGraph(0, 0, imageTitleBK.handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(GAME_WIDTH / 2 - 400, GAME_HEIGHT / 2 - 200, GAME_WIDTH / 2 + 400, GAME_HEIGHT / 2 + 200, GetColor(200, 200, 200), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawString(GAME_WIDTH - 100, GAME_HEIGHT - 50, "Enter→", FONT_COLOR_WHITE);

	switch (fontNum)
	{
	case 1:
		DrawString(fontX, fontY, "ギルドから冒険者試験の内容が届きました！", FONT_COLOR_BLACK);
		break;
	case 2:
		DrawString(fontX, fontY, "冒険者見習の諸君、\n今から君たちには正式な冒険者になるために\nあるものを獲ってきてもらいたい", FONT_COLOR_BLACK);
		break;
	case 3:
		DrawString(fontX, fontY, "見事、依頼したものをギルドに届けることができたら、\n冒険者として認めよう！", FONT_COLOR_BLACK);
		break;
	case 4:
		DrawString(fontX, fontY, "ただし…", FONT_COLOR_BLACK);
		break;
	case 5:
		DrawString(fontX, fontY, "依頼内容をそのまま伝えるのもつまらな・・・\n内容を自分で理解することも重要だ！！", FONT_COLOR_BLACK);
		break;
	case 6:
		DrawString(fontX, fontY, "これから、問題を出す。\n見事答えを導き出し、正しいものをギルドにとどけてくれ！", FONT_COLOR_BLACK);
		break;

	case 7:
		DrawString(fontX, fontY, """目の見えない戦士からの一撃を躱せなければ食われてしまう。\nある一部の地域では、名前に水を含む。""", FONT_COLOR_BLUE);
		break;

	case 8:
		DrawString(fontX, fontY, "注意！\n(進んでいくと、看板が現れます！\n看板にタッチすることで\nギルドにアイテムを選択することができます)", FONT_COLOR_RED);
		break;

	case 9:
		MY_OPERATING_DRAW();
		DrawString(GAME_WIDTH - 100, GAME_HEIGHT - 50, "Enter→", FONT_COLOR_WHITE);
		break;
	default:
		break;
	}
}

/*----------操作説明----------*/
VOID MY_OPERATING_DRAW() {
	DrawRotaGraph(
		imageOperating.image.x,
		imageOperating.image.y,
		imageOperating.rate,
		imageOperating.angle,
		imageOperating.image.handle,
		TRUE);
}

/*-----------アイテム選択テキスト表示-----------------*/
VOID MY_ITEM_TEXT_DRAW() {
	int fontX = GAME_WIDTH / 6 - 20;
	int fontY = GAME_HEIGHT / 4;

	//背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(GAME_WIDTH / 2 - 400, GAME_HEIGHT / 2 - 200, GAME_WIDTH / 2 + 400, GAME_HEIGHT / 2 + 200, GetColor(200, 200, 200), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
	SetFontSize(32);
	DrawString(fontX, fontY, "あなたが思う正解のアイテムを選択してください！", FONT_COLOR_BLACK);

	SetFontSize(40);
	DrawString(GAME_WIDTH / 4, fontY + GAME_HEIGHT / 3, "1 →　スイカ", FONT_COLOR_RED);
	DrawString(GAME_WIDTH / 2 + 64, fontY + GAME_HEIGHT / 3, "2 →　メロン", FONT_COLOR_BLUE);
	
}

/*--------MAP---------*/
//マップチップの分割
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

//CSVの読み込み
BOOL MY_LOAD_CSV_MAP(const char* path, MAP* m, MAP* mInit)
{
	//ＣＳＶファイルを開く
	FILE* fp;

	if ((fp = fopen(path, "r")) == NULL) {
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

	//マップの役割を設定
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++) {
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++) {
			MAP* p = m + tate * GAME_MAP_YOKO_MAX + yoko;
			MAP* pInit = mInit + tate * GAME_MAP_YOKO_MAX + yoko;

			p->kind = MAP_KIND_TURO;

			for (int cnt = 0; cnt < MAP_JIMEN_KIND; cnt++) {
				if (p->value == MapJimenID[cnt]) {
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

//当たり判定
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top)
	{
		return TRUE;
	}
	return FALSE;
}

//デバック用RECTを利用して四角を描画
VOID MY_DRAW_BOX_REXT(RECT r, unsigned int color, bool b)
{
	//引数を基に描画
	DrawBox(r.left, r.top, r.right, r.bottom, color, b);
	return;
}