#include "VirtualMachine.h"

int main(int argc, char **argv)
{
	VirtualMachine virtualMachine;
	for (int i = 1; i < argc; i++) {
		try {
			virtualMachine.setFlag(argv[i]);
		}
		catch (std::exception &e) {
			std::cout << argv[0] << std::endl << argv[0] << " [filename]" << std::endl;
			std::cout << "-errorIgnore - trying to execute code just ignore error lines" << std::endl;
			exit(0);
		}
	}
	virtualMachine.run();
	while (42) {};
	return (0);
}