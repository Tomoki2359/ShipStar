#include "Storage.h"
#include <algorithm>

namespace Storage
{
	std::vector<char> Data_Command;
	std::vector<int> Data_Frame;

	void ThrowData(std::vector<char> command, std::vector<int> frame)
	{
		Data_Command.clear();
		Data_Frame.clear();
		
		Data_Command.reserve(command.size());
		Data_Frame.reserve(command.size());

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
}
