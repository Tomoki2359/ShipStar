#pragma once
#include <string>
#include <vector>
#include <Windows.h>

class CSVReader
{
	//読み込んだデータを格納する二次元配列
	std::vector<std::vector<std::string>> Data_;

	//コンマか改行が行われるまでの文字列を取得
	void GetToComma(std::string* result, std::string data, DWORD* index);
public:
	CSVReader();
	~CSVReader();

	bool Load(std::string FileName);		//引数に指定した名前のファイルを読み込む関数
	std::string GetString(DWORD x, DWORD y);//指定位置を文字列で取得
	int GetValue(DWORD x, DWORD y);			//指定位置を数値で取得

	size_t GetWidth() { return Data_[0].size(); }	//ファイルの横幅を取得
	size_t GetHeight() { return Data_.size(); }		//ファイルの縦の長さを取得
};