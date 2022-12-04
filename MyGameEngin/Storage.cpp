#include "Storage.h"
#include "Engine/Time.h"
#include "Option.h"
#include <algorithm>
#include <Windows.h>

namespace Storage
{
	std::vector<char> Data_Command;
	std::vector<int> Data_Frame;

	std::vector<char> Load_Command;	//�t�@�C������ǂݍ��񂾃f�[�^���i�[
	std::vector<int> Load_Frame;

	float ClearTime;
	float LoadTime;

	void Save();
	bool Load();	//�ǂݎ�莸�s������false��Ԃ�

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

		if (Load())	//Load�ɐ��������ꍇ
		{
			if (ClearTime < LoadTime)	//Load�œǂݎ�������Ԃ��Clear�̕������������ꍇ
			{
				Save();
			}
		}
		else //�f�[�^�����݂��Ȃ������ꍇ
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
			hFile,						//�t�@�C���n���h��
			wtext,						//�ۑ�������������
			(int)(data.length() * 2),	//�ۑ����镶����
			&bytes,						//�ۑ������T�C�Y
			NULL
		);

		CloseHandle(hFile);			//�t�@�C�������
	}

	bool Load()
	{
		std::string strName = "SaveData\\" + Option::GetCourseName() + ".data";
		wchar_t fileName[MAX_PATH];
		size_t ret;
		mbstowcs_s(&ret, fileName, strName.c_str(), strName.length());

		HANDLE hFile = CreateFile
		(
			fileName,		//�t�@�C����
			GENERIC_READ,			//�A�N�Z�X���[�h
			NULL,
			NULL,
			OPEN_EXISTING,			//�쐬���@
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFile);
			return false;
		}

		//�t�@�C���̃T�C�Y���擾
		DWORD fileSize = GetFileSize(hFile, NULL);

		//�t�@�C���̃T�C�Y�����������m��
		wchar_t* data = new wchar_t[fileSize];

		DWORD dwBytes = 0; //�ǂݍ��݈ʒu

		bool read = ReadFile(
			hFile,     //�t�@�C���n���h��
			data,      //�f�[�^������ϐ�
			fileSize,  //�ǂݍ��ރT�C�Y
			&dwBytes,  //�ǂݍ��񂾃T�C�Y
			NULL);     //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j

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
		//���Ԃ��擾
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
			//command�����̎擾
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
			//frame�����̎擾
			j = j * adjust + _wtoi(&data[i]);	//���Y�^ : wtoi�͐��l�Ƃ��ĔF���ł��镔���܂ň�x�ɉ���ł���
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