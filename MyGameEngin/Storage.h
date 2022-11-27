#pragma once
#include <list>
#include <vector>

namespace Storage
{
	void ThrowData(std::vector<char> command, std::vector<int> frame);
	void CopyData(std::list<char> &command, std::list<int> &frame);
};