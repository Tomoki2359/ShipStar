#include "Storage.h"
#include "Engine/Time.h"
#include "Option.h"
#include <algorithm>
#include <Windows.h>

namespace Storage
{
	std::vector<char> Data_Command;
	std::vector<int> Data_Frame;

	std::vector<char> Load_Command;	//ファイルから読み込んだデータを格納
	std::vector<int> Load_Frame;

	float ClearTime;
	float LoadTime;

	void Save();
	bool Load();	//読み取り失敗したらfalseを返す

	void ThrowData(std::vector<char> command, std::vector<int> frame)
	{
		Data_Command.clear();
		Data_Frame.clear();

		Data_Command.reserve(command.size());
		Data_Frame.reserve(command.size());

		ClearTime = Time::GetTime();

		size_t size = 0;

		while (size < command.size())
		{
			char datacom = command.at(size);
			Data_Command.push_back(datacom);
			int datafrm = frame.at(size);
			Data_Frame.push_back(datafrm);
			size++;
		}

		if (Load())	//Loadに成功した場合
		{
			if (ClearTime < LoadTime)	//Loadで読み取った時間よりClearの方が早かった場合
			{
				Save();
			}
		}
		else //データが存在しなかった場合
		{
			Save();
		}
	}

	void CopyData(std::list<char>& command, std::list<int>& frame)
	{
		command.clear();
		frame.clear();

		size_t size = 0;
		while (size < Data_Command.size())
		{
			char datacom = Data_Command.at(size);
			command.push_back(datacom);
			int datafrm = Data_Frame.at(size);
			frame.push_back(datafrm);
			size++;
		}
	}

	void LoadData(std::list<char>& command, std::list<int>& frame)
	{
		if (Load())
		{
			command.clear();
			frame.clear();

			size_t size = 0;
			while (size < Load_Command.size())
			{
				char datacom = Load_Command.at(size);
				command.push_back(datacom);
				int datafrm = Load_Frame.at(size);
				frame.push_back(datafrm);
				size++;
			}
		}
	}

	void Save()
	{
		std::string strName = "SaveData\\" + Option::GetCourseName() + ".data";
		wchar_t fileName[MAX_PATH];
		size_t ret;
		mbstowcs_s(&ret, fileName, strName.c_str(), strName.length());
		HANDLE hFile = CreateFile
		(
			fileName,
			GENERIC_WRITE,
			NULL,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		std::string data = std::to_string(ClearTime) + "\n";

		for (int x = 0; x < Data_Command.size(); x++)
		{
			data += std::to_string(Data_Command.at(x)) + "," + std::to_string(Data_Frame.at(x)) + "\n";
		}

		wchar_t wtext[0x0fff];
		mbstowcs_s(&ret, wtext, data.c_str(), data.length());

		DWORD bytes = 0;
		WriteFile(
			hFile,						//ファイルハンドル
			wtext,						//保存したい文字列
			(int)(data.length() * 2),	//保存する文字数
			&bytes,						//保存したサイズ
			NULL
		);

		CloseHandle(hFile);			//ファイルを閉じる
	}

	bool Load()
	{
		std::string strName = "SaveData\\" + Option::GetCourseName() + ".data";
		wchar_t fileName[MAX_PATH];
		size_t ret;
		mbstowcs_s(&ret, fileName, strName.c_str(), strName.length());

		HANDLE hFile = CreateFile
		(
			fileName,		//ファイル名
			GENERIC_READ,			//アクセスモード
			NULL,
			NULL,
			OPEN_EXISTING,			//作成方法
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFile);
			return false;
		}

		//ファイルのサイズを取得
		DWORD fileSize = GetFileSize(hFile, NULL);

		//ファイルのサイズ分メモリを確保
		wchar_t* data = new wchar_t[fileSize];

		DWORD dwBytes = 0; //読み込み位置

		bool read = ReadFile(
			hFile,     //ファイルハンドル
			data,      //データを入れる変数
			fileSize,  //読み込むサイズ
			&dwBytes,  //読み込んだサイズ
			NULL);     //オーバーラップド構造体（今回は使わない）

		if (read == false)
		{
			CloseHandle(hFile);
			return false;
		}

		Load_Command.clear();
		Load_Frame.clear();

		int x = 0, z = 0;
		int i = 0;
		wchar_t time[16] = L"";
		//時間を取得
		while (data[i] != L'\n')
		{
			time[i] = data[i];
			i++;
		}
		LoadTime = wcstof(time, NULL);
		i++;

		while (data[i] != EOF)
		{
			const char adjust = 10;

			int j = 0;
			//command部分の取得
			while (data[i] != L',')
			{
				j = j * adjust + _wtoi(&data[i]);
				i++;
			}
			if (j >= adjust)
			{
				j = j / adjust;
			}
			Load_Command.push_back(j);

			i++;

			j = 0;
			//frame部分の取得
			j = j * adjust + _wtoi(&data[i]);	//備忘録 : wtoiは数値として認識できる部分まで一度に回収できる
			int digit = (int)log10(j);
			if (digit < 0)
			{
				digit = 0;
			}
			i += digit;
			Load_Frame.push_back(j);

			i++;

			if (data[i] == L'\0')
			{
				break;
			}
		}

		CloseHandle(hFile);
		return true;
	}
}