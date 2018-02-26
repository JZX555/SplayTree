#include "stdafx.h"
#include "SplayTree.h"

/* ���캯��:��ʼ������
 * ����ֵ:��
 * ����:��
 */
SplayTree::SplayTree()
{
	NullNode = new SplayNode(); // ��ʼ���ձ�־�ڵ�
	if (NullNode == NULL)
		cout << "��־�ڵ�����ʧ��!" << endl;
	NullNode->Element = 0;
	NullNode->Left = NullNode->Right = NullNode; 

	Root = NullNode; // ��ʼ�����ڵ�
}

/* ��������:��������ʱ�����ڴ�ռ�
 * ����ֵ:��
 * ����:��
 */
SplayTree::~SplayTree()
{
	MakeEmpty(); // ���ÿ�
	delete Root; // ɾ�����ڵ�
	Root = NULL;
	delete NullNode; // ɾ����־2�ڵ�
	NullNode = NULL;
}

/* �ÿպ���:�����ÿ�
 * ����ֵ:��
 * ����:��
 */
void SplayTree::MakeEmpty() {
	MakeEmpty(Root); // �����ڵ��ÿ�
	Root = NullNode; // �ÿպ��ٴγ�ʼ��
}

/* �ÿպ���:��Ŀ��ڵ��ÿ�
 * ����ֵ:��
 * ����:��
 */
void SplayTree::MakeEmpty(TreeNode Tree) {
	if (Tree != NullNode) { // �ж�Ŀ���Ƿ���Ҫ�ÿ�
		// �ݹ��ÿ�������
		MakeEmpty(Tree->Left);
		MakeEmpty(Tree->Right);
		delete Tree; // ɾ����ǰ�ڵ�
		Tree = NULL;
	}
}

/* ��չ����:�����ڵ����Ŀ��Ԫ�ؽ�����չ
 * ����ֵ:��
 * ����:key:Ŀ��Ԫ��
 */
void SplayTree::Splay(const int key) {
	Splay(key, Root);
}

/* ��չ����:��Ŀ��ڵ����Ŀ��Ԫ�ؽ�����չ
 * ����ֵ:��
 * ����:key:Ŀ��Ԫ�أ�root:��չ��Ŀ��ڵ�
 */
void SplayTree::Splay(const int key, TreeNode &root) {
	static struct SplayNode Header; // ���澲̬ͷ��㣬����ϵͳ����
	TreeNode LeftTreeMax, RightTreeMin; // ��������������

	Header.Left = Header.Right = NullNode; // ��ʼ��ͷ���
	LeftTreeMax = RightTreeMin = &Header; // ��������������ͷ�������
	NullNode->Element = key; // ��ֹ�ظ�����

	while (key != root->Element) { // �ж��Ƿ��ѽ�Ŀ��Ԫ����չ�����ϲ�
		// �����ڵ����Ҳ���չ
		if (key < root->Element) {
			if (root->Left == NullNode) // �˴�ʹ�ÿձ�־�ڵ������NULL�����Լ���ؼ򻯳���ͬʱ����NULL->Element��ʹ��
				break;
			if (key < root->Left->Element) // zig-zig�������δ���
				SingleRotateWithLeft(root);

			// �ر�˵��:
			//     ��Ϊ���Խ�zig-zag���μ򻯲������䲽���뵥��ת������ͬ��ͬʱ��Ϊzig-zig
			// ���α��������������һ�������Խ�zig-zig���ε����жϣ��������������û������
			// ���жϣ����Ǻ���һ��ʹ�á�

			// �����Լ��������ӵ�������
			RightTreeMin->Left = root;
			RightTreeMin = root; // ������������λ��
			root = root->Left; // ��������
		}

		// �����ڵ��������չ
		else {
			if (root->Right == NullNode)
				break;
			if (key > root->Right->Element) // zig-zig�������δ���
				SingleRotateWithRight(root);

			// �������������ӵ���������
			LeftTreeMax->Right = root;
			LeftTreeMax = root; // ������������λ��
			root = root->Right; // ��������
		}
	}
	// ����������
	LeftTreeMax->Right = root->Left;
	RightTreeMin->Left = root->Right;

	// �������������ϲ�
	root->Left = Header.Right;
	root->Right = Header.Left;
}

/* ����ת����:��Ŀ��ڵ�������ת
 * ����ֵ:��
 * ����:Tree:��Ҫ��������ת��Ŀ��ڵ�
 */
void SplayTree::SingleRotateWithLeft(TreeNode &Tree) {
	TreeNode LeftChild; // ����������
	// ������ת����
	LeftChild = Tree->Left;
	Tree->Left = LeftChild->Right;
	LeftChild->Right = Tree;

	Tree = LeftChild; // ����Ŀ��ڵ�
}

/* ����ת����:��Ŀ��ڵ�������ת
 * ����ֵ:��
 * ����:Tree:��Ҫ��������ת��Ŀ��ڵ�
 */
void SplayTree::SingleRotateWithRight(TreeNode &Tree) {
	TreeNode RightChild; // ����������
	// ������ת����
	RightChild = Tree->Right;
	Tree->Right = RightChild->Left;
	RightChild->Left = Tree;

	Tree = RightChild; // ����Ŀ��ڵ�
}

/* ���Һ���:����Ŀ��Ԫ�أ�������ֵ
 * ����ֵ:int:Ŀ��Ԫ�ص�ֵ
 * ����:key:��Ҫ���ҵ�Ŀ��Ԫ��
 */
int SplayTree::Find(int key) {
	Splay(key, Root); // ������չ��
	if (Root->Element != key) { // �ж�Ԫ���Ƿ����
		cout << "������Ԫ��:" << key << endl;
		return NULL;
	}
	else
		return key;
}

/* ���뺯��:����Ŀ��Ԫ��
 * ����ֵ:��
 * ����:key:��Ҫ�����Ŀ��Ԫ��
 */
void SplayTree::Insert(const int key) {
	static TreeNode NewNode = NULL; // ���澲̬�½ڵ㣬����ϵͳ����
	if (NewNode == NULL) { // �ж��½ڵ��Ƿ��ÿ�
		NewNode = new SplayNode(); // ��ʼ���½ڵ�
		if (NewNode == NULL)
			cout << "�½ڵ��ڴ����ʧ��!" << endl;
	}
	NewNode->Element = key;

	if (Root == NullNode) { // �ж������Ƿ�Ϊ�ձ�־
		// ֱ�Ӹ�ֵ�½ڵ�
		NewNode->Left = NewNode->Right = NullNode;
		Root = NewNode;
	}

	else {
		Splay(key, Root); // �����ڵ���չ

		// ��������
		if (key < Root->Element) {
			//        NewNode
			//        /     \
			//  Root->Left  Root  
			NewNode->Left = Root->Left;
			NewNode->Right = Root;
			Root->Left = NullNode;
			Root = NewNode;
		}

		// ���Ҳ����
		else if (key > Root->Element) {
			//        NewNode
			//        /     \
			//     Root  Root->Right
			NewNode->Right = Root->Right;
			NewNode->Left = Root;
			Root->Right = NullNode;
			Root = NewNode;
		}

		else // �Ѿ������в���Ҫ����
			return;
	}

	NewNode = NULL;
}

/* ɾ������:ɾ�����е�Ŀ��Ԫ��
 * ����ֵ:��
 * ����:key:��Ҫɾ����Ŀ��Ԫ��
 */
void SplayTree::Remove(const int key) {
	TreeNode NewNode; // �����½ڵ�

	if (Root == NullNode) // �ж����Ƿ����ִ��ɾ������
		cout << "��������ִ��ɾ������!" << endl;
	else {
		Splay(key, Root); // ���Ÿ���չ��
		// �ж��Ƿ����Ŀ��Ԫ��
		if (key == Root->Element) {
			// �����������Ϊ�ձ�־��ֱ�Ӱ������������µ�������Ҳ���Է�����д��
			if (Root->Left == NullNode)
				NewNode = Root->Right;
			else {
				NewNode = Root->Left;
				Splay(key, NewNode); // ����������չ��
				NewNode->Right = Root->Right; // �ƽӾɵ�������
			}
			delete Root; // ɾ��������
			Root = NewNode; // ��������
		}
	}
}

/* չʾ����:չʾ���е���Ϣ
 * ����ֵ:��
 * ����:��
 */
void SplayTree::Display() {
	Display(Root, 1, 0); // չʾ������Ϣ
}

/* չʾ����:չʾĿ��ڵ���Ϣ
 * ����ֵ:��
 * ����:Tree:��Ҫչʾ��Ŀ��ڵ㣻index:�ڵ����ڲ���
 */
void SplayTree::Display(const TreeNode &Tree, const int index, const int x) {
	// �ж��Ƿ����ִ��չʾ����
	if (Tree != NullNode) {
		// ����չʾ��Ϣ
		if (x == 1)
			cout << "��";
		if (x == 2)
			cout << "��";
		cout << "��" << index << "��: " << Tree->Element << endl;
		Display(Tree->Left, index + 1, 1); // �ݹ�չʾ������

		Display(Tree->Right, index + 1, 2); // �ݹ�չʾ������
	}
	else
		return;
}