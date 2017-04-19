//__author__ = "andrew mei"
// professor : m. luttrel
//class : 110c
// this program implements a basic binary searchtree using c++14 features
//it also adds numbers randomly 


#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include <chrono>

template<typename T>
class Binarytree{
	struct BinaryNode{
		BinaryNode *left;
		BinaryNode *right;
		T value;
		BinaryNode(const T& data, BinaryNode* ltree, BinaryNode *rtree): value(data), left(ltree), right(rtree){}
		~BinaryNode() = default; 
		void destory(BinaryNode *& root);
	};
	void destory(BinaryNode *&root);
	void insert( const T& element, BinaryNode *&root);
	void insert(T && element, BinaryNode *&root);
	void print(BinaryNode *root, std::ostream& out) const;
	void randomadd( T&& elment, BinaryNode *&root);
	public:
	void randomadd( T&& element);
	BinaryNode *clone(BinaryNode *t) const{
		if (t == nullptr)
			return nullptr;
		else
			return new BinaryNode{t->value, clone(t->left), clone(t->right)};
}
	void destory();
	~Binarytree();
	Binarytree(): root(nullptr) {}
	Binarytree(const T& rhs): root(nullptr){root = clone(rhs.root);}
	BinaryNode *root;
	void insert(const T& element);
	void insert(T && element);
	void remove(const T& element);
	bool contains(const T& element, BinaryNode *root);
	void print( std::ostream& out= std::cout ) const;
	bool isEmpty() const{return root == nullptr;}
};
template<typename T>
void Binarytree<T>::destory(){
	destory(root);
}
template<typename T>
Binarytree<T>::~Binarytree(){
	 destory();

}
template<typename T>
void Binarytree<T>::destory(BinaryNode *&root){
	if (root != nullptr){
		destory(root->left);
		destory(root->right);
		delete root;
	}
	root = nullptr;

}
//template<typename T>
//bool  Binarytree<T>::contains(const T& element ){
//	return contains(element, root);
//}
template<typename T>
void Binarytree<T>::randomadd( T&& element, BinaryNode *&root){
	//srand(time(NULL));
	//std::mt19937_64 rng;
	std::random_device rd;
	std::uniform_real_distribution<double> lol (1,2);
	double guess = lol(rd);
	if (root == nullptr)
		root = new BinaryNode(std::move(element), nullptr, nullptr);
	else if (guess <=  1.5)
		randomadd(std::move(element), root->left);
	else 
		randomadd(std::move(element), root->right);
	guess = lol(rd);
	//std::cout << guess << std::endl;
}
template<typename T>
void Binarytree<T>::insert(T && element, BinaryNode *& root){
	if (root == nullptr)
		root = new BinaryNode(std::move(element) , nullptr, nullptr);
	else if (element >= root->value)
		insert(std::move(element), root->right);
	else if (element <= root->value)
		insert(std::move(element), root->left);
}
template<typename T>
void Binarytree<T>::randomadd(T && element){
	randomadd(std::move(element), root);
}
template<typename T>
void Binarytree<T>::insert(T && element){
	insert(std::move(element), root);
}
template<typename T>
void Binarytree<T>::insert(const T& element){
	insert(element, root);
}
template<typename T>
void Binarytree<T>::print(std::ostream& out) const{ 
	if (isEmpty())
		out << "tree is empty "  << std::endl;
	else
		print (root, out);
}

template<typename T>
void Binarytree<T>::print( BinaryNode *root, std::ostream& out) const{
	if (root != nullptr){
	print(root->left, out);
	out << root->value << std::endl;
	print(root->right, out);
	}
}
template<typename T>
bool Binarytree<T>::contains(const T& element, BinaryNode *root){
	if (root == nullptr)
		return false;
	else if (root->data >= element)
		contains(element, root->left);
	else if (root->data <= element)
		contains(element, root->right);
	else
		return true;
}
template<typename T>
void Binarytree<T>::insert(const T& element, BinaryNode *&root){
	if (root == NULL)
		root = new BinaryNode(element, nullptr, nullptr) ;
	else if (element >= root->value)
		insert(element, root->right);
	else if (element <= root->value)
		insert(element, root->left);
}
/*
template<typename T>
BinaryNode::<T>BinaryNode<T>::clone(BinaryNode* t) const {
	if (t== nullptr)
		return nullptr;
	else
		return new BinaryNode(t->element, t->left,t->right);

}

*/
int main(int argc, char **argv ){
	srand(time(NULL));
	std::mt19937_64 rng;
	uint64_t timeseed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{uint32_t (timeseed & 0xfffffff), uint32_t(timeseed >> 32) };
	rng.seed(ss);
	

	Binarytree<int> btree;
	btree.randomadd(10);
	btree.randomadd(20);
	btree.randomadd(30);
	btree.randomadd(40);
	btree.randomadd(50);
	btree.randomadd(60);
	btree.randomadd(70);
	btree.randomadd(80);
	btree.randomadd(90);
	btree.print();
}
/*
40
30
50
90
20
60
10
80
70
Andrews-MacBook-Pro-2:~ pokemon$ nano binarysearchtree.cpp 
Andrews-MacBook-Pro-2:~ pokemon$ g++ -std=c++1y binarysearchtree.cpp 
Andrews-MacBook-Pro-2:~ pokemon$ ./a.out
30
60
90
10
80
20
50
70
40
Andrews-MacBook-Pro-2:~ pokemon$ 
*/
