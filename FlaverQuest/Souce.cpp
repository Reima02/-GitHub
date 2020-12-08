/*----------�w�b�_�[�t�@�C��----------*/
#include "DxLib.h"

/*----------�}�N����`----------*/
#define GAME_WIDTH	1024	//��ʂ̉��̑傫��
#define GAME_HEIGHT	576	//��ʂ̏c�̑傫��
#define GAME_COLOR	32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR	0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"Flavor Quest"	//�E�B���h�E�̃^�C�g��

#define ERR -1			//-1���G���[

//FPS�ݒ�
#define GAME_FPS			60	//FPS�̐��l	

//�p�X�̒���
#define PATH_MAX			255	//255�����܂�
#define NAME_MAX			255	//255�����܂�

//�摜
#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")		//�摜�ǂݍ��݃G���[���b�Z�[�W
#define IMAGE_TITLE_BK_PATH		TEXT(".\\IMAGE\\TitleBack.png") //�^�C�g���w�i�̃p�X
#define IMAGE_TITLE_ROGO_PATH	TEXT(".\\IMAGE\\titlerogo.png")	//�^�C�g�����S�̃p�X
#define	IMAGE_TITLE_ROGO_ROTA	0.25		//�^�C�g�����S�g�嗦
#define IMAGE_TITLE_START_PATH		TEXT(".\\IMAGE\\title_start.png")	//�^�C�g���X�^�[�g�̉摜
#define IMAGE_TITLE_START_ROTA	1
//���y
#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")		//���y�ǂݍ��݃G���[���b�Z�[�W
#define MUSIC_START_PATH		TEXT(".\\MUSIC\\start.mp3")		//�^�C�g��BGM

/*----------�v���g�^�C�v�錾----------*/
//�X�^�[�g���
VOID MY_START(VOID);		//�X�^�[�g���
VOID MY_START_PROC(VOID);	//�X�^�[�g��ʂ̏���
VOID MY_START_DRAW(VOID);	//�X�^�[�g��ʂ̕`��

//�v���C���
VOID MY_PLAY(VOID);			//�v���C���
VOID MY_PLAY_PROC(VOID);	//�v���C��ʂ̏���
VOID MY_PLAY_DRAW(VOID);	//�v���C��ʂ̕`��
VOID MY_PLAY_RESET(VOID);	//�v���C��ʂ̏�����

//�G���h���
VOID MY_END(VOID);			//�G���h���
VOID MY_END_PROC(VOID);		//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);		//�G���h��ʂ̕`��

//�L�[���͏���
VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//�L�[�̓��͏�Ԃ��X�V����
BOOL MY_KEY_DOWN(int);				//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEY_UP(int);				//�L�[�������グ�����A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEYDOWN_KEEP(int, int);		//�L�[�����������Ă��邩�A�L�[�R�[�h�Ŕ��f����

//FPS�֘A
VOID MY_FPS_UPDATE(VOID);			//FPS�l���v���A�X�V����֐�
VOID MY_FPS_DRAW(VOID);				//FPS�l��`�悷��֐�
VOID MY_FPS_WAIT(VOID);				//FPS�l���v�����A�҂֐�

//�摜�ǂݍ��ݏ���
BOOL MY_LOAD_IMAGE(VOID);		//�摜���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_IMAGE(VOID);		//�摜���܂Ƃ߂č폜����֐�

//���y
BOOL MY_LOAD_MUSIC(VOID);		//���y�ǂݍ���
VOID MY_DELETE_MUSIC(VOID);		//���y�폜

/*----------�O���[�o���ϐ�----------*/
//�V�[���̒ǉ�
enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END
};

//�摜�\����
typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
}IMAGE;

//��]�g�傷��摜�̍\����
typedef struct STRUCT_IMAGE_ROTA
{
	IMAGE image;		//IMAGE�\����
	double angle;		//��]��
	double rate;		//�g�嗦

}IMAGE_ROTA;

//�v���C���[
typedef struct STRUCT_CHARA
{
	IMAGE image;				//IMAGE�\����
	int speed = 1;					//����

	RECT coll;					//�����蔻��
	int PlayerStartPosX = 30;
	int PlayerStartPosY = 300;
}CHARA;	//�L�����N�^�[�\����

//���y�\����
typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��
}MUSIC;

//�V�[��
int GameScene;

//�L�[�{�[�h�̓��͂��擾
char AllKeyState[256] = { '\0' };			//���ׂẴL�[�̏�Ԃ�����
char OldAllKeyState[256] = { '\0' };	//���ׂẴL�[�̏��(���O)������
int StartTimeFps;						//����J�n����
int CountFps;							//�J�E���^
float CalcFps;							//�v�Z����
int SampleNumFps = GAME_FPS;		//���ς����T���v����

//�摜
IMAGE ImageTitleBK;					//�^�C�g���w�i
IMAGE_ROTA ImageTitleRogo;			//�^�C�g�����S
IMAGE_ROTA ImageTitleStart;			//�^�C�g���X�^�[�g�̉摜

//���y
MUSIC musicStart;		//�X�^�[�g��ʂ̉��y


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);		//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));	//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);						//��A�N�e�B�u�ł����s����
	SetMouseDispFlag(FALSE);					//�}�E�X�J�[�\����\��

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	int DrawX = 0;	//�\���ʒuX
	int DrawY = 0;	//�\���ʒuY

	SetDrawScreen(DX_SCREEN_BACK);	//Draw�n�֐��͗���ʂɕ`��

	//�摜�ǂݍ���
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//���y�ǂݍ���
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	GameScene = GAME_SCENE_START;//�ŏ��̓X�^�[�g��ʂ���

	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != FALSE) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��

		if (ClearDrawScreen() != FALSE) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		MY_FPS_UPDATE();	//FPS�̏���[�X�V]
		MY_FPS_DRAW();		//FPS�̏���[�`��]
		MY_FPS_WAIT();		//FPS�̏���[�҂�]

		MY_ALL_KEYDOWN_UPDATE();				//�����Ă���L�[��Ԃ��擾

		//�V�[�����Ƃɏ������s��
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//�X�^�[�g���
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//�v���C���
			break;
		case GAME_SCENE_END:
			MY_END();	//�G���h���
			break;
		}

		ScreenFlip();		//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��
	}

	//�摜�n���h����j��
	MY_DELETE_IMAGE();

	//���y�폜
	MY_DELETE_MUSIC();
	DxLib_End();	//�c�w���C�u�����g�p�̏I������

	return 0;
}

/*----------�X�^�[�g���----------*/
VOID MY_START(VOID)
{
	MY_START_PROC();	//�X�^�[�g��ʂ̏���
	MY_START_DRAW();	//�X�^�[�g��ʂ̕`��

	return;
}

//�X�^�[�g��ʂ̏���
VOID MY_START_PROC(VOID)
{
	//BGM�Đ�
	if (CheckSoundMem(musicStart.handle) == 0) {					//�������ǂݎ��Ă�����
		ChangeVolumeSoundMem(255 * 50 / 100, musicStart.handle);	//���ʕύX
		PlaySoundMem(musicStart.handle, DX_PLAYTYPE_LOOP);			//�Đ�
	}
	//�G���^�[�L�[����������A�v���C�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		//BGM��~
		if (CheckSoundMem(musicStart.handle) != 0) {
			StopSoundMem(musicStart.handle);
		}
		GameScene = GAME_SCENE_PLAY;
	}

	return;
}

//�X�^�[�g��ʂ̕`��
VOID MY_START_DRAW(VOID)
{
	//�w�i
	DrawGraph(0, 0, ImageTitleBK.handle, TRUE);

	//���S
	DrawRotaGraph(
		ImageTitleRogo.image.x,
		ImageTitleRogo.image.y,
		ImageTitleRogo.rate,
		ImageTitleRogo.angle,
		ImageTitleRogo.image.handle,
		TRUE
	);

	//�X�^�[�g�\��
	DrawRotaGraph(
		ImageTitleStart.image.x,
		ImageTitleStart.image.y,
		ImageTitleStart.rate,
		ImageTitleStart.angle,
		ImageTitleStart.image.handle,
		TRUE);

	DrawString(0, 0, "�X�^�[�g���", GetColor(255, 255, 255));
	return;
}

/*----------�v���C���----------*/
VOID MY_PLAY(VOID) {
	MY_PLAY_PROC();
	MY_PLAY_DRAW();
}

VOID MY_PLAY_PROC(VOID)
{
	//�X�y�[�X�L�[����������A�G���h�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		GameScene = GAME_SCENE_END;
	}

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{
	//�΂̎l�p��`��
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 255, 0), TRUE);

	DrawString(0, 0, "�v���C���(�X�y�[�X�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

/*----------�G���h���----------*/
VOID MY_END(VOID)
{
	MY_END_PROC();	//�G���h��ʂ̏���
	MY_END_DRAW();	//�G���h��ʂ̕`��
	return;
}

//�G���h��ʂ̏���
VOID MY_END_PROC(VOID)
{
	//�G�X�P�[�v�L�[����������A�X�^�[�g�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		GameScene = GAME_SCENE_START;
	}

	return;
}

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{
	//�̎l�p��`��
	DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);

	DrawString(0, 0, "�G���h���(�G�X�P�[�v�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

/*------------FPS----------*/
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1�t���[���ڂȂ玞�����L��
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60�t���[���ڂȂ畽�ς��v�Z
	{
		int now = GetNowCount();
		//���݂̎��Ԃ���A0�t���[���ڂ̎��Ԃ������AFPS�̐��l�Ŋ��遁1FPS�ӂ�̕��ώ��Ԃ��v�Z�����
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}


VOID MY_FPS_DRAW(VOID)
{
	//�������`��
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}


VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//������������
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//�҂ׂ�����

	if (waitTime > 0)		//�w���FPS�l���������ꍇ
	{
		WaitTimer(waitTime);	//�҂�
	}
	return;
}

/*------------------�L�[���͏����֐�-----------------------------*/
//�L�[���͂̏�Ԃ��ێ�
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[256];	//�ꎞ�I�ɁA���݂̃L�[�̓��͏�Ԃ��i�[����

	//���O�̃L�[���͂��Ƃ��Ă���
	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//������Ă���L�[�̃L�[�R�[�h�������Ă���Ƃ�
		{
			AllKeyState[i]++;	//������Ă���
		}
		else
		{
			AllKeyState[i] = 0;	//������Ă��Ȃ�
		}
	}
	return;
}

//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//�L�[�R�[�h�̃L�[�������Ă��鎞
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//�L�[�������Ă���
	}
	else
	{
		return FALSE;	//�L�[�������Ă��Ȃ�
	}
}

//�L�[�������グ�����A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//���O�͉����Ă���
		&& AllKeyState[KEY_INPUT_] == 0)	//���͉����Ă��Ȃ��Ƃ�
	{
		return TRUE;	//�L�[�������グ�Ă���
	}
	else
	{
		return FALSE;	//�L�[�������グ�Ă��Ȃ�
	}
}

//�L�[�����������Ă��邩�A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	//���������鎞��=�b���~FPS�l
	//��j60FPS�̃Q�[���ŁA1�b�ԉ���������Ȃ�A1�b�~60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//���������Ă���
	}
	else
	{
		return FALSE;	//���������Ă��Ȃ�
	}
}

/*----------�摜�ǂݍ��ݏ���----------*/
BOOL MY_LOAD_IMAGE(VOID) {
	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);
	if (ImageTitleBK.handle == ERR) {
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);	//�摜�̕��ƍ������擾
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

	//�X�^�[�g�\�L
	strcpy_s(ImageTitleStart.image.path, IMAGE_TITLE_START_PATH);			//�p�X�̐ݒ�
	ImageTitleStart.image.handle = LoadGraph(ImageTitleStart.image.path);			//�ǂݍ���
	if (ImageTitleStart.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleStart.image.handle, &ImageTitleStart.image.width, &ImageTitleStart.image.height);	//�摜�̕��ƍ������擾
	ImageTitleStart.image.x = GAME_WIDTH / 2 - ImageTitleStart.image.x / 2;		//���E��������
	ImageTitleStart.image.y = GAME_HEIGHT/1.2;		//�㉺��������
	ImageTitleStart.angle = 0;
	ImageTitleStart.rate = IMAGE_TITLE_START_ROTA;

	return TRUE;
}

VOID MY_DELETE_IMAGE(VOID) {
	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleRogo.image.handle);
	DeleteGraph(ImageTitleStart.image.handle);
}

/*----------���y�ǂݍ��ݏ���----------*/
BOOL MY_LOAD_MUSIC(VOID) {
	//�X�^�[�g��ʂ�BGM
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