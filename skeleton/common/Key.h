#pragma once

//�w�b�_�t�@�C���ǂݍ���
#include <DxLib.h>

//�}�N����`
#define KeyKindMax 256 // �L�[�̎��

//�O���̃v���g�^�C�v�錾
extern void KeyInit(void);						//�L�[�{�[�h�����̏�����
extern void KeyUpdate(void);					//�L�[�{�[�h�����̍X�V
extern bool KeyDown(int KEY_INPUT_);			//����̃L�[�����������H
extern bool KeyClick(int KEY_INPUT_);			//����̃L�[���N���b�N�������H
extern int KeyPressFrame(int KEY_INPUT_);		//����̃L�[���������t���[����