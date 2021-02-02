#pragma once

#include "DxLib.h"
#include "game.h"

#define GAME_MAP_PATH		TEXT(".\\MAP\\mapChip1.png")		//マップ画像パス
#define GAME_CSV_PATH_MAP1_SORA 		TEXT(".\\MAP\\map_sita.csv")//空
#define GAME_CSV_PATH_MAP1_JIMEN		TEXT(".\\MAP\\map_naka.csv")//地面
#define GAME_CSV_PATH_MAP1_SOUSHOKU		TEXT(".\\MAP\\map_ue.csv")//装飾

#define GAME_MAP_TATE_MAX		40	//マップ縦の広さ
#define GAME_MAP_YOKO_MAX		100	//マップ横の広さ

#define MAP_KABE_KIND 4
#define MAP_GUILD_KIND 4

#define MAP_DIV_WIDTH			32
#define MAP_DIV_HEIGHT			32

#define MAP_DIV_TATE			18  //画像の分割数（マップの使う数じゃない）マップchipのプロパティを表示して大きさを確認して区切るビット数で割った数を入れる
#define MAP_DIV_YOKO			32
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//マップチップを分割する総数

#define GAME_YOKO_CENTER    15

enum MAP_KIND {
     MAP_KIND_SORA,
     MAP_KIND_KABE,
     MAP_KIND_TURO,
     MAP_KIND_NONE,
     MAP_KIND_KANBAN,
     MAP_KIND_GUILD
};

typedef struct STRUCT_MAPCHIP
{
    char path[PATH_MAX];
    int handle[MAP_DIV_NUM];
    int width;
    int height;
}MAP_CHIP;      //マップチップのデータ

typedef struct STRUCT_MAP
{
    int value;			//マップの値
    MAP_KIND kind;		//マップの種類
    int x;				//X位置
    int y;				//Y位置
    int width;			//幅
    int height;			//高さ
    RECT coll;			//マップの当たり判定
}MAP;          //ゲームで使うマップのデータ

BOOL MY_LOAD_MAPCHIP(VOID);
BOOL MY_CHECK_MAP_PLAYER_COLL(VOID);
BOOL MY_LOAD_CSV_MAP(const char* path, MAP* m, MAP* mInit);
