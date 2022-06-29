#include "Mouse.h"
//#include "geometory.h"

// グローバル変数
MousePoint nowPoint;//現在のマウスの位置
MousePoint oldPoint;//以前のマウスの位置

int nowMousePressFrame[MouseKindMax];// 現在のマウスのボタンを押しているフレーム数を管理
int oldMousePressFrame[MouseKindMax];// 以前のマウスのボタンを押しているフレーム数を管理

int nowWheelValue;//現在のマウスのホイール回転量
int oldWheelValue;//以前のマウスのホイール回転量

// マウスのボタンコードとフレーム数を管理している配列の要素数を紐付ける
int MouseCodeIndex[MouseKindMax]
{
    MOUSE_INPUT_LEFT,   // 配列の要素数0にはマウスのボタン情報の0x0001の情報を入れる
    MOUSE_INPUT_RIGHT,  // 配列の要素数1にはマウスのボタン情報の0x0002の情報を入れる
    MOUSE_INPUT_MIDDLE, // 配列の要素数2にはマウスのボタン情報の0x0004の情報を入れる
    MOUSE_INPUT_4,      // 配列の要素数3にはマウスのボタン情報の0x0008の情報を入れる
    MOUSE_INPUT_5,      // 配列の要素数4にはマウスのボタン情報の0x0010の情報を入れる
    MOUSE_INPUT_6,      // 配列の要素数5にはマウスのボタン情報の0x0020の情報を入れる
    MOUSE_INPUT_7,      // 配列の要素数6にはマウスのボタン情報の0x0040の情報を入れる
    MOUSE_INPUT_8,      // 配列の要素数7にはマウスのボタン情報の0x0080の情報を入れる
};

// Now???系の変数の値をOld???系の変数へ入れる
void MouseNowIntoOld(void)
{
    oldPoint = nowPoint; //マウスの位置

    // フレーム数
    for (int i = 0; i < MouseKindMax; i++)
    {
        oldMousePressFrame[i] = nowMousePressFrame[i];
    }

    // ホイール量
    oldWheelValue = nowWheelValue;

    return;
}
// マウスのボタンコードを配列の要素数に変換する
int MouseCodeToIndex(int MOUSE_INPUT_)
{
    for (int i = 0; i < MouseKindMax; i++)
    {
        // マウスコードが紐付けされているなら
        if (MouseCodeIndex[i] == MOUSE_INPUT_)
        {
            return i;   // その要素数を返す
        }
    }

    // マウスコードがないならエラー！
    return MouseCodeErrIndex;
}

// マウス処理の初期化
void MouseInit(void)
{
	// マウスの位置
	nowPoint.x = 0;
	nowPoint.y = 0;

	//フレーム数
	for (int i = 0; i < MouseKindMax; i++)
	{
		nowMousePressFrame[i] = 0;
	}

	// ホイール量
	nowWheelValue = 0;

	// old系も初期化
	MouseNowIntoOld();

	return;
}

// マウス処理の更新
void MouseUpdate(int gameWidht,int gameheight)
{
	//マウスのボタン情報をすべて取得
    int input;

    // 現在の情報を以前の情報として保存
    MouseNowIntoOld();

    // 現在のマウスのクライアント座標の位置を取得
    GetMousePoint(&nowPoint.x,&nowPoint.y);

    // もし、マウスの座標がゲーム画面外にあるなら、ゲーム画面内に収める
    if (nowPoint.x < 0)
    {
        nowPoint.x = 0; //左
    }
    else if (nowPoint.x > gameWidht)
    {
        nowPoint.x = gameWidht;// 右
    }
    if (nowPoint.y < 0)
    {
        nowPoint.y = 0; // 上
    }
    else if (nowPoint.y > gameheight)
    {
        nowPoint.y = gameheight;// 下
    }

    // マウスのボタン情報を一気に取得
    input = GetMouseInput();

    // 各ボタンを押しているかチェック
    for (int i = 0; i < MouseKindMax; i++)
    {
        //【if文の条件の説明】
        // 取得したマウスコードでマスクした結果が、そのマウスコードならば
        // 例) 取得した値が0x0007      →　最後のバイトが　00000111　の場合
        //    マウスコードが0x001(左)  →　最後のバイトが　00000001　で
        // 論理積でマスク処理(上下とも1なら1/それ以外は0)& ---------
        //                  結果0x0001 →　最後のバイトが　00000001　となる
        // 複数の値が入っていても、マスク処理をすれば、特定の値のみ抽出できる！
        // ?某サイトでは、Input & 1<<iとしている。（左シフトで1のビットをずらす）
        if ((input & MouseCodeIndex[i]) == MouseCodeIndex[i])
        {
            // 現在押しているボタンのフレーム数をカウントアップ
            nowMousePressFrame[i]++;
        }
        else if ((input & MouseCodeIndex[i]) != MouseCodeIndex[i])
        {
            // 現在押しているボタンのフレーム数をゼロクリア
            nowMousePressFrame[i] = 0;
        }
    }

    // ホイールの回転量を取得
    nowWheelValue = GetMouseWheelRotVol();


    return;
}

// 特定のボタンを押したか？ 
// 引数：DXライブラリのマウスコード（MOUSE_INPUT_で始まるマクロ定義）
bool MouseDown(int MOUSE_INPUT_)
{
    // マウスコードを配列の要素数に変換
    int index = MouseCodeToIndex(MOUSE_INPUT_);

    // 実在するマウスコードなら
    if (index != MouseCodeErrIndex)
    {
        // 現在押しているなら
        if (nowMousePressFrame[index] > 0)
        {
            return true;		//押している
        }
    }

    return false;		// 押していない
}

// 特定のボタンをクリックしたか？
// 引数：DXライブラリのマウスコード（MOUSE_INPUT_で始まるマクロ定義）
// 説明：「ボタンを押す→ボタンを上げる」がセットで行われた時が、クリック
bool MouseClick(int MOUSE_INPUT_)
{
    // マウスコードを配列の要素数に変換
    int index = MouseCodeToIndex(MOUSE_INPUT_);

    // 実在するマウスコードなら
    if (index != MouseCodeErrIndex)
    {
        if (nowMousePressFrame[index] == 0  // 現在は押していたが
            && oldMousePressFrame[index] > 0)// 以前は押していた
        {
            return true;		//押している
        }
    }
    return false;		// 押していない
}

// 特定のボタンを押したフレーム数
// 引数：DXライブラリのマウスコード（MOUSE_INPUT_で始まるマクロ定義）
// 注意：戻り値はミリ秒などではなく、フレーム数！
int MousePressFrame(int MOUSE_INPUT_)
{
    // マウスコードを配列の要素数に変換
    int index = MouseCodeToIndex(MOUSE_INPUT_);

    // 実在するマウスコードなら
    if (index != MouseCodeErrIndex)
    {
        return nowMousePressFrame[MOUSE_INPUT_];
    }

    return 0;
}

// マウスの現在位置を取得する
MousePoint GetPointMouse(void)
{
    return nowPoint;
}

// マウスの以前の位置を取得する
MousePoint GetOldPointMouse(void)
{
    return oldPoint;
}

// マウスの依然と現在の位置の差を取得する
MousePoint GetDiffPointMouse(void)
{
    MousePoint diff;

    diff.x = oldPoint.x - nowPoint.x;
    diff.y = oldPoint.y - nowPoint.y;

    return diff;
}

// マウスの現在ホイール値を取得する
int GetWheelMouse(void)
{
    return nowWheelValue;
}

// 矩形とマウスの点が当たっているか？
bool CollRectToMousePoint(RECT rect)
{
    if (rect.left <= nowPoint.x &&
        rect.top <= nowPoint.y &&
        rect.right >= nowPoint.x &&
        rect.bottom >= nowPoint.y)
    {
        // 当たっている
        return true;
    }

    // 当たっていない
    return false;
}

// 画面とマウスの点が当たっているか？
bool CollWindowToMousePoint(int gameWidth, int gameHeight)
{
    RECT window; // 画面の矩形

    window.left = 0;
    window.top = 0;
    window.right = gameWidth;
    window.bottom = gameHeight;

    // この関数の結果をそのまま返す
    return CollRectToMousePoint(window);
}

//矩形内でマウスのボタンを押したか？
bool CollRectToMouseDown(RECT rect, int MOUSE_INPUT_)
{
    //矩形内で
    if (CollRectToMousePoint(rect))
    {
        // ボタンを押したか
        if (MouseDown(MOUSE_INPUT_))
        {
            // 押した
            return true;
        }
    }
    // 押していない
    return false;
}

//矩形内でマウスのボタンをクリックしたか？
bool CollRectToMouseClick(RECT rect, int MOUSE_INPUT_)
{
    //矩形内で
    if (CollRectToMousePoint(rect))
    {
        // ボタンをクリックしたか
        if (MouseClick(MOUSE_INPUT_))
        {
            // 押した
            return true;
        }
    }
    // 押していない
    return false;
}

//画面のどこかででマウスのボタンを押したか？
bool CollWindowToMouseDown(int gameWidth, int gameHeight,int MOUSE_INPUT_)
{
    //画面内で
    if (CollWindowToMousePoint(gameWidth, gameHeight))
    {
        // ボタンをクリックしたか
        if (MouseDown(MOUSE_INPUT_))
        {
            // 押した
            return true;
        }
    }
    // 押していない
    return false;
}

//画面のどこかでマウスのボタンをクリックしたか？
bool CollWindowToMouseClick(int gameWidth, int gameHeight,int MOUSE_INPUT_)
{
    //画面内で
    if (CollWindowToMousePoint(gameWidth,gameHeight))
    {
        // ボタンをクリックしたか
        if (MouseClick(MOUSE_INPUT_))
        {
            // 押した
            return true;
        }
    }
    // 押していない
    return false;
}

