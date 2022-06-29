#pragma once

#include <DxLib.h>

// �}�N����`
#define GameFPS					60	// �ݒ肵�����t���[�����[�g

#define MicroSecond		1000000.0f	//1�}�C�N���b
#define MillSecond		  1000.0f	//1�~���b
#define WaitTimeMill        3000    //�ő�ő҂Ă�~����

// �\���̂̒�`�����O�̍Ē�`
typedef struct _FPS
{
	LONGLONG firstTakeTime = 0;		// 1�t���[���ڂ̌v������
	LONGLONG nowTakeTime = 0;		// ���݂̌v������
	LONGLONG oldTakeTime = 0;		// �ȑO�̌v������

	float deltatime = 0.000001f;	// �f���^�^�C��(�o�ߎ���)
	int frameCount = 1;				// ���݂̃t���[����(1�t���[���ځ`MAX�t���[���ڂ܂�)
	float average = 0.0f;			// ����FPS�l
}FPS;

//�O���O���[�o���ϐ�
extern FPS fps;

extern void FPSInit(void);		//FPS������
extern void FPSCheck(void);		//FPS�v��
extern void FPSDraw(void);		//FPS�`��
extern void FPSWait(void);		//FPS�ҋ@
extern float GetDeltaTimes(void);//�f���^�^�C�����擾
