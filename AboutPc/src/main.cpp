#include "pch.h";

int main()
{
	/* Device Specifications */

	std::cout << "\033[1;35m" << R"(
	  ______   _______    ______   __    __  ________        _______    ______  
	 /      \ |       \  /      \ |  \  |  \|        \      |       \  /      \ 
	|  $$$$$$\| $$$$$$$\|  $$$$$$\| $$  | $$ \$$$$$$$$      | $$$$$$$\|  $$$$$$\
	| $$__| $$| $$__/ $$| $$  | $$| $$  | $$   | $$         | $$__/ $$| $$   \$$
	| $$    $$| $$    $$| $$  | $$| $$  | $$   | $$         | $$    $$| $$      
	| $$$$$$$$| $$$$$$$\| $$  | $$| $$  | $$   | $$         | $$$$$$$ | $$   __ 
	| $$  | $$| $$__/ $$| $$__/ $$| $$__/ $$   | $$         | $$      | $$__/  \
	| $$  | $$| $$    $$ \$$    $$ \$$    $$   | $$         | $$       \$$    $$
	 \$$   \$$ \$$$$$$$   \$$$$$$   \$$$$$$     \$$          \$$        \$$$$$$ 
                                                                            
                                                                                                                                       
)" << "\033[1;31m" << "\n";

	// Device name
	char ComputerName[MAX_COMPUTERNAME_LENGTH + 1]{};
	DWORD dwSize = sizeof(ComputerName);

	GetComputerNameExA(ComputerNameDnsHostname, ComputerName, &dwSize);
	std::cout << "\tNAME: \t\t" << ComputerName << "\n";

	// Processor
	SYSTEM_INFO sysInfo{};
	GetSystemInfo(&sysInfo);

	DWORD sysThreads = sysInfo.dwNumberOfProcessors;

	WORD sysArchitecture = sysInfo.wProcessorArchitecture;

	switch (sysArchitecture)
	{
	case 9:
		std::cout << "\tArchitecture: \t" << "PROCESSOR_ARCHITECTURE_AMD64\n";
		break;
	case 5:
		std::cout << "\tArchitecture: \t" << "PROCESSOR_ARCHITECTURE_ARM\n";
		break;
	case 12:
		std::cout << "\tArchitecture: \t" << "PROCESSOR_ARCHITECTURE_ARM64 \n";
		break;
	case 6:
		std::cout << "\tArchitecture: \t" << "PROCESSOR_ARCHITECTURE_IA64 \n";
		break;
	case 0:
		std::cout << "\tArchitecture: \t" << "PROCESSOR_ARCHITECTURE_INTEL x86\n";
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		std::cout << "\tArchitecture: \t" << "PROCESSOR_ARCHITECTURE_UNKNOWN\n";
	default:
		break;
	}

	DWORD sysProcType = sysInfo.dwProcessorType;

	switch (sysProcType)
	{
	case 386:
		std::cout << "\tType: \t\t" << "PROCESSOR_INTEL_386\n";
	case 486:
		std::cout << "\tType: \t\t" << "PROCESSOR_INTEL_486 \n";
	case 586:
		std::cout << "\tType: \t\t" << "PROCESSOR_INTEL_PENTIUM \n";
	case 2200:
		std::cout << "\tType: \t\t" << "PROCESSOR_INTEL_IA64 \n";
	case 8664:
		std::cout << "\tType: \t\t" << "PROCESSOR_AMD_X8664\n";
	default:
		break;
	}

	DWORD byteSize = 0;
	GetLogicalProcessorInformation(NULL, &byteSize);

	int processorCount = byteSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);

	SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer =
		new SYSTEM_LOGICAL_PROCESSOR_INFORMATION[processorCount];
	GetLogicalProcessorInformation(buffer, &byteSize);

	int coreCount = 0;
	for (int i = 0; i < processorCount; i++)
	{
		if (buffer[i].Relationship == RelationProcessorCore)
			coreCount++;
	}

	std::cout << "\tPhysical cores: " << coreCount << std::endl;
	delete[] buffer;

	std::cout << "\tThreads: \t" << sysThreads << "\n";

	// Installed RAM
	MEMORYSTATUSEX memstatus{};
	memstatus.dwLength = sizeof(memstatus);
	GlobalMemoryStatusEx(&memstatus);

	double totalRAM = (double)(memstatus.ullTotalPhys) / 1073741824;
	std::cout << "\tTotal RAM: \t" << std::fixed << std::setprecision(1) << totalRAM << " GB" << std::endl;






	std::cin.get();
	return 0;
}