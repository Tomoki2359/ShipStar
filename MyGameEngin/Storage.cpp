#include "Storage.h"
#include <algorithm>

namespace Storage
{
	std::list<char> Data_Command;
	std::list<int> Data_Frame;

	void ThrowData(std::vector<char> command, std::vector<int> frame)
	{
		Data_Command.clear();
		Data_Frame.clear();

		size_t size = 0;
		
		while (size < command.size())
		{
			char datacom = command.at(size);
			Data_Command.push_back(datacom);
			int datafrm = frame.at(size);
			Data_Frame.push_back(datafrm);
			size++;
		}
	}

	void CopyData(std::list<char> &command, std::list<int> &frame)
	{
		command.clear();
		frame.clear();
		memcpy_s(&command, std::size(Data_Command), &Data_Command, std::size(Data_Command));
		memcpy_s(&frame, std::size(Data_Frame), &Data_Frame, std::size(Data_Frame));
	}
}
