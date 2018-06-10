#include <Floppy.h>

int main()
{
    std::shared_ptr<Floppy> floppy = Floppy::getInstance();
	return 0;
}

