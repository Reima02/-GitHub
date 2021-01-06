#pragma once

#include "DxLib.h"
#include "game.h"

#define GAME_MAP_PATH		TEXT(".\\MAP\\mapChip1.png")		//マップ画像パス
#define GAME_CSV_PATH_MAP1_SORA 		TEXT(".\\MAP\\map_sita.csv")//空
#define GAME_CSV_PATH_MAP1_JIMEN		TEXT(".\\MAP\\map1_naka.csv")//地面
#define GAME_CSV_PATH_MAP1_SOUSHOKU		TEXT(".\\MAP\\map1_ue.csv")//装飾
//#define GAME_CSV_PATH_MAP1_ATARIHANTEI 	TEXT(".\\MAP\\map1_atarihantei.csv")//装飾

#define GAME_MAP_TATE_MAX		20	//マップ縦の広さ
#define GAME_MAP_YOKO_MAX		100	//マップ横の広さ

#define MAP_DIV_WIDTH			32
#define MAP_DIV_HEIGHT			32

#define MAP_DIV_TATE			10
#define MAP_DIV_YOKO			16
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//マップチップを分割する総数



enum MAP_KIND {
     GAME_MAP_JIMEN_LEFT = 182,//地面左
     GAME_MAP_JIMEN_RIGTH = 183,//地面右
     GAME_MAP_JIMEN	= 182,//地面
     GAME_MAP_JIMEN_LEFT_NAKA = 235,//地面中左
     GAME_MAP_JIMEN_LEFT2_NAKA = 289,//地面中左２
     GAME_MAP_JIMEN_NAKA = 236,//地面中
     GAME_MAP_JIMEN_RIGHT = 237,//地面左
     GAME_MAP_JIMEN_RIGHT2 = 291,//地面左
    
     GAME_MAP_SORA_1 = 284,
     GAME_MAP_SORA_2 = 285,
     GAME_MAP_SORA_3 = 286,
     GAME_MAP_SORA_4 = 287,
     GAME_MAP_SORA_5 = 288,

     GAME_MAP_SORA_6 = 230,
     GAME_MAP_SORA_7 = 231,
     GAME_MAP_SORA_8 = 232,
     GAME_MAP_SORA_9 = 233,
     GAME_MAP_SORA_10 = 234,
    
     GAME_MAP_SORA_11 = 176,
     GAME_MAP_SORA_12 = 177,
     GAME_MAP_SORA_13 = 178,
     GAME_MAP_SORA_14 = 179,
     GAME_MAP_SORA_15 = 180,
    
     GAME_MAP_KUSA	= 187,
     GAME_MAP_KI_UE_1 =	144,
     GAME_MAP_KI_UE_2 =	145,
     GAME_MAP_KI_SITA_1 = 198,
     GAME_MAP_KI_SITA_2 = 199,
     GAME_MAP_KI_2_UE_1 = 146,
     GAME_MAP_KI_2_UE_2 =  147,
     GAME_MAP_KI_2_SITA_1 =  200,
     GAME_MAP_KI_2_SITA_2 =  201,
     GAME_MAP_KI_3 = 202,
     GAME_MAP_KANBAN = 294,
     GAME_MAP_GUILD_UE_1 = 150,
     GAME_MAP_GUILD_UE_2 = 151,
     GAME_MAP_GUILD_SITA_1 = 204,
     GAME_MAP_GUILD_SITA_2 = 205,
    
     GAME_MAP_ATARI_MARU = 295,
     GAME_MAP_ATARI_BATSU = 296,

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
