#pragma once
#include <DxLib.h>

// �}�N����`
#define MouseKindMax			8        // �}�E�X�̃{�^���̎��
#define MouseCodeErrIndex		999		 // �}�E�X�R�[�h��ϊ������v�f���̃G���[��

//�\����
typedef struct _MousePoint
{
	int x;		// �}�E�X��X�ʒu
	int y;		// �}�E�X��Y�ʒu
}MousePoint;

// �O���̃v���g�^�C�v�錾
extern void MouseNowIntoOld(void);							// Now???�n�̕ϐ��̒l��Old???�n�̕ϐ��֓����
extern int MouseCodeToIndex(int MOUSE_INPUUT_);				// �}�E�X�̃{�^���R�[�h��z��̗v�f���ɕϊ�����
												
extern void MouseInit(void);								// �}�E�X�����̏�����
extern void MouseUpdate(int gameWidht, int gameheight);	// �}�E�X�����̍X�V
extern bool MouseDown(int MOUSE_INPUT_);					// ����̃{�^�������������H
extern bool MouseClick(int MOUSE_INPUT_);					// ����̃{�^�����N���b�N�������H
extern int MousePressFrame(int MOUSE_INPUT_);				// ����̃{�^�����������t���[����
												
extern MousePoint GetPointMouse(void);						// �}�E�X�̌��݈ʒu���擾����
extern MousePoint GetOldPointMouse(void);					// �}�E�X�̈ȑO�̈ʒu���擾����
extern MousePoint GetDiffPointMouse(void);					// �}�E�X�̈ˑR�ƌ��݂̈ʒu�̍����擾����
												
extern int GetWheelMouse(void);								// �}�E�X�̌��݃z�C�[���l���擾����

extern bool CollRectToMousePoint(RECT rect);	// ��`�ƃ}�E�X�̓_���������Ă��邩�H
extern bool CollWindowToMousePoint(int gameWidth, int gameHeight);	// ��ʂƃ}�E�X�̓_���������Ă��邩�H

extern bool CollRectToMouseDown(RECT rect, int MOUSE_INPUT_);	//��`���Ń}�E�X�̃{�^�������������H
extern bool CollRectToMouseClick(RECT rect, int MOUSE_INPUT_);	//��`���Ń}�E�X�̃{�^�����N���b�N�������H

extern bool CollWindowToMouseDown(int gameWidth, int gameHeight, int MOUSE_INPUT_);	//��ʂ̂ǂ����łŃ}�E�X�̃{�^�������������H
extern bool CollWindowToMouseClick(int gameWidth, int gameHeight, int MOUSE_INPUT_);	//��ʂ̂ǂ����Ń}�E�X�̃{�^�����N���b�N�������H
