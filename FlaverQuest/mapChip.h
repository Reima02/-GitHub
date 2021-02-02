#pragma once

#include "DxLib.h"
#include "game.h"

#define GAME_MAP_PATH		TEXT(".\\MAP\\mapChip1.png")		//�}�b�v�摜�p�X
#define GAME_CSV_PATH_MAP1_SORA 		TEXT(".\\MAP\\map_sita.csv")//��
#define GAME_CSV_PATH_MAP1_JIMEN		TEXT(".\\MAP\\map_naka.csv")//�n��
#define GAME_CSV_PATH_MAP1_SOUSHOKU		TEXT(".\\MAP\\map_ue.csv")//����

#define GAME_MAP_TATE_MAX		40	//�}�b�v�c�̍L��
#define GAME_MAP_YOKO_MAX		100	//�}�b�v���̍L��

#define MAP_KABE_KIND 4
#define MAP_GUILD_KIND 4

#define MAP_DIV_WIDTH			32
#define MAP_DIV_HEIGHT			32

#define MAP_DIV_TATE			18  //�摜�̕������i�}�b�v�̎g��������Ȃ��j�}�b�vchip�̃v���p�e�B��\�����đ傫�����m�F���ċ�؂�r�b�g���Ŋ�������������
#define MAP_DIV_YOKO			32
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//�}�b�v�`�b�v�𕪊����鑍��

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
