typedef struct TreeNode TreeNode;
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

void tree_insert( TreeNode* root, char data );
TreeNode* tree_search( TreeNode* root, char data );
void tree_print_sorted( TreeNode* root );
void tree_delete( TreeNode* root );

int main (void) {
    return 0;
}