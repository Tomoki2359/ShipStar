#include "CSVReader.h"
#include <assert.h>

void CSVReader::GetToComma(std::string* result, std::string data, DWORD* index)
{
	//�u,�v�܂ňꕶ������result�ɓ����
	while (data[*index] != ',' && data[*index] != '\n' && data[*index] != '\r')
	{
		*result += data[*index];
		(*index)++;
	}

	//�Ō�Ɂu\0�v��t����
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

	//�t�@�C�����J���Ȃ������ꍇ
	if (hFile == INVALID_HANDLE_VALUE)
	{
		LPCWSTR message = L"�t�@�C�����J���܂���ł����B\n�J���Ă���ꍇ�͕��Ă��������B";
		MessageBox(NULL, message, L"BaseProjDx9�G���[", MB_OK);
		return false;
	}

	//�t�@�C���̃T�C�Y�i�������j�𒲂ׂ�
	DWORD fileSize = GetFileSize(hFile, NULL);

	//���ׂĂ̕�����������z���p��
	char* temp;
	temp = new char[fileSize];

	//�t�@�C���̒��g��z��ɓǂݍ���
	DWORD dwBytes = NULL;
	bool SuccessRead = ReadFile(hFile, temp, fileSize, &dwBytes, NULL);
	assert(SuccessRead == true);

	//�J�����t�@�C�������
	CloseHandle(hFile);

	//1�s�̃f�[�^������z��
	std::vector<std::string>	line;
	//���ׂ镶���̈ʒu
	DWORD index = 0;

	//�Ō�̕����܂ŌJ��Ԃ�
	while (index < fileSize)
	{
		//index�����ڂ���u,�v���u���s�v�܂ł̕�������擾
		std::string val;
		GetToComma(&val, temp, &index);

		//��������0�������Ƃ������Ƃ͍s��
		if (val.length() - 1 == 0)
		{
			//_data��1�s���ǉ�
			Data_.push_back(line);

			//1�s�f�[�^���N���A
			line.clear();

			//index++;
			continue;
		}

		//1�s���̃f�[�^�ɒǉ�
		line.push_back(val);
	}

	//�ǂݍ��񂾃f�[�^�͊J������
	delete[] temp;

	//����
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
