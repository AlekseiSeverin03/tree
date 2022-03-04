
// tree.h


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "graph_dump.h"


const int  MAX_DEPTH_TREE = 1000;
const int  MAX_N_NODES    = 1000;

typedef int           data_t;
typedef struct tree_t tree_t;

struct tree_t 
{
	data_t data;
	tree_t *left_branch;
	tree_t *right_branch;
};



int     NodeCtor            (tree_t **tree_ptr, data_t data);
tree_t *TreeAdd             (tree_t **tree_ptr, data_t data);
int     TreePrintSymmetric  (tree_t  *tree_ptr);
int     TreePrintDirect     (tree_t  *tree_ptr);
int     TreePrintBack       (tree_t  *tree_ptr);
tree_t *NodeInsert          (tree_t  *tree_after_ptr, data_t data, 
							 int is_left, int is_left_branch);
int     NodeDelete          (tree_t **tree_ptr_ptr);
int     TreeDelete          (tree_t **root_ptr_ptr);
int     isEmptyTree         (tree_t  *root_ptr);
int     TreeDepth           (tree_t  *tree_ptr, int *cur_depth_ptr,
							  				    int *max_depth_ptr);
int     isTreeBalanced      (tree_t  *tree_ptr, int *cur_condition);
int     PrintNodesSameDepth (tree_t  *tree_ptr, int level_depth, int *cur_level_depth);
int     ReadValuesNodes     (tree_t **tree_ptr);
int     HelpUseTree         (void);
void    ClearBuffer         (void);
tree_t *SearchNode          (tree_t *root, data_t data);
tree_t *SearchParentNode    (tree_t *root, tree_t *parent_ptr,  // when called parent_ptr = root
							 data_t data, int *is_left_child);

int     ReadCommands        (tree_t **tree_ptr);
int     GraphDumpTree       (tree_t *tree_ptr);
int     PrintNodes          (tree_t *tree_ptr, int depth_tree);
int     PrintConnections    (tree_t *tree_ptr, data_t data_parent);


