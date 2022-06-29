#include "Key.h"

// ���݂̃L�[�������Ă���t���[����
int nowKeyPressFrame[KeyKindMax];

// �ЂƂO�̃L�[�������Ă���t���[����
int oldKeyPressFrame[KeyKindMax];

void KeyInit(void)
{
	// �z��̏�����
	for (int i = 0; i < KeyKindMax; i++)
	{
		nowKeyPressFrame[i] = 0;
		oldKeyPressFrame[i] = 0;
	}
}

void KeyUpdate(void)
{
	// �ꎞ�I�ɕێ�����L�[���
	char keyState[KeyKindMax];

	// ���ׂẴL�[������x�Ɏ擾
	GetHitKeyStateAll(&keyState[0]);

	// �L�[�����X�V
	for (int i = 0; i < KeyKindMax; i++)
	{
		// �ЂƂO�̃L�[���͂�ێ�
		oldKeyPressFrame[i] = nowKeyPressFrame[i];
		// ���݁A�L�[��������Ă���Ƃ�
		if (keyState[i] != 0)
		{
			// ������Ă���t���[�������J�E���g�A�b�v
			nowKeyPressFrame[i]++;
		}
		else if(keyState[i] == 0)
		{
			// ������Ă��Ȃ��Ȃ�A�t���[�������[���N���A
			nowKeyPressFrame[i] = 0;
		}
	}
}

// �����FDX���C�u�����̃L�[�R�[�h�iKEY_INPUT_�Ŏn�܂�}�N����`�j
bool KeyDown(int KEY_INPUT_)
{
	// ���݉�����Ă���L�[�̃t���[�������O������Ȃ�
	if (nowKeyPressFrame[KEY_INPUT_] > 0)
	{
		return true;		//������
	}

	return false;		// �����Ă��Ȃ�
}

// �����FDX���C�u�����̃L�[�R�[�h�iKEY_INPUT_�Ŏn�܂�}�N����`�j
// �����F�u�L�[���������L�[���グ��v���Z�b�g�ōs��ꂽ�����A�N���b�N
bool KeyClick(int KEY_INPUT_)
{
	// ���݁A�L�[�͉�����Ă��炸�@����
	// �ЂƂO�̃L�[�͉�����Ă����Ƃ�
	if (nowKeyPressFrame[KEY_INPUT_] == 0
		&& oldKeyPressFrame[KEY_INPUT_] > 0)
	{
		return true;		//������
	}

	return false;		// �����Ă��Ȃ�
}

// �����FDX���C�u�����̃L�[�R�[�h�iKEY_INPUT_�Ŏn�܂�}�N����`�j
// ���ӁF�߂�l�̓~���b�Ȃǂł͂Ȃ��A�t���[�����I
int KeyPressFrame(int KEY_INPUT_)
{
	return nowKeyPressFrame[KEY_INPUT_];
}
