#pragma once
#include <string>
#include <vector>
#include <Windows.h>

class CSVReader
{
	//�ǂݍ��񂾃f�[�^���i�[����񎟌��z��
	std::vector<std::vector<std::string>> Data_;

	//�R���}�����s���s����܂ł̕�������擾
	void GetToComma(std::string* result, std::string data, DWORD* index);
public:
	CSVReader();
	~CSVReader();

	bool Load(std::string FileName);		//�����Ɏw�肵�����O�̃t�@�C����ǂݍ��ފ֐�
	std::string GetString(DWORD x, DWORD y);//�w��ʒu�𕶎���Ŏ擾
	int GetValue(DWORD x, DWORD y);			//�w��ʒu�𐔒l�Ŏ擾

	size_t GetWidth() { return Data_[0].size(); }	//�t�@�C���̉������擾
	size_t GetHeight() { return Data_.size(); }		//�t�@�C���̏c�̒������擾
};