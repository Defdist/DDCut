#include "DDUpdater.h"

#include <iostream>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		return -1;
	}

	std::cout << argv[1];
	DDUpdater().UpdateDDCut(argv[1]);

	system("pause");

	return 1;
}