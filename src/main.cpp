#include "domain/PtsDataCollector.h"

int main( int argc, char* argv[] )
{
	measurementor::PtsDataCollector collector;
	collector.correctData();
	collector.permanentProjectData();
	return 0;
}
