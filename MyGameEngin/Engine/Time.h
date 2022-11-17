#pragma once

class Transform;

namespace Time
{
	//初期化
	void Initialize();

	//秒のみ表示にするかどうか
	//true = 秒のみ
	//false = 値に応じて時/分の表示
	void SetDisplayMode(bool Mode);

	void Draw(int value, Transform tr);
	void Draw(float value, Transform tr);
};

