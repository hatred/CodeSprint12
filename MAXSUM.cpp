#include<iostream>
#include<vector>

using namespace std;

struct node
{
	node* left;
	node* right;
	int key; // key
	long long w; // maximum sub-sequence of weight of a substree with any element <=key
	int height;
};

node* initializeNode(int key,int weight)
{
	node* root = (node*)malloc(sizeof(node));
	root->left = NULL;
	root->right = NULL;

	root->key = key;
	root->w = weight;
	root->height = 0;
	return root;
}

long long findLargest(node* root,int k)
{
	if(!root)
		return 0;
	
	if(root->key == k)
		return max(0LL,findLargest(root->left,k));
	if(root->key < k)
		return max(root->w,findLargest(root->right,k));
	else
		return max(0LL,findLargest(root->left,k));
}

int HEIGHT(node* root)
{
	if(!root)	return -1;
	return root->height;
}


node* SingleRotateWithLeft(node* k2)
{
	node* k1;
	k1 = k2->left;
	
	k2->left = k1->right;
	k1->right = k2;

	k2->height = max(HEIGHT(k2->left), HEIGHT(k2->right) ) + 1;
	k1->height = max(HEIGHT(k1->left),k2->height) + 1;
	if(k1->left)
		k1->w = max(k1->left->w,k1->w);
	return k1; // the new root
}

node* SingleRotateWithRight(node* k1);

node* DoubleRotateWithLeft(node* k3)
{
	k3->left = SingleRotateWithRight(k3->left);
	
	if(k3->left->left)
		k3->left->w = max(k3->left->left->w,k3->left->w);
	return SingleRotateWithLeft(k3);
}

node* SingleRotateWithRight(node* k1)
{
	node* k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = max(HEIGHT(k1->left), HEIGHT(k1->right)) + 1;
	k2->height = max(HEIGHT(k2->right), k1->height) + 1;
	if(k2->left)
		k2->w = max(k2->left->w,k2->w);
	return k2;
}

node* DoubleRotateWithRight(node* k1)
{
	k1->right = SingleRotateWithLeft(k1->right);

	return SingleRotateWithRight(k1);
}



node* insertInTree(node* root, int key,long long maxWeight,long long w)
{
	if(root == NULL)
	{
		//cout<<key<<" "<<maxWeight<<" "<<w<<endl;
		root = initializeNode(key,w);
		root->w = maxWeight + w;
		return root;
	}

	//cout<<root->key<<" dd "<<root->w<<" dd "<<key<<endl;
	if(root->key == key)
	{
		root->w = max(maxWeight + w, root->w);
		return root;
	}
	else if(key < root->key)
	{
		root->left = insertInTree(root->left,key,maxWeight,w);
		if(HEIGHT(root->left) - HEIGHT(root->right) == 2)
			if( key < root->left->key )
				root = SingleRotateWithLeft(root);
			else
				root = DoubleRotateWithLeft(root);
	}
	else if(key > root->key)
	{
		root->right = insertInTree(root->right,key,maxWeight,w);
		if(HEIGHT(root->right) - HEIGHT(root->left) == 2)
			if(key > root->right->key)
				root = SingleRotateWithRight(root);
			else
				root = DoubleRotateWithRight(root);
	}
	root->height = max(HEIGHT(root->left),HEIGHT(root->right)) + 1;
	return root;
}

long long findMaxWs(node* root)
{
	if(!root)
		return 0;
	
	long long leftR = findMaxWs(root->left);
	long long rightR = findMaxWs(root->right);

	return max(max(leftR,rightR), root->w);
}


void printInOrder(node* root)
{
	if(!root)
		return;
	printInOrder(root->left);
	//cout<<root->key<<" "<<root->w<<endl;
	printInOrder(root->right);
}

long long update(node* root,int key)
{
	if(!root)
		return 0 ;
	
	if(root->key > key)
	{
		long long left = update(root->left,key);
		
		root->w = max(root->w,left);
		return root->w;
	}
	else
	{
		long long right = update(root->right,key);
		return max(root->w,right);
	}
}
int main()
{
	int t;
	cin>>t;
	while(t-- > 0)
	{
		int n;
		cin>>n;

		int a[n];
		int w[n];
		for(int i=0;i<n;i++)
			cin>>a[i];
		for(int i=0;i<n;i++)
			cin>>w[i];
	
		node* root = initializeNode(a[0],w[0]);
		
		for(int i=1;i<n;i++)
		{
			// find the largest w which is <= a[i];
			long long wi = findLargest(root,a[i]);
			root = insertInTree(root,a[i],wi,w[i]);
		//	printInOrder(root);
			update(root,a[i]);
			//cout<<wi<<" "<<a[i]<<" "<<" "<<w[i]<<" "<<findMaxWs(root)<<endl;
			
		}
	//	printInOrder(root);
		cout<<findMaxWs(root)<<endl;
	}
	return 0;
}