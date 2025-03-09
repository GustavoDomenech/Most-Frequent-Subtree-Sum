/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

 int subtreeSum( struct TreeNode* root, int* result, int* index, int* minSum,
    int* maxSum ) {
if ( !root )
return 0;
int left = subtreeSum( root->left, result, index, minSum, maxSum );
int right = subtreeSum( root->right, result, index, minSum, maxSum );
int sum = root->val + left + right;
result[ ( *index ) ++ ] = sum;
if ( sum < *minSum )
*minSum = sum;
if ( sum > *maxSum )
*maxSum = sum;
return sum;
}

int countNodes( struct TreeNode* root ) {
if ( !root )
return 0;
return 1 + countNodes( root->left ) + countNodes( root->right );
}

int* findFrequentTreeSum( struct TreeNode* root, int* returnSize ) {
if ( !root ) {
*returnSize = 0;
return NULL;
}

int n = countNodes ( root );
int* sums = ( int* ) malloc ( n * sizeof ( int ) );
int index = 0;
int minSum = INT_MAX, maxSum = INT_MIN;

subtreeSum( root, sums, &index, &minSum, &maxSum );

int range = maxSum - minSum + 1;
int* freq = ( int* ) calloc ( range, sizeof ( int ) );

for ( int i = 0; i < n; i++ ) {
freq[ sums[ i ] - minSum ]++;
}

int maxFreq = 0;
for ( int i = 0; i < range; i++ ) {
if ( freq[ i ] > maxFreq ) {
 maxFreq = freq[ i ];
}
}

int* result = ( int* ) malloc ( n * sizeof ( int ) );
int resultCount = 0;
for ( int i = 0; i < n; i++ ) {
if (freq[ sums[ i ] - minSum ] == maxFreq) {
 result[ resultCount++ ] = sums[ i ];
 freq[ sums[i] - minSum ] = 0;
}
}

*returnSize = resultCount;

free( sums );
free( freq );

return result;
}
