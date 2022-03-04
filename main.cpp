
// main.cpp


#include "tree.h"


int main ()
{
	tree_t *root = NULL;

	ReadCommands (&root);

	GraphDumpTree (root);

	return 0;
}
