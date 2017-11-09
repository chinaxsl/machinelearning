#include <iostream>
#include <vector>
using namespace std;
#define MAX_CHILD 26
#define TYPE char
#define DTYPE float
struct TreeNode {
	TYPE value;//节点内容
	DTYPE data;//节点数据
	bool state;//节点状态
	TreeNode * child[MAX_CHILD];//孩子指针
};
class TrieTree {
private:
	TreeNode * root;
	TreeNode * createNode(TYPE value, DTYPE data);
	void insertNode(TreeNode * node);
public:
	TreeNode * getRoot();
	TrieTree();
	~TrieTree();
	void deepOrder();
	void add(TYPE value[]);
	bool find(TYPE value[]);
	void deepOrder(TreeNode * node, vector<char> &v, int & count);
};
int chartoindex(char a) {
	return a - 'a';
}
char indextochar(int index) {
	return 'a' + index;
}
void printString(vector<char> v) {
	int length = v.size();
	for (int i = 0; i<length; i++) {
		printf("%c", v[i]);
	}
	printf("\n");
}
TrieTree::TrieTree() {
	root = new TreeNode();
	for (int i = 0; i<MAX_CHILD; i++) {
		root->child[i] = NULL;
	}
}
TrieTree::~TrieTree() {
	if (root != NULL) {
		delete[] root;
	}

}

TreeNode * TrieTree::getRoot() {
	return root;
}

TreeNode * TrieTree::createNode(TYPE value, DTYPE data) {
	TreeNode *node = new TreeNode();
	node->state = false;
	node->value = value;
	node->data = data;
	for (int i = 0; i<MAX_CHILD; i++) {
		node->child[i] = NULL;
	}
	return node;
}
// 插入孩子节点
void TrieTree::insertNode(TreeNode * node) {
	if (node != NULL) {
		for (int i = 0; i<MAX_CHILD; i++) {
			if (node->child[i] == NULL) {
				node->child[i] = createNode(indextochar(i), 0);
			}
		}
	}
}
// 加入某个字符串
void TrieTree::add(TYPE value[]) {
	TreeNode * ptr = root;
	int length = strlen(value);
	for (int i = 0; i<length; i++) {
		if (ptr->child[chartoindex(value[i])] == NULL) {
			insertNode(ptr);
		}
		ptr = ptr->child[chartoindex(value[i])];
	}
	ptr->state = true;
}
// 寻找某个字符串是否存在于字典树
bool TrieTree::find(TYPE value[]) {
	TreeNode * ptr = root;
	int length = strlen(value);
	for (int i = 0; i<length; i++) {
		if (ptr->child[chartoindex(value[i])] == NULL) {
			return false;
		}
		ptr = ptr->child[chartoindex(value[i])];
	}
	if (ptr->state) {
		return true;
	}
	else {
		return false;
	}
}

//深度优先遍历字典树并打印字符串
void TrieTree::deepOrder(TreeNode * node, vector<char> &v, int &count) {
	TreeNode * ptr = node;
	if (ptr == NULL) {
		return;
	}
	else {
		for (int i = 0; i<MAX_CHILD; i++) {
			v.push_back(indextochar(i));
			if (ptr->child[i] != NULL && ptr->child[i]->state) {
				printf("%d: ", ++count);
				printString(v);
			}
			deepOrder(ptr->child[i], v, count);
			v.pop_back();
		}
	}
}
int main() {
	TrieTree tree = TrieTree();
	tree.add("xsl");
	tree.add("woshishei");
	tree.add("liyipin");
	tree.add("zhch");
	vector<char> v;
	int count = 0;
	tree.deepOrder(tree.getRoot(), v, count);
	if (tree.find("xsl")) {
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
	if (tree.find("xl")) {
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
	return 0;
}
