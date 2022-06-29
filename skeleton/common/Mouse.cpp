#include "Mouse.h"
//#include "geometory.h"

// �O���[�o���ϐ�
MousePoint nowPoint;//���݂̃}�E�X�̈ʒu
MousePoint oldPoint;//�ȑO�̃}�E�X�̈ʒu

int nowMousePressFrame[MouseKindMax];// ���݂̃}�E�X�̃{�^���������Ă���t���[�������Ǘ�
int oldMousePressFrame[MouseKindMax];// �ȑO�̃}�E�X�̃{�^���������Ă���t���[�������Ǘ�

int nowWheelValue;//���݂̃}�E�X�̃z�C�[����]��
int oldWheelValue;//�ȑO�̃}�E�X�̃z�C�[����]��

// �}�E�X�̃{�^���R�[�h�ƃt���[�������Ǘ����Ă���z��̗v�f����R�t����
int MouseCodeIndex[MouseKindMax]
{
    MOUSE_INPUT_LEFT,   // �z��̗v�f��0�ɂ̓}�E�X�̃{�^������0x0001�̏�������
    MOUSE_INPUT_RIGHT,  // �z��̗v�f��1�ɂ̓}�E�X�̃{�^������0x0002�̏�������
    MOUSE_INPUT_MIDDLE, // �z��̗v�f��2�ɂ̓}�E�X�̃{�^������0x0004�̏�������
    MOUSE_INPUT_4,      // �z��̗v�f��3�ɂ̓}�E�X�̃{�^������0x0008�̏�������
    MOUSE_INPUT_5,      // �z��̗v�f��4�ɂ̓}�E�X�̃{�^������0x0010�̏�������
    MOUSE_INPUT_6,      // �z��̗v�f��5�ɂ̓}�E�X�̃{�^������0x0020�̏�������
    MOUSE_INPUT_7,      // �z��̗v�f��6�ɂ̓}�E�X�̃{�^������0x0040�̏�������
    MOUSE_INPUT_8,      // �z��̗v�f��7�ɂ̓}�E�X�̃{�^������0x0080�̏�������
};

// Now???�n�̕ϐ��̒l��Old???�n�̕ϐ��֓����
void MouseNowIntoOld(void)
{
    oldPoint = nowPoint; //�}�E�X�̈ʒu

    // �t���[����
    for (int i = 0; i < MouseKindMax; i++)
    {
        oldMousePressFrame[i] = nowMousePressFrame[i];
    }

    // �z�C�[����
    oldWheelValue = nowWheelValue;

    return;
}
// �}�E�X�̃{�^���R�[�h��z��̗v�f���ɕϊ�����
int MouseCodeToIndex(int MOUSE_INPUT_)
{
    for (int i = 0; i < MouseKindMax; i++)
    {
        // �}�E�X�R�[�h���R�t������Ă���Ȃ�
        if (MouseCodeIndex[i] == MOUSE_INPUT_)
        {
            return i;   // ���̗v�f����Ԃ�
        }
    }

    // �}�E�X�R�[�h���Ȃ��Ȃ�G���[�I
    return MouseCodeErrIndex;
}

// �}�E�X�����̏�����
void MouseInit(void)
{
	// �}�E�X�̈ʒu
	nowPoint.x = 0;
	nowPoint.y = 0;

	//�t���[����
	for (int i = 0; i < MouseKindMax; i++)
	{
		nowMousePressFrame[i] = 0;
	}

	// �z�C�[����
	nowWheelValue = 0;

	// old�n��������
	MouseNowIntoOld();

	return;
}

// �}�E�X�����̍X�V
void MouseUpdate(int gameWidht,int gameheight)
{
	//�}�E�X�̃{�^���������ׂĎ擾
    int input;

    // ���݂̏����ȑO�̏��Ƃ��ĕۑ�
    MouseNowIntoOld();

    // ���݂̃}�E�X�̃N���C�A���g���W�̈ʒu���擾
    GetMousePoint(&nowPoint.x,&nowPoint.y);

    // �����A�}�E�X�̍��W���Q�[����ʊO�ɂ���Ȃ�A�Q�[����ʓ��Ɏ��߂�
    if (nowPoint.x < 0)
    {
        nowPoint.x = 0; //��
    }
    else if (nowPoint.x > gameWidht)
    {
        nowPoint.x = gameWidht;// �E
    }
    if (nowPoint.y < 0)
    {
        nowPoint.y = 0; // ��
    }
    else if (nowPoint.y > gameheight)
    {
        nowPoint.y = gameheight;// ��
    }

    // �}�E�X�̃{�^��������C�Ɏ擾
    input = GetMouseInput();

    // �e�{�^���������Ă��邩�`�F�b�N
    for (int i = 0; i < MouseKindMax; i++)
    {
        //�yif���̏����̐����z
        // �擾�����}�E�X�R�[�h�Ń}�X�N�������ʂ��A���̃}�E�X�R�[�h�Ȃ��
        // ��) �擾�����l��0x0007      ���@�Ō�̃o�C�g���@00000111�@�̏ꍇ
        //    �}�E�X�R�[�h��0x001(��)  ���@�Ō�̃o�C�g���@00000001�@��
        // �_���ςŃ}�X�N����(�㉺�Ƃ�1�Ȃ�1/����ȊO��0)& ---------
        //                  ����0x0001 ���@�Ō�̃o�C�g���@00000001�@�ƂȂ�
        // �����̒l�������Ă��Ă��A�}�X�N����������΁A����̒l�̂ݒ��o�ł���I
        // ?�^�T�C�g�ł́AInput & 1<<i�Ƃ��Ă���B�i���V�t�g��1�̃r�b�g�����炷�j
        if ((input & MouseCodeIndex[i]) == MouseCodeIndex[i])
        {
            // ���݉����Ă���{�^���̃t���[�������J�E���g�A�b�v
            nowMousePressFrame[i]++;
        }
        else if ((input & MouseCodeIndex[i]) != MouseCodeIndex[i])
        {
            // ���݉����Ă���{�^���̃t���[�������[���N���A
            nowMousePressFrame[i] = 0;
        }
    }

    // �z�C�[���̉�]�ʂ��擾
    nowWheelValue = GetMouseWheelRotVol();


    return;
}

// ����̃{�^�������������H 
// �����FDX���C�u�����̃}�E�X�R�[�h�iMOUSE_INPUT_�Ŏn�܂�}�N����`�j
bool MouseDown(int MOUSE_INPUT_)
{
    // �}�E�X�R�[�h��z��̗v�f���ɕϊ�
    int index = MouseCodeToIndex(MOUSE_INPUT_);

    // ���݂���}�E�X�R�[�h�Ȃ�
    if (index != MouseCodeErrIndex)
    {
        // ���݉����Ă���Ȃ�
        if (nowMousePressFrame[index] > 0)
        {
            return true;		//�����Ă���
        }
    }

    return false;		// �����Ă��Ȃ�
}

// ����̃{�^�����N���b�N�������H
// �����FDX���C�u�����̃}�E�X�R�[�h�iMOUSE_INPUT_�Ŏn�܂�}�N����`�j
// �����F�u�{�^�����������{�^�����グ��v���Z�b�g�ōs��ꂽ�����A�N���b�N
bool MouseClick(int MOUSE_INPUT_)
{
    // �}�E�X�R�[�h��z��̗v�f���ɕϊ�
    int index = MouseCodeToIndex(MOUSE_INPUT_);

    // ���݂���}�E�X�R�[�h�Ȃ�
    if (index != MouseCodeErrIndex)
    {
        if (nowMousePressFrame[index] == 0  // ���݂͉����Ă�����
            && oldMousePressFrame[index] > 0)// �ȑO�͉����Ă���
        {
            return true;		//�����Ă���
        }
    }
    return false;		// �����Ă��Ȃ�
}

// ����̃{�^�����������t���[����
// �����FDX���C�u�����̃}�E�X�R�[�h�iMOUSE_INPUT_�Ŏn�܂�}�N����`�j
// ���ӁF�߂�l�̓~���b�Ȃǂł͂Ȃ��A�t���[�����I
int MousePressFrame(int MOUSE_INPUT_)
{
    // �}�E�X�R�[�h��z��̗v�f���ɕϊ�
    int index = MouseCodeToIndex(MOUSE_INPUT_);

    // ���݂���}�E�X�R�[�h�Ȃ�
    if (index != MouseCodeErrIndex)
    {
        return nowMousePressFrame[MOUSE_INPUT_];
    }

    return 0;
}

// �}�E�X�̌��݈ʒu���擾����
MousePoint GetPointMouse(void)
{
    return nowPoint;
}

// �}�E�X�̈ȑO�̈ʒu���擾����
MousePoint GetOldPointMouse(void)
{
    return oldPoint;
}

// �}�E�X�̈ˑR�ƌ��݂̈ʒu�̍����擾����
MousePoint GetDiffPointMouse(void)
{
    MousePoint diff;

    diff.x = oldPoint.x - nowPoint.x;
    diff.y = oldPoint.y - nowPoint.y;

    return diff;
}

// �}�E�X�̌��݃z�C�[���l���擾����
int GetWheelMouse(void)
{
    return nowWheelValue;
}

// ��`�ƃ}�E�X�̓_���������Ă��邩�H
bool CollRectToMousePoint(RECT rect)
{
    if (rect.left <= nowPoint.x &&
        rect.top <= nowPoint.y &&
        rect.right >= nowPoint.x &&
        rect.bottom >= nowPoint.y)
    {
        // �������Ă���
        return true;
    }

    // �������Ă��Ȃ�
    return false;
}

// ��ʂƃ}�E�X�̓_���������Ă��邩�H
bool CollWindowToMousePoint(int gameWidth, int gameHeight)
{
    RECT window; // ��ʂ̋�`

    window.left = 0;
    window.top = 0;
    window.right = gameWidth;
    window.bottom = gameHeight;

    // ���̊֐��̌��ʂ����̂܂ܕԂ�
    return CollRectToMousePoint(window);
}

//��`���Ń}�E�X�̃{�^�������������H
bool CollRectToMouseDown(RECT rect, int MOUSE_INPUT_)
{
    //��`����
    if (CollRectToMousePoint(rect))
    {
        // �{�^������������
        if (MouseDown(MOUSE_INPUT_))
        {
            // ������
            return true;
        }
    }
    // �����Ă��Ȃ�
    return false;
}

//��`���Ń}�E�X�̃{�^�����N���b�N�������H
bool CollRectToMouseClick(RECT rect, int MOUSE_INPUT_)
{
    //��`����
    if (CollRectToMousePoint(rect))
    {
        // �{�^�����N���b�N������
        if (MouseClick(MOUSE_INPUT_))
        {
            // ������
            return true;
        }
    }
    // �����Ă��Ȃ�
    return false;
}

//��ʂ̂ǂ����łŃ}�E�X�̃{�^�������������H
bool CollWindowToMouseDown(int gameWidth, int gameHeight,int MOUSE_INPUT_)
{
    //��ʓ���
    if (CollWindowToMousePoint(gameWidth, gameHeight))
    {
        // �{�^�����N���b�N������
        if (MouseDown(MOUSE_INPUT_))
        {
            // ������
            return true;
        }
    }
    // �����Ă��Ȃ�
    return false;
}

//��ʂ̂ǂ����Ń}�E�X�̃{�^�����N���b�N�������H
bool CollWindowToMouseClick(int gameWidth, int gameHeight,int MOUSE_INPUT_)
{
    //��ʓ���
    if (CollWindowToMousePoint(gameWidth,gameHeight))
    {
        // �{�^�����N���b�N������
        if (MouseClick(MOUSE_INPUT_))
        {
            // ������
            return true;
        }
    }
    // �����Ă��Ȃ�
    return false;
}

