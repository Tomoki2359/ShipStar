#pragma once
#include <list>
#include <vector>

namespace Storage
{
	//データをストレージに送る関数
	void ThrowData(std::vector<char> command, std::vector<int> frame);

	//リプレイ用のデータを取得する関数
	void CopyData(std::list<char> &command, std::list<int> &frame);

	//保存されたゴーストデータを取得する関数
	void LoadData(std::list<char>& command, std::list<int>& frame);

	//選択されているコースのデータが存在するか
	///戻り値 : true = ある  false = ない
	bool ExistData();

	//記録が更新されたかを返す
	bool IsBreaked();
};