#include "VirtualMachine.h"

int main(int argc, char **argv)
{
	VirtualMachine virtualMachine;
	if (argc == 2)
		virtualMachine.setFile(argv[1]);
	virtualMachine.run();
	return (0);
}