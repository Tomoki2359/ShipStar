#include "CSVReader.h"
#include <assert.h>

void CSVReader::GetToComma(std::string* result, std::string data, DWORD* index)
{
	//「,」まで一文字ずつresultに入れる
	while (data[*index] != ',' && data[*index] != '\n' && data[*index] != '\r')
	{
		*result += data[*index];
		(*index)++;
	}

	//最後に「\0」を付ける
	*result += '\0';
	(*index)++;
}

CSVReader::CSVReader()
{
	Data_.clear();
}

CSVReader::~CSVReader()
{
	for (int y = 0; y < Data_.size(); y++)
	{
		for (int x = 0; x < Data_[y].size(); x++)
		{
			Data_[y][x].clear();
		}
	}
}

bool CSVReader::Load(std::string FileName)
{
	HANDLE hFile;
	wchar_t name[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, name, FileName.c_str(), FileName.length());
	hFile = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//ファイルが開けなかった場合
	if (hFile == INVALID_HANDLE_VALUE)
	{
		LPCWSTR message = L"ファイルを開けませんでした。\n開いている場合は閉じてください。";
		MessageBox(NULL, message, L"BaseProjDx9エラー", MB_OK);
		return false;
	}

	//ファイルのサイズ（文字数）を調べる
	DWORD fileSize = GetFileSize(hFile, NULL);

	//すべての文字を入れられる配列を用意
	char* temp;
	temp = new char[fileSize];

	//ファイルの中身を配列に読み込む
	DWORD dwBytes = NULL;
	bool SuccessRead = ReadFile(hFile, temp, fileSize, &dwBytes, NULL);
	assert(SuccessRead == true);

	//開いたファイルを閉じる
	CloseHandle(hFile);

	//1行のデータを入れる配列
	std::vector<std::string>	line;
	//調べる文字の位置
	DWORD index = 0;

	//最後の文字まで繰り返す
	while (index < fileSize)
	{
		//index文字目から「,」か「改行」までの文字列を取得
		std::string val;
		GetToComma(&val, temp, &index);

		//文字数が0だったということは行末
		if (val.length() - 1 == 0)
		{
			//_dataに1行分追加
			Data_.push_back(line);

			//1行データをクリア
			line.clear();

			//index++;
			continue;
		}

		//1行分のデータに追加
		line.push_back(val);
	}

	//読み込んだデータは開放する
	delete[] temp;

	//成功
	return true;
}

std::string CSVReader::GetString(DWORD x, DWORD y)
{
	if (x < 0 || x >= GetWidth() || y < 0 || y >= GetHeight())
		return "";

	return Data_[y][x];
}

int CSVReader::GetValue(DWORD x, DWORD y)
{
	return atoi(GetString(x, y).c_str());
}
