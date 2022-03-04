
// tree.cpp


#include "tree.h"


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int NodeCtor (tree_t **tree_ptr, data_t data)
{
	*tree_ptr = (tree_t*) calloc (1, sizeof (tree_t));

	(*tree_ptr)->data = data;
	(*tree_ptr)->left_branch  = NULL;
	(*tree_ptr)->right_branch = NULL;

	return 0;
}


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
tree_t *TreeAdd (tree_t **tree_ptr, data_t data)
{
	if ((*tree_ptr) == NULL)
	{
		NodeCtor (tree_ptr, data);
	}
	else if (data < (*tree_ptr)->data)
	{
		(*tree_ptr)->left_branch = TreeAdd (&((*tree_ptr)->left_branch), data);
	}
	else
	{
		(*tree_ptr)->right_branch = TreeAdd (&((*tree_ptr)->right_branch), data);
	}
	
	return *tree_ptr;
}


int TreePrintSymmetric (tree_t *tree_ptr)
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
{
	if (tree_ptr == NULL)
	{
		return 0;
	}
		
	TreePrintSymmetric (tree_ptr->left_branch);
	printf (" %d ", tree_ptr->data);
	TreePrintSymmetric (tree_ptr->right_branch);

	return 0;
}	


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int TreePrintDirect (tree_t *tree_ptr)
{
	if (tree_ptr == NULL)
	{
		return 0;
	}

	printf (" %d ", tree_ptr->data);
	TreePrintDirect (tree_ptr->left_branch);
	TreePrintDirect (tree_ptr->right_branch);

	return 0;
}


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int TreePrintBack (tree_t *tree_ptr)
{
	if (tree_ptr == NULL)
	{
		return 0;
	}
	
	
	TreePrintBack (tree_ptr->left_branch);
	TreePrintBack (tree_ptr->right_branch);
	printf (" %d ", tree_ptr->data);

	return 0;
}
	

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
tree_t *NodeInsert (tree_t *tree_after_ptr, data_t data,
					int is_left, int is_left_branch)
{
	assert (tree_after_ptr != NULL);

	tree_t *new_tree_ptr = NULL;
	NodeCtor (&new_tree_ptr, data);

	if (is_left)
	{
		if (is_left_branch)
		{
			new_tree_ptr->left_branch = tree_after_ptr->left_branch;
		}
		else
		{
			new_tree_ptr->right_branch = tree_after_ptr->left_branch;
	 	}

		tree_after_ptr->left_branch = new_tree_ptr;
	}
	else
	{
		if (is_left_branch)
		{
			new_tree_ptr->left_branch = tree_after_ptr->right_branch;
		}
		else
		{
			new_tree_ptr->right_branch = tree_after_ptr->right_branch;
		}

		tree_after_ptr->right_branch = new_tree_ptr;
	}

	return new_tree_ptr;
}


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int NodeDelete (tree_t **tree_ptr_ptr)
{
	if (*tree_ptr_ptr == NULL)
	{
		return 0;
	}

	NodeDelete (&((*tree_ptr_ptr)->left_branch));
	NodeDelete (&((*tree_ptr_ptr)->right_branch));

	free (*tree_ptr_ptr);
	*tree_ptr_ptr = NULL;

	return 0;
}
	
		
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int TreeDelete (tree_t **root_ptr_ptr)
{
	NodeDelete (root_ptr_ptr);

	return 0;
}


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int isEmptyTree (tree_t *root_ptr)
{
	if (root_ptr == NULL)
	{
		return 1;
	}

	return 0;
}


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int TreeDepth (tree_t *tree_ptr, int *cur_depth_ptr, int *max_depth_ptr)
{
	assert (cur_depth_ptr != NULL);
	assert (max_depth_ptr != NULL);

	if (tree_ptr == NULL)
	{
		return 0;
	}

	(*cur_depth_ptr)++;

	TreeDepth (tree_ptr->left_branch, cur_depth_ptr, max_depth_ptr);
	TreeDepth (tree_ptr->right_branch, cur_depth_ptr, max_depth_ptr);

	(*cur_depth_ptr)--;

	if (*max_depth_ptr < *cur_depth_ptr)
	{
		*max_depth_ptr = *cur_depth_ptr;
	}

	return 0;
}
	

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int isTreeBalanced (tree_t *tree_ptr, int *cur_condition)
{
	if (*cur_condition == 0)
	{
		return 0;
	}

	if (tree_ptr == NULL)
	{
		return 1;
	}

	int left_depth = 0;
	int right_depth = 0;
	int cur_depth_left = 0;
	int cur_depth_rigth = 0;

	TreeDepth (tree_ptr->left_branch, &cur_depth_left, &left_depth);
	TreeDepth (tree_ptr->right_branch, &cur_depth_rigth, &right_depth);

//printf ("cur_data: %d -> left depth = %d; right depth = %d\n", 
//		tree_ptr->data, left_depth, right_depth);

	if (!(abs(left_depth - right_depth) < 2))
	{
		*cur_condition = 0;
		return 0;
	}

	isTreeBalanced (tree_ptr->left_branch, cur_condition);

	if (*cur_condition == 0)
	{
		return 0;
	}

	isTreeBalanced (tree_ptr->right_branch, cur_condition);

	if (*cur_condition == 0)
	{
		return 0;
	}

	
	return 1;
}
	
	
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int PrintNodesSameDepth (tree_t *tree_ptr, int level_depth, int *cur_level_depth)
{
	assert (level_depth >= 0);

	if (tree_ptr == NULL)
	{
		return 0;
	}

	if (*cur_level_depth == level_depth)
	{
		printf ("%d ", tree_ptr->data);
		return 0;
	}

	(*cur_level_depth)++;
	PrintNodesSameDepth (tree_ptr->left_branch, level_depth, cur_level_depth);
	PrintNodesSameDepth (tree_ptr->right_branch, level_depth, cur_level_depth);
	(*cur_level_depth)--;
	
	return 0;
}
	

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int ReadValuesNodes (tree_t **root)
{
	printf ("Enter values tree's nodes:\t");
	
	char data_nodes[MAX_N_NODES] = "";

	int value_node = 0;
	while (scanf ("%d", &value_node) > 0)
	{
		TreeAdd (root, value_node);
	}

	return 0;
}


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int HelpUseTree ()
{
	printf ("\n"
			"______________________________________________________\n"
			"|                                                    |\n"
			"| IF YOU WANT:                                       |\n"
			"|                                                    |\n"
			"| - print tree's nodes at the same depth, enter <0>; |\n"
			"| - print binary tree                                |\n"
			"|         1) simmetric:                   enter <1>, |\n"
			"|         2) direct:                      enter <2>, |\n"
			"|         3) reverse:                     enter <3>; |\n"
			"| - insert node into tree,                enter <4>; |\n"
			"| - delete node from tree,                enter <5>; |\n"
			"| - check (is tree empty?),               enter <6>; |\n"
			"| - delete all tree,                      enter <7>; |\n"
			"| - discover depth tree,                  enter <8>; |\n"
			"| - discover (is tree balansed ?),        enter <9>; |\n"
			"| * exit from progam,                     enter <#>. |\n"
			"|____________________________________________________|\n"
			"\n");

	return 0;
}
			

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void ClearBuffer (void)
{
	while(getchar () != '\n');
}


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
tree_t *SearchNode_ (tree_t *tree_ptr, data_t data)
{
	if (tree_ptr == NULL)
	{
		return NULL;
	}
		
	if (data == tree_ptr->data)
	{
		return tree_ptr;
	}
	else if (data < tree_ptr->data)
	{
		return SearchNode (tree_ptr->left_branch, data);
	}
	else 
	{
		return SearchNode (tree_ptr->right_branch, data);
	}
}


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
tree_t *SearchNode (tree_t *tree_ptr, data_t data)
{
	if (tree_ptr == NULL)
	{
		return NULL;
	}
		
	if (data == tree_ptr->data)
	{
		return tree_ptr;
	}

	tree_t *node_ptr = NULL;

	node_ptr = SearchNode (tree_ptr->left_branch, data);
	if (node_ptr != NULL)
	{
		return node_ptr;
	}

	node_ptr = SearchNode (tree_ptr->right_branch, data);
	if (node_ptr != NULL)
	{
		return node_ptr;
	}
	
	return NULL;
}


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
tree_t *SearchParentNode_ (tree_t *tree_ptr, tree_t *parent_ptr, 
						  data_t data, int *is_left_child)
{
	assert (is_left_child != NULL);

	if (tree_ptr == NULL)
	{
		return NULL;
	}
		
	if (data == tree_ptr->data)
	{
		return parent_ptr;
	}
	else if (data < tree_ptr->data)
	{
		if (*is_left_child == 1)
		{
			*is_left_child = 1;
			return SearchParentNode (tree_ptr->left_branch, parent_ptr->left_branch, 
									 data, is_left_child);
		}
		else if (*is_left_child == 0)
		{
			*is_left_child = 1;
			return SearchParentNode (tree_ptr->left_branch, parent_ptr->right_branch, 
									 data, is_left_child);
		}
		else
		{
			*is_left_child = 1;
			return SearchParentNode (tree_ptr->left_branch, parent_ptr, 
									 data, is_left_child);
		}
	}
	else 
	{
		if (*is_left_child == 1)
		{
			*is_left_child = 0;
			return SearchParentNode (tree_ptr->right_branch, parent_ptr->left_branch, 
									 data, is_left_child);
		}
		else if (*is_left_child == 0)
		{
			*is_left_child = 0;
			return SearchParentNode (tree_ptr->right_branch, parent_ptr->right_branch, 
									 data, is_left_child);
		}
		else
		{
			*is_left_child = 0;
			return SearchParentNode (tree_ptr->right_branch, parent_ptr, 
									 data, is_left_child);
		}

	}
}


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
tree_t *SearchParentNode (tree_t *tree_ptr, tree_t *parent_ptr, 
						  data_t data, int *is_left_child)
{
	assert (is_left_child != NULL);

	if (tree_ptr == NULL)
	{
		return NULL;
	}
		
	if (data == tree_ptr->data)
	{
		return parent_ptr;
	}

	tree_t *node_ptr = NULL;

	if (*is_left_child == 1)
	{
		*is_left_child = 1;
		node_ptr = SearchParentNode (tree_ptr->left_branch, parent_ptr->left_branch, 
									 data, is_left_child);
		if (node_ptr != NULL)
		{
			return node_ptr;
		}

		*is_left_child = 0;
		node_ptr = SearchParentNode (tree_ptr->right_branch, parent_ptr->left_branch,
									 data, is_left_child);
		if (node_ptr != NULL)
		{
			return node_ptr;
		}	
	}
	else if (*is_left_child == 0)
	{
		*is_left_child = 1;
		node_ptr = SearchParentNode (tree_ptr->left_branch, parent_ptr->right_branch, 
									 data, is_left_child);
		if (node_ptr != NULL)
		{
			return node_ptr;
		}

		*is_left_child = 0;
		node_ptr = SearchParentNode (tree_ptr->right_branch, parent_ptr->right_branch,
									 data, is_left_child);
		if (node_ptr != NULL)
		{
			return node_ptr;
		}	
	}
	else
	{
		*is_left_child = 1;
		node_ptr = SearchParentNode (tree_ptr->left_branch, parent_ptr, 
									 data, is_left_child);
		if (node_ptr != NULL)
		{
			return node_ptr;
		}

		*is_left_child = 0;
		node_ptr = SearchParentNode (tree_ptr->right_branch, parent_ptr,
									 data, is_left_child);
		if (node_ptr != NULL)
		{
			return node_ptr;
		}	
	}

	return NULL;
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int ReadCommands (tree_t **root)
{
	ReadValuesNodes (root);

	HelpUseTree ();

	int is_continue = 1;
	char mode = 0;
	while (is_continue)
	{
		ClearBuffer ();
		printf ("Enter command's code: ");
		scanf ("%c", &mode);

		switch (mode)
		{
			case 35:  // #
			{
				is_continue = 0;
				break;
			}
			case 48:  // 0
			{
				int level_depth = 0;
				int cur_level_depth = 0;
				printf ("Enter depth: ");
				scanf ("%d", &level_depth);
				PrintNodesSameDepth (*root, level_depth, &cur_level_depth);
				printf ("\n");
				break;
			}
			case 49:  // 1
			{
				TreePrintSymmetric (*root);
				printf ("\n");
				break;
			}
			case 50:  // 2
			{
				TreePrintDirect (*root);
				printf ("\n");
				break;
			}
			case 51:  // 3
			{
				TreePrintBack (*root);
				printf ("\n");
				break;
			}
			case 52:  // 4
			{
				data_t data_after = 0;
				printf ("Enter value node, " 
						"after them you want insert new node: ");
				scanf ("%d", &data_after);

				data_t data = 0;
				printf ("Enter value new node: ");
				scanf ("%d", &data);

				int is_left = 0;
				printf ("If you want insert new node to the left, "
						"enter: 1, else 0.\n");
				scanf ("%d", &is_left); 

				int is_left_branch = 0;
				printf ("If you want to "
						"node after new node will be left branch, "
						"enter: 1, else 0.\n");
				scanf ("%d", &is_left_branch); 

				NodeInsert (SearchNode (*root, data_after), data, 
							is_left, is_left_branch);

				break;
			}
			case 53:  // 5
			{
				data_t data = 0;
				printf ("Enter value node to be removed: ");
				scanf ("%d", &data);

				int is_left = -1;
				tree_t *parent_node = SearchParentNode (*root, *root, data, &is_left);

				if (is_left)
				{
					NodeDelete (&(parent_node->left_branch));
					parent_node->left_branch = NULL;
				}
				else
				{
					NodeDelete (&(parent_node->right_branch));
					parent_node->right_branch = NULL;
				}
					
				break;
			}
			case 54:  // 6
			{
				if (isEmptyTree (*root))
				{
					printf ("Tree is empt.\n");
				}
				else
				{
					printf ("Tree isn't empt.\n");
				}
				
				break;
			}
			case 55:  // 7
			{
				TreeDelete (root);
				break;
			}
			case 56:  // 8
			{
				int cur_depth = 0;
				int max_depth = 0;
				TreeDepth (*root, &cur_depth, &max_depth);
				printf ("Depth tree = %d.\n", max_depth);
				break;
			}
			case 57:  // 9
			{
				int cur_condition = 1;
				if (isTreeBalanced (*root, &cur_condition))
				{
					printf ("Tree is balanced.\n");
				}
				else
				{
					printf ("Tree isn't balanced.\n");
				}
				
				break;
				
			}
				default:
			{
				printf ("\nIncorrect input, try again.\n");
			}	
		}
	}


	return 0;
}


int GraphDumpTree (tree_t *tree_ptr)
{
	assert (tree_ptr != NULL);

	Start_Dot_File ("duump.dot");

//	MakeInfoTree (tree_ptr);

	int cur_depth = 0;
	int max_depth = 0;
	TreeDepth (tree_ptr, &cur_depth, &max_depth);

	Preamble (max_depth);

	Make_All ();

	PrintNodes (tree_ptr, max_depth);

	PrintConnections (tree_ptr, tree_ptr->data);	

	End_Dot_File ("dump.dot");

	return 0;
}	


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int PrintNodes (tree_t *tree_ptr, int depth_tree)
{
	if (tree_ptr == NULL)
	{
		return 0;
	}
		
	PrintNodes (tree_ptr->left_branch, depth_tree);

	int cur_depth = 0;
	int max_depth = 0;
	TreeDepth (tree_ptr, &cur_depth, &max_depth);

	Make_Node (depth_tree - max_depth, tree_ptr->data, "green");

	PrintNodes (tree_ptr->right_branch, depth_tree);

	return 0;
}	


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
int PrintConnections (tree_t *tree_ptr, data_t data_parent)
{
	if (tree_ptr == NULL)
	{
		return 0;
	}
		
	PrintConnections (tree_ptr->left_branch, tree_ptr->data);
	Make_Connection (data_parent, tree_ptr->data, "black", "grey");
	PrintConnections (tree_ptr->right_branch, tree_ptr->data);

	return 0;
}	


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//int DumpTree (tree_t *root)
//{
//	assert (root != NULL);
//
//	int cur_depth = 0;
//	int max_depth = 0;
//	n_iteration = TreeDepth (root, &cur_depth, &max_depth) + 1;
//	
//	int count = 0;
//
//	int cur_level_depth = 0;
//
//	for (count = 0; count < n_iteration; count++)
//	{
//		PrintfNodesSameDepth (root, count, &cur_level_depth);
//	}
//
//	return 0;
//}
		
	

