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
};