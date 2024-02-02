#include "pts/OpenProjectFactory.h"
#include "pts/OpenProject.h"

int main( int argc, char* argv[] )
{
	pts::OpenProjectFactory::getInstance()->createPts()->collectAllActiveProject();
	return 0;
}
