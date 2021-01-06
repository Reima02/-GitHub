#pragma once

#include "DxLib.h"
#include "game.h"

#define GAME_MAP_PATH		TEXT(".\\MAP\\mapChip1.png")		//�}�b�v�摜�p�X
#define GAME_CSV_PATH_MAP1_SORA 		TEXT(".\\MAP\\map_sita.csv")//��
#define GAME_CSV_PATH_MAP1_JIMEN		TEXT(".\\MAP\\map1_naka.csv")//�n��
#define GAME_CSV_PATH_MAP1_SOUSHOKU		TEXT(".\\MAP\\map1_ue.csv")//����
//#define GAME_CSV_PATH_MAP1_ATARIHANTEI 	TEXT(".\\MAP\\map1_atarihantei.csv")//����

#define GAME_MAP_TATE_MAX		20	//�}�b�v�c�̍L��
#define GAME_MAP_YOKO_MAX		100	//�}�b�v���̍L��

#define MAP_DIV_WIDTH			32
#define MAP_DIV_HEIGHT			32

#define MAP_DIV_TATE			10
#define MAP_DIV_YOKO			16
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//�}�b�v�`�b�v�𕪊����鑍��



enum MAP_KIND {
     GAME_MAP_JIMEN_LEFT = 182,//�n�ʍ�
     GAME_MAP_JIMEN_RIGTH = 183,//�n�ʉE
     GAME_MAP_JIMEN	= 182,//�n��
     GAME_MAP_JIMEN_LEFT_NAKA = 235,//�n�ʒ���
     GAME_MAP_JIMEN_LEFT2_NAKA = 289,//�n�ʒ����Q
     GAME_MAP_JIMEN_NAKA = 236,//�n�ʒ�
     GAME_MAP_JIMEN_RIGHT = 237,//�n�ʍ�
     GAME_MAP_JIMEN_RIGHT2 = 291,//�n�ʍ�
    
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
}MAP_CHIP;      //�}�b�v�`�b�v�̃f�[�^

typedef struct STRUCT_MAP
{
    int value;			//�}�b�v�̒l
    MAP_KIND kind;		//�}�b�v�̎��
    int x;				//X�ʒu
    int y;				//Y�ʒu
    int width;			//��
    int height;			//����
    RECT coll;			//�}�b�v�̓����蔻��
}MAP;          //�Q�[���Ŏg���}�b�v�̃f�[�^

BOOL MY_LOAD_MAPCHIP(VOID);
BOOL MY_CHECK_MAP_PLAYER_COLL(VOID);
BOOL MY_LOAD_CSV_MAP(const char* path, MAP* m, MAP* mInit);
