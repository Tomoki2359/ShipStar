#pragma once

class Transform;

namespace Time
{
	//‰Šú‰»
	void Initialize();

	//•b‚Ì‚İ•\¦‚É‚·‚é‚©‚Ç‚¤‚©
	//true = •b‚Ì‚İ
	//false = ’l‚É‰‚¶‚Ä/•ª‚Ì•\¦
	void SetDisplayMode(bool Mode);

	void Draw(int value, Transform tr);
	void Draw(float value, Transform tr);
};

