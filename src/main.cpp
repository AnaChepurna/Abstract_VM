#include "VirtualMachine.h"

int main(int argc, char **argv)
{
	VirtualMachine virtualMachine;
	for (int i = 1; i < argc; i++) {
		try {
			virtualMachine.setFlag(argv[i]);
		}
		catch (std::exception &e) {
			std::cout << "usage: " << std::endl;
			std::cout << "\t" << argv[0] << std::endl << "\t"<< argv[0] << " [filename]" << std::endl;
			std::cout << "\t" << "-errorIgnore : trying to execute code just ignore error lines (do not pass to absent exit int the end of program)" << std::endl;
			exit(0);
		}
	}
	virtualMachine.run();
	return (0);
}
