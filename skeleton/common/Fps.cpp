#include"Fps.h"


//	�O���[�o���ϐ�
FPS fps;

void FPSInit(void)
{
	// Windows���N�����Ă��猻�݂܂ł̎��Ԃ𓾂�i�}�C�N���b�j
	fps.firstTakeTime = GetNowHiPerformanceCount();

	// ���̒l��������
	fps.nowTakeTime = fps.firstTakeTime;
	fps.oldTakeTime = fps.firstTakeTime;
	fps.deltatime = 0.000001f;
	fps.frameCount = 1;
	fps.average = 0.0f;

	return;
}

// �v��
void FPSCheck(void)
{
	// ���݂̎������擾
	fps.nowTakeTime = GetNowHiPerformanceCount();

	// �f���^�^�C�����v�Z
	fps.deltatime = (fps.nowTakeTime - fps.oldTakeTime) / MicroSecond;

	// ���݂̎�����ۑ�
	fps.oldTakeTime = fps.nowTakeTime;

	// ���݂�MAX�t���[���ڂȂ�
	if (fps.frameCount == GameFPS)
	{
		// 1�t���[���ځ`MAX�t���[���ڂ܂ł̍��v���Ԃ��v�Z
		float totalFrameTime = fps.nowTakeTime - fps.firstTakeTime;

		// ���v���Ԃ𗝑z��FPS�l�Ŋ����ĕ��ϒl���v�Z
		float calcAverage = totalFrameTime / GameFPS;

		// 1�b������̃t���[�����ɕϊ�
 		fps.average = MicroSecond / calcAverage;

		// 1�t���[���ڂ̎������擾
		fps.firstTakeTime = GetNowHiPerformanceCount();

		// �t���[������1�ɖ߂�
		fps.frameCount = 1;
	}
	else
	{
		// �t���[�������J�E���g�A�b�v
		fps.frameCount++;
	}

	return;
}

void FPSDraw(void)
{
	DrawFormatString(0,0,0xffffff,"FPS:%3.1f",fps.average);
	
	return;
}

void FPSWait(void)
{
	// ���������Ƃ��ɑҋ@����~���b
	int wait = 0;

	// �҂����Ԃ��v��
	wait = 
		MicroSecond / GameFPS * fps.frameCount // ���z�̎���
		- (fps.nowTakeTime - fps.firstTakeTime);// ���ۂ̎���

	// �}�C�N���b���~���b�ɕϊ�
	wait /= MillSecond;

	// �҂����Ԃ�����Ȃ��
	if (wait > 0 && wait <= WaitTimeMill)
	{
		// ���b�Z�[�W���������Ȃ���҂�
		WaitTimer(wait);
	}

	return;

}

float GetDeltaTimes(void)
{
	return fps.deltatime;
}
