#pragma once

#include <stdlib.h>

#include "../../../lib2/SystemErrors2/errors.h"
#include "../../department/department.h"

typedef struct BinTreeNode {
	Departament* departament;
	struct BinTreeNode* left;
	struct BinTreeNode* right;
} BinTreeNode;

typedef struct BinTree {
	size_t size;
	BinTreeNode* head;
} BinTree;

error_msg create_bin_tree(BinTree* tree);
error_msg push_into_bin_tree(BinTree* tree, size_t id_department, size_t count_operators, char what_queue);
error_msg get_bin_tree(BinTree* tree, size_t id, Departament** dep);
error_msg destroy_bin_tree(BinTree* tree);