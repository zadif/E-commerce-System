#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <chrono>
//#include"utils/ConsoleUtility.h"
#include"termcolor.hpp"
#include"tabulate.hpp"
#include <cstdlib>
using namespace std;
using namespace chrono;
using namespace termcolor;
using namespace tabulate;


int loggedInSellerId = 0;
int loggedInCustomerId = 0;


/*Currently in the world of digital market, optimizing the working of system, processing the orders and managing the routes for deliveries is the core thing, which is necessary to run an E-commerce system. Traditional systems don�t offer personalized recommendations and experience a lot of delays while sending the parcels. Now-a-days, customer demands a secure platform that provides customized dashboard, loyalty rewards and maintain thorough user history, these things lack in basic E-commerce systems.
Significance and Relevance:
		Now-a-days E-commerce has taken global trade. Efficiently managing inventory, securing user data, and providing personalized experiences are essential for the success of any E-commerce system. By adding features we can obtain all the functionalities which are necessary to smoothly run a system. This project demonstrates the practical application of DSA in solving real-world business problem. It has practical usage of stacks, queues, linked-lists, recursion, trees, graphs and sorting algorithms. These data structures will streamline the workflow of our system.

Features:
�	Admin: Admin can add, delete, update, view and search both customers and sellers.
�	Customer: Customer can see the product after selecting the category, order and pay for the product, add the product to the cart, made his own account, update his profile, search for the product and view his history.
�	Seller: Seller can add the product and view his own added product, made his own account, update his own profile, view his history
�	Customer Loyalty Program: Points based loyalty program to reward customers.
�	Personalized User Dashboard: Use to track orders and to get personalized recommendations. They can also access their history.
�	Smart System: Alerts the admin when a particular product is getting out of stock.

*/

void header() {

	cout << "                          ______" << endl;
	cout << "                         |  ____|                                                " << endl;
	cout << "                         | |__   ___ ___  _ __ ___  _ __ ___   ___ _ __ ___ ___ " << endl;
	cout << "                         |  __| / __/ _ \\| '_ ` _ \\| '_ ` _ \\ / _ \\ '__/ __/ _ \\" << endl;
	cout << "                         | |___| (_| (_) | | | | | | | | | | |  __/ | | (_|  __/" << endl;
	cout << "                         |______\\___\\___/|_| |_| |_|_| |_| |_|\\___|_|  \\___\\___|" << endl;
	cout << "                                                        " << endl;
}
class ProductCategoryTree;
class ProductCategoryNode;
class ProductTree;
class ProductNode;
class Seller;
class Customer;
class Order;
class OrderItem;
class Cart;
class CartItem;
class SearchHistory;
class SearchItem;
template <typename T>
class Stack {
private:
	struct Node {
		T data;
		Node* next;
		Node(const T& data) : data(data), next(nullptr) {}
	};
	Node* top;

public:
	Stack() : top(nullptr) {}

	void push(const T& data) {
		Node* newNode = new Node(data);
		newNode->next = top;
		top = newNode;
	}

	void pop() {
		if (top == nullptr) {
			cout << "Stack is empty\n";
			return;
		}
		Node* temp = top;
		top = top->next;
		delete temp;
	}

	T peek() const {
		if (top == nullptr) {
			throw runtime_error("Stack is empty");
		}
		return top->data;
	}

	bool isEmpty() const {
		return top == nullptr;
	}

	void display() const {
		Node* temp = top;
		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	~Stack() {
		while (top != nullptr) {
			pop();
		}
	}
};

template <typename T>
class Queue {
public:
	struct Node {
		T data;
		Node* next;
		Node(const T& data) : data(data), next(nullptr) {}
	};
	Node* front;
	Node* rear;

public:
	Queue() : front(nullptr), rear(nullptr) {}

	void push(const T& data) {
		Node* newNode = new Node(data);
		if (rear == nullptr) {
			front = rear = newNode;
			return;
		}
		rear->next = newNode;
		rear = newNode;
	}

	void pop() {
		if (front == nullptr) {
			cout << "Queue is empty\n";
			return;
		}
		Node* temp = front;
		front = front->next;
		if (front == nullptr) {
			rear = nullptr;
		}
		delete temp;
	}

	T peek() const {
		if (front == nullptr) {
			//error
		}
		return front->data;
	}

	bool empty() const {
		return front == nullptr;
	}

	void display() const {
		Node* temp = front;
		while (temp != nullptr) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	~Queue() {
		while (front != nullptr) {
			pop();
		}
	}
	
};

ifstream inputFile;
ofstream outputFile;
ofstream fout, fout_product;
ifstream fin, fin_product;

void displayCustomerMenu();
void manageCategories();
void displaySellerMenu();
void displayAdminMenu();
void addSeller();
void deleteSeller(int id);
void updateSeller(int id);
void searchSeller(int id);
void viewAllSellers();
void displaySellerMenu();
void updateCustomer(int id);
void addCustomer();
void searchCustomer(int id);
void deleteCustomer(int id);
void viewAllCustomers();
void displayCustomerMenu();
void adminLogin();
void addProduct(ProductCategoryNode*);
void manageProducts();
void deleteProduct(ProductCategoryNode*);
void updateProduct(ProductCategoryNode*);
void searchProduct(ProductCategoryNode*);
void viewAllProducts(ProductCategoryNode*);
void sellerMenu();
void SellerLogin();
void writeCustomersToFile();
void writeSellersToFile();
void readCustomersFromFile();
void readSellersFromFile();
void menus();
void manageCategories();
void addCategory();
void updateCategory();
void searchCategory();
void viewAllCategory();

string generateUniqueID(char c)
{

	// get the current time in nanoseconds
	auto now = system_clock::now();
	// get time since 1/1/1970 and subtract it with current time
	auto now_ns = duration_cast<nanoseconds>(now.time_since_epoch()).count();

	srand(time(NULL));
	int randomNum = rand() % 1000;

	return c + to_string(now_ns) + "_" + to_string(randomNum);
}

class Admin
{
private:
	string email;
	string password;

public:
	Admin() : email(""), password("") {}
	Admin(string email, string password) : email(email), password(password) {}
	string getEmail() const { return email; }
	string getPassword() const { return password; }
};

class ProductNode
{
public:
	string productId;
	string productName;
	int productPrice;
	int quantity;
	ProductNode* left;
	ProductNode* right;
	int height;
	string sellerID;
	string buyerID;
	ProductNode(string name, int price, int quantity, string productid, string sellerid)
	{
		productName = name;
		productPrice = price;
		this->quantity = quantity;
		left = right = NULL;
		// generate random id
		if (productid == " ")
			productId = generateUniqueID('p');
		else
			productId = productid;
		height = 1;
		sellerID = sellerid;
	}
};

// Use binary search trees to store products based on categories
class ProductTree
{
public:
	ProductNode* root;
	ProductTree()
	{
		root = NULL;
	}
	void setProductTree(ProductNode* tree) { root = tree; }

	void insert(string name, int price, int quantity, string productId,string sellerId)
	{
		root = insertRec(root, name, price, quantity, productId,sellerId);
		// return this->;
	}
	int height(ProductNode* N)
	{
		if (!N)
			return 0;

		return N->height;
	}
	int getBalanceFactor(ProductNode* N)
	{
		if (!N)
			return 0;

		return height(N->left) - height(N->right);
	}
	ProductNode* rightRotate(ProductNode* y)
	{
		ProductNode* x = y->left;
		ProductNode* T2 = x->right;
		x->right = y;
		y->left = T2;
		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;
		return x;
	}
	ProductNode* leftRotate(ProductNode* x)
	{
		ProductNode* y = x->right;
		ProductNode* T2 = y->left;
		y->left = x;
		x->right = T2;
		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;
		return y;
	}
	ProductNode* insertRec(ProductNode* node, string name, int price, int quantity, string productid,string sellerid)
	{
		if (node == nullptr)
		{
			return new ProductNode(name, price, quantity, productid,sellerid);
		}
		if (name < node->productName)
		{
			node->left = insertRec(node->left, name, price, quantity, productid, sellerid);
		}
		else if (name > node->productName)
		{
			node->right = insertRec(node->right, name, price, quantity, productid, sellerid);
		}
		else
		{
			return node;
		}
		node->height = 1 + max(height(node->left), height(node->right));
		int balanceFactor = getBalanceFactor(node);
		if (balanceFactor > 1 && name < node->left->productName)
		{
			return rightRotate(node);
		}
		if (balanceFactor < -1 && name > node->right->productName)
		{
			return leftRotate(node);
		}
		if (balanceFactor > 1 && name > node->left->productName)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		if (balanceFactor < -1 && name < node->right->productName)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
		return node;
	}

	/*ProductNode* insertRec(ProductNode* root, string name, int price, int quantity) {
		if (root == NULL) {
			return new ProductNode(name, price, quantity);
		}
		if (name < root->productName) {
			root->left = insertRec(root->left, name, price, quantity);
		}
		else if (name > root->productName) {
			root->right = insertRec(root->right, name, price, quantity);
		}
		return root;
	}*/
	void inorder()
	{
		Table table;
		table.add_row({"Product Name", "Product Price", "Quantity"});
		inorderRec(root , table);
		
  for(size_t i = 0; i < 3; ++i) {
	table[0][i].format()
	  .font_color(Color::green)
	  .font_align(FontAlign::center)
	  .font_style({FontStyle::bold});
  }
  std::cout << table << std::endl;
	}
	void inorderRec(ProductNode* root , Table table)
	{
		if (root != NULL)
		{
			inorderRec(root->left , table);
			// make table
			table.add_row({root->productName , to_string(root->productPrice) , to_string(root->quantity)});
			
			inorderRec(root->right , table);
		}
	}
	
	void levelorder()
	{
		levelorderRec(root);
	}
	void levelorderRec(ProductNode* root)
	{
		if (root)
		{
			cout << "\nLevel order:";
			queue<ProductNode*> q;
			q.push(root);
			while (!q.empty())
			{
				ProductNode* n = q.front();
				q.pop();
				cout << n->productName << " " << n->productPrice << endl;

				if (n->left)
					q.push(n->left);
				if (n->right)
					q.push(n->right);
			}
		}
	}
	void writeProductsInFile(ofstream& os, string category_id)
	{
		if (root)
		{
			queue<ProductNode*> q;

			q.push(root);
			while (!q.empty())
			{
				ProductNode* n = q.front();
				q.pop();
				fout_product << category_id << endl;
				fout_product << n->productId << endl;
				fout_product << n->productName << endl;
				fout_product << n->productPrice << endl;
				fout_product << n->quantity << endl;

				if (n->left)
					q.push(n->left);
				if (n->right)
					q.push(n->right);
			}
		}
	}
	ProductNode* search(string name)
	{
		return searchRec(root, name);
	}
	ProductNode* searchRec(ProductNode* root, string name)
	{
		if (root == NULL || root->productName == name)
		{
			return root;
		}
		if (name < root->productName)
		{
			return searchRec(root->left, name);
		}
		return searchRec(root->right, name);
	}
	void deleteNode(string name)
	{
		root = deleteNodeRec(root, name);
	}
	ProductNode* deleteNodeRec(ProductNode* root, string name)
	{
		if (root == nullptr)
		{
			return root;
		}
		if (name < root->productName)
		{
			root->left = deleteNodeRec(root->left, name);
		}
		else if (name > root->productName)
		{
			root->right = deleteNodeRec(root->right, name);
		}
		else
		{
			if ((root->left == nullptr) || (root->right == nullptr))
			{
				ProductNode* temp = root->left ? root->left : root->right;
				if (temp == nullptr)
				{
					temp = root;
					root = nullptr;
				}
				else
				{
					*root = *temp;
				}
				delete temp;
			}
			else
			{
				ProductNode* temp = minValueNode(root->right);
				root->productName = temp->productName;
				root->right = deleteNodeRec(root->right, temp->productName);
			}
		}
		if (root == nullptr)
		{
			return root;
		}
		root->height = 1 + max(height(root->left), height(root->right));
		int balanceFactor = getBalanceFactor(root);
		if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0)
		{
			return rightRotate(root);
		}
		if (balanceFactor > 1 && getBalanceFactor(root->left) < 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0)
		{
			return leftRotate(root);
		}
		if (balanceFactor < -1 && getBalanceFactor(root->right) > 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}
	/*ProductNode* deleteNodeRec(ProductNode* root, string name) {
		if (root == NULL) {
			return root;
		}
		if (name < root->productName) {
			root->left = deleteNodeRec(root->left, name);
		}
		else if (name > root->productName) {
			root->right = deleteNodeRec(root->right, name);
		}
		else {
			if (root->left == NULL) {
				ProductNode* temp = root->right;
				delete root;
				return temp;
			}
			else if (root->right == NULL) {
				ProductNode* temp = root->left;
				delete root;
				return temp;
			}
			ProductNode* temp = minValueNode(root->right);
			root->productName = temp->productName;
			root->right = deleteNodeRec(root->right, temp->productName);
		}
		return root;
	}*/
	ProductNode* minValueNode(ProductNode* root)
	{
		ProductNode* current = root;
		while (current && current->left != NULL)
		{
			current = current->left;
		}
		return current;
	}
	void countProducts() {
		if (root)
		{
			queue<ProductNode*> q;

			q.push(root);
			while (!q.empty())
			{
				ProductNode* n = q.front();
				q.pop();
				if (n->quantity == 0) {
					cout << "\nProduct is out of stock\nProduct Name: ";
					cout << n->productName;
					
				}
				if (n->left)
					q.push(n->left);
				if (n->right)
					q.push(n->right);
			}
		}
	}
};
class ProductCategoryNode
{
public:
	string categoryName;
	string unique_id;
	ProductCategoryNode* left;
	ProductCategoryNode* right;
	ProductTree productTree;
	int height;
	ProductCategoryNode(string name, string categoryID)
	{
		categoryName = name;
		left = right = NULL;
		// generate random id
		if (categoryID == " ")
			unique_id = generateUniqueID('t');
		else
			unique_id = categoryID;
		height = 1;
	}
	ProductTree& getProdutTree() { return this->productTree; }
	void setProductTree(ProductTree tree) {
		tree;
		this->productTree = tree; 
	}
};

// Use binary search trees to store products based on categories
class ProductCategoryTree
{
public:
	ProductCategoryNode* root;
	
	ProductCategoryTree()
	{
		root = NULL;
	}
	void insert(string name, string id = " ")
	{
		root = insertRec(root, name, id);
		// return this->;
	}
	ProductCategoryNode* insertRec(ProductCategoryNode* node, string name, string id)
	{
		if (node == nullptr)
			return new ProductCategoryNode(name, id);
		if (name < node->categoryName)
			node->left = insertRec(node->left, name, id);
		else if (name > node->categoryName)
			node->right = insertRec(node->right, name, id);
		else
			return node;
		node->height = 1 + max(height(node->left), height(node->right));
		int balanceFactor = getBalanceFactor(node);
		if (balanceFactor > 1)
		{
			if (name < node->left->categoryName)
			{
				return rightRotate(node);
			}
			else if (name > node->left->categoryName)
			{
				node->left = leftRotate(node->left);
				return rightRotate(node);
			}
		}
		if (balanceFactor < -1)
		{
			if (name > node->right->categoryName)
			{
				return leftRotate(node);
			}
			else if (name < node->right->categoryName)
			{
				node->right = rightRotate(node->right);
				return leftRotate(node);
			}
		}
		return node;
	}
	void insertTree(ProductCategoryTree tree) {
		insert(tree.root->categoryName, tree.root->unique_id);

		if (root)//adding product tree of categorytree of parameter to root
		{
			queue<ProductCategoryNode*> q;
			q.push(root);
			while (!q.empty())
			{
				ProductCategoryNode* n = q.front();
				q.pop();
				if (n->unique_id == tree.root->unique_id) {
					n->setProductTree(tree.getProductTreeFromCategoryTree());
				}
				if (n->left)
					q.push(n->left);
				if (n->right)
					q.push(n->right);
			}
		}


		//root->setProductTree(tree.getProductTreeFromCategoryTree());
		
	}
	ProductTree getProductTreeFromCategoryTree() {
		return root->getProdutTree();
	}
	
	int size()
	{
		return sizeRec(root);
	}
	int sizeRec(ProductCategoryNode* root)
	{
		if (root == NULL)
			return 0;
		return sizeRec(root->left) + sizeRec(root->right) + 1;
	}

	// convert to array function
	string* convertToArray()
	{
		string* arr = new string[size()];
		int i = 0;
		convertToArrayRec(root, arr, i);
		return arr;
	}
	void convertToArrayRec(ProductCategoryNode* root, string* arr, int& i)
	{
		if (root == NULL)
			return;
		convertToArrayRec(root->left, arr, i);
		arr[i++] = root->categoryName;
		convertToArrayRec(root->right, arr, i);
	}
	/*ProductCategoryNode* insertRec(ProductCategoryNode* root, string name) {
		if (root == NULL) {
			return new ProductCategoryNode(name);
		}
		if (name < root->categoryName) {
			root->left = insertRec(root->left, name);
		}
		else if (name > root->categoryName) {
			root->right = insertRec(root->right, name);
		}
		return root;
	}*/
	void inorder()
	{
		inorderRec(root);
	}
	void inorderRec(ProductCategoryNode* root)
	{
		if (root != NULL)
		{
			inorderRec(root->left);
			cout << root->categoryName << endl;
			inorderRec(root->right);
		}
	}
	void levelorder()
	{
		levelorderRec(root);
	}
	void levelorderRec(ProductCategoryNode* root)
	{
		if (root)
		{
			queue<ProductCategoryNode*> q;
			q.push(root);
			while (!q.empty())
			{
				ProductCategoryNode* n = q.front();
				q.pop();
				cout << n->categoryName << " ";
				if (n->left)
					q.push(n->left);
				if (n->right)
					q.push(n->right);
			}
		}
	}
	string writeCategoriesInFile(ofstream& os, string id)
	{
		string category_id;
		if (root)
		{
			queue<ProductCategoryNode*> q;
			q.push(root);
			while (!q.empty())
			{
				ProductCategoryNode* n = q.front();
				q.pop();
				fout << id << endl;
				category_id = n->unique_id;
				fout << n->unique_id << endl;
				fout << n->categoryName << endl;
				//				id = n->unique_id;
				if (n->left)
					q.push(n->left);
				if (n->right)
					q.push(n->right);
			}
		}
		return category_id;
	}
	void writeProductsInFile(ofstream& os)
	{
		if (root)
		{
			queue<ProductCategoryNode*> q;
			q.push(root);
			while (!q.empty())
			{
				ProductCategoryNode* n = q.front();
				q.pop();
				string id;
				id = n->unique_id;// talha
				n->getProdutTree().writeProductsInFile(os, id);
				if (n->left)
					q.push(n->left);
				if (n->right)
					q.push(n->right);
			}
		}
	}
	/*void writeProductsInFile(ofstream& os, string category_id)
	{
		if (root)
		{
			queue<ProductCategoryNode*> q;
			q.push(root);
			while (!q.empty())
			{
				ProductCategoryNode* n = q.front();
				q.pop();
				n->getProdutTree().writeProductsInFile(os, category_id);
				if (n->left)
					q.push(n->left);
				if (n->right)
					q.push(n->right);
			}
		}
	}*/
	ProductCategoryNode* search(string name)
	{
		return searchRec(root, name);
	}
	ProductCategoryNode* searchRec(ProductCategoryNode* root, string name)
	{
		if (root == NULL || root->categoryName == name)
		{
			return root;
		}
		if (name < root->categoryName)
		{
			return searchRec(root->left, name);
		}
		return searchRec(root->right, name);
	}
	void deleteNode(string name)
	{
		root = deleteNodeRec(root, name);
	}
	ProductCategoryNode* deleteNodeRec(ProductCategoryNode* root, string name)
	{
		if (root == nullptr)
			return root;
		if (name < root->categoryName)
			root->left = deleteNodeRec(root->left, name);
		else if (name > root->categoryName)
			root->right = deleteNodeRec(root->right, name);
		else
		{
			if ((root->left == nullptr) || (root->right == nullptr))
			{
				ProductCategoryNode* temp = root->left ? root->left : root->right;
				if (temp == nullptr)
				{
					temp = root;
					root = nullptr;
				}
				else
					*root = *temp;
				delete temp;
			}
			else
			{
				ProductCategoryNode* temp = minValueNode(root->right);
				root->categoryName = temp->categoryName;
				root->right = deleteNodeRec(root->right, temp->categoryName);
			}
		}
		if (root == nullptr)
			return root;
		root->height = 1 + max(height(root->left), height(root->right));
		int balanceFactor = getBalanceFactor(root);
		if (balanceFactor > 1)
		{
			if (getBalanceFactor(root->left) >= 0)
			{
				return rightRotate(root);
			}
			else
			{
				root->left = leftRotate(root->left);
				return rightRotate(root);
			}
		}
		if (balanceFactor < -1)
		{
			if (getBalanceFactor(root->right) <= 0)
			{
				return leftRotate(root);
			}
			else
			{
				root->right = rightRotate(root->right);
				return leftRotate(root);
			}
		}
		return root;
	}
	/*ProductCategoryNode* deleteNodeRec(ProductCategoryNode* root, string name) {
		if (root == NULL) {
			return root;
		}
		if (name < root->categoryName) {
			root->left = deleteNodeRec(root->left, name);
		}
		else if (name > root->categoryName) {
			root->right = deleteNodeRec(root->right, name);
		}
		else {
			if (root->left == NULL) {
				ProductCategoryNode* temp = root->right;
				delete root;
				return temp;
			}
			else if (root->right == NULL) {
				ProductCategoryNode* temp = root->left;
				delete root;
				return temp;
			}
			ProductCategoryNode* temp = minValueNode(root->right);
			root->categoryName = temp->categoryName;
			root->right = deleteNodeRec(root->right, temp->categoryName);
		}
		return root;
	}*/
	ProductCategoryNode* minValueNode(ProductCategoryNode* root)
	{
		ProductCategoryNode* current = root;
		while (current && current->left != NULL)
		{
			current = current->left;
		}
		return current;
	}
	ProductCategoryNode* validCategory(string str)
	{
		return validCategoryRec(root, str);
	}
	ProductCategoryNode* validCategoryRec(ProductCategoryNode* ptr, string str)
	{
		if (!ptr)
			return nullptr;
		if (ptr->categoryName == str)
			return ptr;
		ProductCategoryNode* foundInLeft = validCategoryRec(ptr->left, str);
		if (foundInLeft)
			return foundInLeft;

		return validCategoryRec(ptr->right, str);
	}
	int height(ProductCategoryNode* N)
	{
		if (!N)
			return 0;

		return N->height;
	}
	int getBalanceFactor(ProductCategoryNode* N)
	{
		if (!N)
			return 0;
		return height(N->left) - height(N->right);
	}
	ProductCategoryNode* rightRotate(ProductCategoryNode* y)
	{
		ProductCategoryNode* x = y->left;
		ProductCategoryNode* T2 = x->right;
		x->right = y;
		y->left = T2;
		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;
		return x;
	}
	ProductCategoryNode* leftRotate(ProductCategoryNode* x)
	{
		ProductCategoryNode* y = x->right;
		ProductCategoryNode* T2 = y->left;
		y->left = x;
		x->right = T2;
		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;
		return y;
	}
	void checkCategories() {
		checkCategoriesRec(root);
	}
	void checkCategoriesRec(ProductCategoryNode* root) {
		cout << "\nNotifications:\n\n"; //show seller if a particular product is over
		if (root)
		{
			Queue<ProductCategoryNode*> q;
			q.push(root);
			while (!q.empty())
			{
				ProductCategoryNode* n = q.peek();
				q.pop();
				n->getProdutTree().countProducts();

				if (n->left)
					q.push(n->left);
				if (n->right)
					q.push(n->right);
			}
		}
		cout << endl<<endl;
		system("pause");
	}
};


string cit[8] = { "Lahore","Faisalabad","Multan","Karachi","Islamabad","Okara","Murree","Kashmir" };
int getindex(string source) {
	for (int i = 0; i < 8; i++) {
		if (cit[i] == source) {
			return i;
		}
	}
}
class CityNode {
public:

	//string name;
	int index;
	int weight;
	CityNode* next;

	CityNode(int index, int weight) : index(index), next(nullptr), weight(weight) {}
};
class City {

public:
	string name;
	int index;
	static int i;
	CityNode* head;
	City(string a) :name(a), index(i++), head(nullptr) {}
	City() :name(""), index(i++), head(nullptr) {}

	void addCity(string cityName, int weight) {
		CityNode* newCity = new CityNode(getindex(cityName), weight);
		if (head == nullptr) {
			head = newCity;
		}
		else {
			CityNode* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = newCity;
		}

	}

	void viewCities() {
		if (head == nullptr) {
			cout << "No cities to display." << endl;
			return;
		}
		CityNode* temp = head;
		while (temp != nullptr) {
			cout << temp->index << " -->  " << temp->weight << " kms" << endl;
			temp = temp->next;
		}
	}
};
int City::i = 0;

class PriorityQueue {

	CityNode* head;  // Head pointer of the linked list

public:
	PriorityQueue() : head(nullptr) {}

	// Insert node while maintaining sorted order
	void insert(int cityIndex, int weight) {
		CityNode* newNode = new CityNode(cityIndex, weight);

		// If the list is empty or the new node has the smallest weight
		if (!head || weight < head->weight) {
			newNode->next = head;
			head = newNode;
			return;
		}

		// Traverse the list to find the correct position
		CityNode* temp = head;
		while (temp->next && temp->next->weight <= weight) {
			temp = temp->next;
		}

		// Insert the new node
		newNode->next = temp->next;
		temp->next = newNode;
	}

	// Extract and remove the node with the minimum weight (head node)
	int extractMin() {
		if (!head) {
			cout << "Priority Queue is empty!\n";
			return -1;
		}

		CityNode* temp = head;
		int minCityIndex = temp->index;

		head = head->next;  // Move the head to the next node
		delete temp;        // Free the old head node

		return minCityIndex;
	}

	// Check if the queue is empty
	bool isEmpty() {
		return head == nullptr;
	}
};

class Graph {
	City* city;
public:
	Graph() {
		initiateCity();
		initiateWeights();
	}
	~Graph() {
		delete[] city;
	}
	void initiateCity() {
		city = new City[8];

		for (int i = 0; i < 8; i++) {
			city[i].name = cit[i];
		}
	}
	void initiateWeights() {
		// Lahore connections
		city[0].addCity("Faisalabad", 128);
		city[0].addCity("Multan", 232);
		city[0].addCity("Karachi", 350);
		city[0].addCity("Islamabad", 290);
		// Faisalabad connections
		city[1].addCity("Lahore", 128);
		city[1].addCity("Islamabad", 185);
		city[1].addCity("Multan", 200);
		city[1].addCity("Okara", 160);
		// Multan connections
		city[2].addCity("Karachi", 756);
		city[2].addCity("Okara", 146);
		city[2].addCity("Faisalabad", 200);
		city[2].addCity("Murree", 400);
		// Karachi connections 
		city[3].addCity("Multan", 756);
		city[3].addCity("Murree", 367);
		city[3].addCity("Lahore", 350);
		city[3].addCity("Kashmir", 800);
		// Islamabad connections 
		city[4].addCity("Lahore", 290);
		city[4].addCity("Kashmir", 237);
		city[4].addCity("Faisalabad", 185);
		city[4].addCity("Okara", 170);
		// Okara connections 
		city[5].addCity("Islamabad", 170);
		city[5].addCity("Murree", 215);
		city[5].addCity("Multan", 146);
		city[5].addCity("Faisalabad", 160);
		// Murree connections 
		city[6].addCity("Kashmir", 467);
		city[6].addCity("Lahore", 215);
		city[6].addCity("Karachi", 367);
		city[6].addCity("Multan", 400);
		// Kashmir connections 
		city[7].addCity("Islamabad", 237);
		city[7].addCity("Lahore", 185);
		city[7].addCity("Karachi", 800);
		city[7].addCity("Murree", 467);
	}
	void viewGraph() {
		for (int i = 0; i < 8; i++) {
			cout << "City: " << city[i].name << endl;
			city[i].viewCities();
			cout << endl;
		}
	}
	int* dijakstra(string source) {
		int index = getindex(source);

		//visited cities
		bool visited[8];

		//array of weights
		int weight[8];
		int max = 999999;

		//intializing weight with max and visting false
		for (int i = 0; i < 8; i++) {
			weight[i] = max;
			visited[i] = false;
		}
		weight[index] = 0;

		PriorityQueue pq;
		pq.insert(index, 0);

		City* cityptr;
		while (!pq.isEmpty()) {
			int minIndex = pq.extractMin(); //dequeue and get index of next city which weight is less
			cityptr = &city[minIndex]; //get that city from array of city
			CityNode* nodeptr = cityptr->head; //get head of its linked list
			while (nodeptr) {
				if (!visited[nodeptr->index]) {
					if (nodeptr->weight + weight[minIndex] < weight[nodeptr->index]) {
						weight[nodeptr->index] = nodeptr->weight + weight[minIndex];
						pq.insert(nodeptr->index, weight[nodeptr->index]);
					}
				}
				nodeptr = nodeptr->next;
			}


			visited[minIndex] = true;
		}

		return weight;
	}
};





class Seller
{
private:
	static int sellerStaticId;
	int sellerId;
	string uniqueID;
	string name;
	string email;
	string password;
	string role;
	string address;
	int productStock;
	bool toDelete;
	// product tree of this seller
	ProductCategoryTree categoryTree;

public:
	Seller() : sellerId(sellerStaticId++), email(""), password(""), role("seller"), address(""), productStock(0), toDelete(false), uniqueID(generateUniqueID('s')) {}
	void setProductStock(int stock) { productStock = stock; }
	int getProductStock() const { return productStock; }
	void setEmail(const string& email) { this->email = email; }
	string getEmail() const { return email; }
	void setUniqueID(const string& e) { this->uniqueID = e; }
	string getUniqueID() const { return uniqueID; }
	void setPassword(const string& password) { this->password = password; }
	string getPassword() const { return password; }
	int getSellerId() const { return sellerId; }
	void setAddress(const string& address) { this->address = address; }
	string getAddress() const { return address; }
	void setToDelete(bool flag) { toDelete = flag; }
	bool getToDelete() const { return toDelete; }
	string getRole() const { return role; }
	void setName(const string& name) { this->name = name; }
	string getName() const { return name; }

	// get Product tree
	ProductCategoryTree& getProductCategoryTree() { return categoryTree; }
	void setProductCategoryTree(ProductCategoryNode* tree) { categoryTree.root = tree; }
	void insertDetails()
	{
		cout << "Enter your email id: ";
		getline(cin, email);
		cout << "Enter your password: ";
		getline(cin, password);
		cout << "Enter your address: ";
		getline(cin, address);
	}
	void displayDetails() const
	{
		if (!toDelete)
		{
		
			Table table;
			table.add_row({"Seller ID", "Seller Name", "Email", "Password", "Address", "Product Stock"});
			table.add_row({to_string(sellerId), name, email, password, address, to_string(productStock)});
            //format headings
			for(int i = 0; i < 6; i++)
			{
				table[0][i].format()
					.font_color(Color::yellow)
					.font_align(FontAlign::center)
					.font_style({FontStyle::bold});
			}
		}
	}
};

// stack for cart
class CartItem
{
public:
	ProductNode* product;
	int quantity;
	CartItem* next;
	CartItem(ProductNode* product, int quantity)
	{
		this->product = product;
		this->quantity = quantity;
		next = NULL;
	}
};

class Cart
{
public:
	CartItem* top;
	Cart()
	{
		top = NULL;
	}
	void push(ProductNode* product, int quantity)
	{
		CartItem* temp = new CartItem(product, quantity);
		temp->next = top;
		top = temp;
	}
	void pop()
	{
		if (top == NULL)
		{
			cout << "Cart is empty\n";
			return;
		}
		CartItem* temp = top;
		top = top->next;
		delete temp;
	}
	void display()
	{
		cout << "Your Cart\n";
		CartItem* temp = top;
		if (temp == NULL)
		{
			cout << "Cart is empty\n";
			return;
		}
		Table table;
		table.add_row({"Product Name", "Quantity" , "Seller ID" , "Product Price (Rs)"});
		while (temp)
		{
			//get int seller id of the seller of the product
			//display product name, quantity and seller id
			
			

			
			table.add_row({temp->product->productName, to_string(temp->quantity), temp->product->sellerID, to_string(temp->product->productPrice*temp->quantity)});
			temp = temp->next;
		}
		for(int i = 0; i < 4; i++)
		{
			table[0][i].format()
				.font_color(Color::green)
				.font_align(FontAlign::center)
				.font_style({FontStyle::bold});
		}
		cout << table;
		cout<<endl;
	}
	int calculateTotal()
	{
		int total = 0;
		CartItem* temp = top;
		while (temp)
		{
			total += temp->product->productPrice * temp->quantity;
			temp = temp->next;
		}
		return total;
	}
	// search and delete item from cart and also increasq quantity for that product

	void deleteItem(string name)
	{
		CartItem* temp = top;
		CartItem* prev = NULL;
		while (temp && temp->product->productName != name)
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL)
		{
			cout << "Item not found\n";
			return;
		}
		if (prev == NULL)
		{
			top = temp->next;
		}
		else
		{
			prev->next = temp->next;
		}
		
		delete temp;
	}
};

class SearchItem
{

public:
	// implement using linked list
	string name;
	SearchItem* next;

	SearchItem(string name)
	{
		this->name = name;
		next = NULL;
	}
};

class SearchHistory
{
public:
	SearchItem* head;

	SearchHistory()
	{
		head = NULL;
	}
	// push , pop functions
	void push(string name)
	{
		//dont push if duplicate
		SearchItem* ptr = head;
		while (ptr) {
			if (ptr->name == name) return;
			ptr = ptr->next;

		}
		SearchItem* temp = new SearchItem(name);
		temp->next = head;
		head = temp;
	}
	void pop()
	{
		if (head == NULL)
		{
			cout << "No search history\n";
			return;
		}
		SearchItem* temp = head;
		head = head->next;
		delete temp;
	}
	void display()
	{
		SearchItem* temp = head;
		Table table;
		table.add_row({"Sr No.", "Product Name"});
		int i=0;
		while (temp)
		{
			table.add_row({to_string(++i), temp->name});
			


			
			temp = temp->next;
		}
		for(int i = 0; i < 2; i++)
		{
			table[0][i].format()
				.font_color(Color::green)
				.font_align(FontAlign::center)
				.font_style({FontStyle::bold});
		}
		cout << table;
		cout<<endl;
	}
};

class Customer
{
private:
	static int customerIdCounter;
	int customerId;
	string uniqueID;
	string email;
	string password;
	string address;
	string role;
	bool toDelete;
	int loyaltyPoints;
	// search history of this customer
	SearchHistory searchHistory;
	// cart of this customer
	Cart cart;

public:
	Customer() : customerId(customerIdCounter++), email(""), password(""), address(""), role("customer"), toDelete(false), loyaltyPoints(0), uniqueID(generateUniqueID('p')) {}
	void setLoyaltyPoints(int points) { loyaltyPoints = points; }
	int getLoyaltyPoints() const { return loyaltyPoints; }
	void setEmail(const string& email) { this->email = email; }
	string getEmail() const { return email; }
	void setUniqueID(const string& e) { this->uniqueID = e; }
	string getUniqueID() const { return uniqueID; }
	void setPassword(const string& password) { this->password = password; }
	string getPassword() const { return password; }
	int getCustomerId() const { return customerId; }
	void setAddress(const string& address) { this->address = address; }
	string getAddress() const { return address; }
	void setToDelete(bool flag) { toDelete = flag; }
	bool getToDelete() const { return toDelete; }
	string getRole() const { return role; }

	Cart& getCart() { return cart; }

	SearchHistory& getSearchHistory() { return searchHistory; }

	void insertDetails()
	{
		cout << "Enter your email id: ";
		getline(cin, email);
		cout << "Enter your password: ";
		getline(cin, password);
		cout << "Enter your address: ";
		getline(cin, address);
	}
	void displayDetails(string mode) const
	{
		
		if(mode=="individual"){
			Table table;
		if (!toDelete )
		{
			table.add_row({"Customer ID", to_string(customerId)});
			table.add_row({"Customer Email", email});
			table.add_row({"Customer Address", address});
			table.add_row({"Loyalty Points", to_string(loyaltyPoints)});
			table.add_row({"Role", role});

			
			

		}
		for(int i = 0; i < 5; i++)
		{
			table[i][0].format()
				.font_color(Color::green)
				.font_align(FontAlign::center)
				.font_style({FontStyle::bold});
		}
		
		cout << table;
		//make first column green only

	}
	if(mode=="all"){
		Table table;
		table.add_row({"Customer ID", "Customer Email", "Customer Address", "Loyalty Points", "Role"});
		if (!toDelete )
		{
			table.add_row({to_string(customerId), email, address, to_string(loyaltyPoints), role});
		}
		for(int i = 0; i < 5; i++)
		{
			table[i][0].format()
				.font_color(Color::green)
				.font_align(FontAlign::center)
				.font_style({FontStyle::bold});
		}
		cout << table;
	}

	}

};

// queue for orders
class OrderItem
{
public:
	ProductNode* product;
	string status;
	string orderID;
	string sellerID;
	string customerID;
	OrderItem* next;
	int quantity;
	vector<string> deliveryCities;
	OrderItem(ProductNode* product, string status, string orderID, string sellerID, string customerID, int quantity,string customerCity)
	{
		this->product = product;
		this->status = status;
		this->orderID = orderID;
		this->sellerID = sellerID;
		this->customerID = customerID;
		this->quantity = quantity;
		deliveryCities.push_back(customerCity);
		next = NULL;
	}
};
int Customer::customerIdCounter = 0;
int Seller::sellerStaticId = 0;

vector<Customer> customers;
vector<Seller> sellers;
class Order
{
public:
	OrderItem* front;
	OrderItem* rear;
	Order()
	{
		front = rear = NULL;
	}
	void enqueue(ProductNode* ProductNode, string status, string orderID, string sellerID, string customerID, int quantity,string customerCity)
	{
		OrderItem* temp = new OrderItem(ProductNode, status, orderID, sellerID, customerID, quantity,customerCity);
		if (rear == NULL)
		{
			front = rear = temp;
			return;
		}
		rear->next = temp;
		rear = temp;
	}
	void dequeue()
	{
		if (front == NULL)
		{
			cout << "Order is empty\n";
			return;
		}
		OrderItem* temp = front;
		front = front->next;
		if (front == NULL)
		{
			rear = NULL;
		}
		delete temp;
	}

	void changeStatus(string orderID, string status)
	{
		OrderItem* temp = front;
		while (temp && temp->orderID != orderID)
		{
			temp = temp->next;
		}
		if (temp == NULL)
		{
			cout << "Order not found\n";
			return;
		}
		temp->status = status;
	}

	void cancelStatus(OrderItem* front, string orderID)
	{
		OrderItem* temp = front;
		while (temp && temp->orderID != orderID)
		{
			temp = temp->next;
		}
		if (temp == NULL)
		{
			cout << "Order not found\n";
			return;
		}
		temp->status = "Cancelled";
		temp->product->quantity += temp->quantity;

	}

	void dispatchStatus(string orderID)
	{
		OrderItem* temp = front;
		while (temp && temp->orderID != orderID)
		{
			temp = temp->next;
		}
		if (temp == NULL)
		{
			cout << "Order not found\n";
			return;
		}
		temp->status = "Dispatched";

		for (auto& seller : sellers)
		{
			if (seller.getUniqueID() == temp->sellerID)
			{
				cout << "Order dispatched from: " << seller.getAddress() << endl;
				break;
			}
		}
		for (auto& customer : customers)
		{
			if (customer.getUniqueID() == temp->customerID)
			{
				cout << "Order dispatched to: " << customer.getAddress() << endl;
				break;
			}
		}


	}

	void display(string customerID = "null", string sellerID = "null")
	{
		if (customerID != "null")
		{
			Table table;
			OrderItem* temp = front;
			bool found = false;
			table.add_row({"Order ID", "Product Name", "Quantity", "Status", "Seller ID" , "Total Price"});
			while (temp)
			{
				if (temp->customerID == customerID)
				{
					table.add_row({temp->orderID, temp->product->productName, to_string(temp->quantity), temp->status, temp->sellerID, to_string(temp->quantity*temp->product->productPrice)});
					found = true;
				}
				temp = temp->next;
			}

			if (!found)
			{
				cout << "No orders found\n";
				system("pause");
				return;
			}
			for(int i = 0; i < 6; i++)
			{
				table[0][i].format()
					.font_color(Color::green)
					.font_align(FontAlign::center)
					.font_style({FontStyle::bold});
			}
			cout << table;
			cout<<endl;


		}
		else if (sellerID != "null")
		{
			OrderItem* temp = front;
			bool found = false;
			Table table;
			table.add_row({"Order ID", "Product Name", "Quantity", "Status", "Customer ID" , "Total Price"});
			while (temp)
			{
				if (temp->sellerID == sellerID)
				{
					table.add_row({temp->orderID, temp->product->productName, to_string(temp->quantity), temp->status, temp->customerID, to_string(temp->quantity*temp->product->productPrice)});
					found = true;
				}
				temp = temp->next;
			}
			if (!found)
			{
				cout << "No orders found\n";
				system("pause");
				return;
			}
			for(int i = 0; i < 6; i++)
			{
				table[0][i].format()
					.font_color(Color::green)
					.font_align(FontAlign::center)
					.font_style({FontStyle::bold});
			}
		}
		else
		{
			OrderItem* temp = front;
			while (temp)
			{
				cout << "Order ID: " << temp->orderID << endl;
				cout << "Product Name: " << temp->product->productName << endl;
				cout << "Quantity: " << temp->quantity << endl;
				cout << "Status: " << temp->status << endl;
				cout << "Seller ID: " << temp->sellerID << endl;
				cout << "Customer ID: " << temp->customerID << endl;
				cout << "====================================\n";
				temp = temp->next;
			}
		}
		system("pause");
	}

	void deleteItem(string name)
	{
		OrderItem* temp = front;
		OrderItem* prev = NULL;
		while (temp && temp->product->productName != name)
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL)
		{
			cout << "Item not found\n";
			return;
		}
		if (prev == NULL)
		{
			front = temp->next;
		}
		else
		{
			prev->next = temp->next;
		}
		delete temp;
	}

	void sellerDispatch(string sellerid) {
		OrderItem* temp = front;
		bool found = false;
		if (front) {
			while (temp) {
				Table table;
				table.add_row({"Order ID", "Product Name", "Quantity", "Status", "Customer ID"});
				if(temp->sellerID == sellerid && temp->status=="Ordered") {
					table.add_row({temp->orderID, temp->product->productName, to_string(temp->quantity), temp->status, temp->customerID});
					found = true;
					cout << "Want to dispatch this ?\nPress y:  ";
					string a;
					cin >> a;
					if (a == "y" || a == "Y") {
						temp->status = "Dispatched";
					}
					for(int i = 0; i < 5; i++)
					{
						table[0][i].format()
							.font_color(Color::green)
							.font_align(FontAlign::center)
							.font_style({FontStyle::bold});
					}
					cout << table << endl;
				}
				
				temp = temp->next;
			}
			if (!found) {
				cout << "\nNo orders in the dispatch\n\n";
				return;
				
			}
			


		}
		else {
			cout << "No orders in the dispatch";
		}
	}
	void orderHistory(string sellerid) {
		OrderItem* temp = front;
		int total = 0;
		bool found = false;
		Table table;
		table.add_row({"Order ID", "Product Name", "Quantity", "Status", "Customer ID"});
		if (front) {
			
			while (temp) {
				if (temp->sellerID == sellerid && temp->status == "Dispatched") {
					table.add_row({temp->orderID, temp->product->productName, to_string(temp->quantity), temp->status, temp->customerID});
					found = true;
					int multiply= temp->quantity * temp->product->productPrice;
					total += multiply;
				}

				temp = temp->next;
			}

			if(found){
				for(int i = 0; i < 5; i++)
				{
					table[0][i].format()
						.font_color(Color::green)
						.font_align(FontAlign::center)
						.font_style({FontStyle::bold});
				}
				cout << table;
				cout<<endl;
			}

			if (!found) {
				cout << "No orders in the dispatch";
				return;

			}
			

			else {
				cout << "\n\nTotal sales: " << total;
			}
			
		}
		else {
			cout << "No orders in the dispatch";
		}
	}
};
Order orderQueue;


void viewCart()
{

	do {
		system("cls");
		cout << green << endl;
		header();
		cout << "\n\n\n\n";
		cout << "Main Menu > Customer Menu > View Cart\n\n" << white;
		//check empty cart
		if (customers[loggedInCustomerId].getCart().top == NULL) {
			cout << "Cart is empty\n";
			Sleep(1500);
			return;
		}
		// view cart of logged in customer
		for (auto& customer : customers)
		{
			if (customer.getCustomerId() == loggedInCustomerId)
			{
				customer.getCart().display();
				break;
			}
		}
		// calculate total
		int total = 0;
		for (auto& customer : customers)
		{
			if (customer.getCustomerId() == loggedInCustomerId)
			{
				total = customer.getCart().calculateTotal();
				break;
			}
		}
		cout << "Total: " << total << endl;
		// if want to delete something


		cout << "1. Delete Item\n";
		cout << "2. Checkout\n";
		cout << "3. Go Back\n";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			string name;
			cout << "Enter product name to delete: ";
			cin >> name;
			for (auto& customer : customers)
			{
				if (customer.getCustomerId() == loggedInCustomerId)
				{
					customer.getCart().deleteItem(name);
					break;
				}
			}
			break;
		}
		case 2:
		{
			// checkout
			// add to orders
			for (auto& customer : customers)
			{
				if (customer.getCustomerId() == loggedInCustomerId)
				{
					double total = 0, product = 0;
					CartItem* temp = customer.getCart().top;
					cout << endl;
					while (temp)
					{
						cout << "Order queued\n";
						
						// Decrease quantity
						temp->product->quantity -= temp->quantity;
						product = temp->quantity * temp->product->productPrice;
						total += product;
						temp->product->buyerID = customer.getUniqueID();
						orderQueue.enqueue(temp->product, "Ordered", generateUniqueID('o'), temp->product->sellerID, customer.getUniqueID(), temp->quantity,customer.getAddress());
						temp = temp->next;
					}
					customer.getCart().top = NULL;
					cout << "Order placed successfully\n";
					int originalTotal = total;//if total get change below we will award loyalty points based on this
					cout << "\nOriginal amount to pay: " << total;
					int loylaltypoints = customers[loggedInCustomerId].getLoyaltyPoints();
					if (loylaltypoints > 0) {
						cout << "\nWant to use your loyalty points?";
						cout << "\nCurrent points: " << loylaltypoints;
						cout << "\nYou will get discount of: " << loylaltypoints * 0.01;
						string c;

						cout << "\nEnter Y  to use all your loyalty points: ";
						cin >> c;
						if (c == "Y" || c == "y") {
							if (loylaltypoints * 0.01 > total) {
								//if loyality points are greater enough to pay his whole bill
								int p = loylaltypoints * 0.01;
								p -= total;
								total = 0;

								//remaning loyalty  points are setted
								customers[loggedInCustomerId].setLoyaltyPoints(p);
							}
							else {
								customers[loggedInCustomerId].setLoyaltyPoints(0);
								total -= loylaltypoints * 0.01;
							}
							

						}
					}
					
					cout << "\nTotal amount payed: " << total;
					if (total == 0) {
						cout << "\nYour whole bill was payed with help of loyalty points";
					}
					cout << "\nTotal loyalty points earned: " << originalTotal * 10;
					Sleep(2500);
					int currentpoints= customers[loggedInCustomerId].getLoyaltyPoints();

					customers[loggedInCustomerId].setLoyaltyPoints((originalTotal * 10)+currentpoints);
					return;
					break;
				}



			} }
		break;
		case 3:
			cout << "Going back...\n";
			Sleep(1500);
			return;
		default:
			cout << "Invalid choice\n";
			break;
		}
	} while (true && customers[loggedInCustomerId].getCart().top != NULL);
	// checkout or go back


}

void viewOrders()
{
	// view orders of logged in customer
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Customer Menu > View Orders\n\n" << white;
	for (auto& customer : customers)
	{
		if (customer.getCustomerId() == loggedInCustomerId)
		{
			orderQueue.display(customer.getUniqueID());
			
			break;
		}
	}
}

Admin admin("a", "a");

void manageCategories()
{
	int choice = 0;

	do
	{
		system("cls");
		cout << green << endl;
		header();
		cout << "\n\n\n\n";
		cout << "Main Menu > Seller Menu > Manage Categories\n\n" << white;

		cout << "1.Add Category\n";
		// cout << "2.Delete Category\n";
		cout << "2.Update Category\n";
		cout << "3.Search Category\n";
		cout << "4.View All Category\n";
		cout << "5.Manage Products\n";
		cout << "6.Go Back\n";

		cin >> choice;
		switch (choice)
		{
		case 1:
			addCategory();
			break;
		case 2:
			updateCategory();
			break;
		case 3:
			searchCategory();
			break;
		case 4:
			viewAllCategory();
			break;
		case 5:
			manageProducts();
			break;
		case 6:
			cout << "Going back...\n";
			Sleep(1500);
			return;
		default:
			cout << "Invalid choice\n";
			break;
		}

	} while (true);
}

void addCategory()
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Seller Menu > Manage Categories > Add Category\n\n" << white;
	string name;
	cout << "Enter Category name: ";
	cin.ignore();
	getline(cin, name);
	if (name == "")
	{ // if name is empty
		cout << "Name cannot be empty\n";
		Sleep(1500);
		return;
	}

	// productTree of logged in seller
	sellers[loggedInSellerId].getProductCategoryTree().insert(name);

	cout << "\nCategory added successfully\n";
	Sleep(1500);
	return;
}

void updateCategory()
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Seller Menu > Manage Categories > Update Category\n\n" << white;
	string name;

	try {
		cout << "Enter Category name: ";
		cin >> name;
	}
	catch (const exception& e) {
		cout << "An error occurred: " << e.what() << endl;
		return;
	}

	ProductCategoryNode* product = sellers[loggedInSellerId].getProductCategoryTree().search(name);
	if (product != NULL)
	{
		try {
			cout << "\nEnter new name: ";
			cin >> name;
			product->categoryName = name;
		}
		catch (const exception& e) {
			cout << "An error occurred: " << e.what() << endl;
		}
	}
	else
	{
		cout << "Category not found\n";
		Sleep(1500);
	}
	cout << "Category updated successfully\n";
	Sleep(1500);
	return;
}
void searchCategory()
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Seller Menu > Manage Categories > Search Category\n\n" << white;
	string name;
	cout << "Enter Category name: ";
	cin >> name;
	ProductCategoryNode* product = sellers[loggedInSellerId].getProductCategoryTree().search(name);
	if (product != NULL)
	{
		cout << "Category found\n";
		cout << "Name: " << product->categoryName << endl;
		Sleep(1500);
		return;
	}
	else
	{
		cout << "Category not found\n";
		Sleep(1500);

	}
}
void viewAllCategory()
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Seller Menu > Manage Categories > View All Categories\n\n" << white;
	sellers[loggedInSellerId].getProductCategoryTree().inorder();
	Sleep(1500);
}

void displayAdminMenu()
{



	int choice = 0;

	do
	{
		system("cls");
		cout << green << endl;
		header();
		cout << "\n\n\n\n";
		cout << "Main Menu > Admin Menu\n\n" << white;

		cout << "1. Customer options\n2. Seller options\n3. Exit\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			displayCustomerMenu();
			break;
		case 2:
			displaySellerMenu();
			break;
		case 3:
			cout << "Exiting...\n";
			return;
		default:
			cout << "Invalid choice\n";
			break;
		}

	} while (true);
}

void addSeller()
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Admin Menu > Seller Options > Add Seller\n\n" << white;
	cin.ignore();
	Seller seller;
	seller.insertDetails();
	sellers.push_back(seller);
	cout << "Added successfully\n";
	Sleep(1500);
}

void deleteSeller(int id)
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Admin Menu > Seller Options > Delete Seller\n\n" << white;
	for (auto& seller : sellers)
	{
		if (seller.getSellerId() == id)
		{
			seller.setToDelete(true);
			cout << "Deleted successfully\n";
			Sleep(1500);
			return;
		}
	}
	cout << "Not Found\n";
	Sleep(1500);
}

void updateSeller(int id)
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Admin Menu > Seller Options > Update Seller\n\n" << white;
	for (auto& seller : sellers)
	{
		if (seller.getSellerId() == id)
		{
			seller.displayDetails();
			int choice;
			string update;
			cout << "1.Edit Email\n2.Edit Password\n3.Edit Address\n4.Go back\n";
			cin >> choice;
			cin.ignore();
			switch (choice)
			{
			case 1:
				cout << "Enter the new email: ";
				getline(cin, update);
				seller.setEmail(update);
				break;
			case 2:
				cout << "Enter the new password: ";
				getline(cin, update);
				seller.setPassword(update);
				break;
			case 3:
				cout << "Enter the new address: ";
				getline(cin, update);
				seller.setAddress(update);
				break;
			case 4:
				cout << "Going Back..." << endl;
				return;
			default:
				cout << "Invalid choice\n";
				break;
			}
			cout << "Updated successfully\n";

			cout << "Updated Seller Details:\n";

			seller.displayDetails();
			system("Pause");

			return;
		}
	}
	cout << "Not Found\n";
}

void searchSeller(int id)
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Admin Menu > Seller Options > Search Seller\n\n" << white;
	for (const auto& seller : sellers)
	{
		if (seller.getSellerId() == id)
		{
			seller.displayDetails();
			system("Pause");
			return;
		}
	}
	cout << "Not Found\n";
	Sleep(1500);
}

void viewAllSellers()
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Admin Menu > Seller Options > View All Sellers\n\n" << white;
	for (const auto& seller : sellers)
	{
		seller.displayDetails();
		cout << endl
			<< endl;

	}
	system("Pause");
}

void displaySellerMenu()
{
	int id = 0, choice = 0;

	do
	{
		system("cls");
		cout << green << endl;
		header();
		cout << "\n\n\n\n";
		cout << "Main Menu > Admin Menu > Seller Options\n\n" << white;
		cout << "1. Add new seller\n2. Delete existing seller\n3. Update existing seller\n4. Search existing seller\n5. View all sellers\n6. Go back\n";
		cin >> choice;
		if (choice == 2 || choice == 3 || choice == 4)
		{
			cout << "Enter the id of the seller: ";
			cin >> id;
		}
		switch (choice)
		{
		case 1:
			addSeller();
			break;
		case 2:
			deleteSeller(id);
			break;
		case 3:
			updateSeller(id);
			break;
		case 4:
			searchSeller(id);
			break;
		case 5:
			viewAllSellers();
			break;
		case 6:
			cout << "Going Back..." << endl;
			return;
		default:
			cout << "Invalid choice\n";
			break;
		}

	} while (true);
}

void updateCustomer(int id)
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Admin Menu > Customer Options > Update Customer\n\n" << white;
	for (auto& customer : customers)
	{
		if (customer.getCustomerId() == id)
		{
			customer.displayDetails("individual");
			int choice, points;
			string update;
			cout << "1.Edit Email\n2.Edit Password\n3.Edit loyalty points\n4.Edit address\n5.Go back\n";
			cin >> choice;
			cin.ignore();
			switch (choice)
			{
			case 1:
				cout << "Enter the new email: ";
				getline(cin, update);
				customer.setEmail(update);
				break;
			case 2:
				cout << "Enter the new password: ";
				getline(cin, update);
				customer.setPassword(update);
				break;
			case 3:
				cout << "Enter loyalty points: ";
				cin >> points;
				customer.setLoyaltyPoints(points);
				break;
			case 4:
				cout << "Enter the new address: ";
				getline(cin, update);
				customer.setAddress(update);
				break;
			case 5:
				cout << "Going Back..." << endl;
				return;
			default:
				cout << "Invalid choice\n";
				break;
			}
			cout << "Updated successfully\n";
			system("Pause");

			customer.displayDetails("individual");
			return;
		}
	}
	cout << "Customer Not Found...\n";
	Sleep(1500);
}

void addCustomer()
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Admin Menu > Customer Options > Add Customer\n\n" << white;

	cin.ignore();
	Customer customer;
	customer.insertDetails();
	customers.push_back(customer);
	cout << "Added successfully...\n";
	Sleep(1500);
}

void searchCustomer(int id)
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Admin Menu > Customer Options > Search Customer\n\n" << white;
	for (const auto& customer : customers)
	{
		if (customer.getCustomerId() == id)
		{
			customer.displayDetails("individual");
			system("Pause");
			return;
		}
	}
	cout << "Not Found\n";
	Sleep(1500);
}

void deleteCustomer(int id)
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Admin Menu > Customer Options > Delete Customer\n\n" << white;
	for (auto& customer : customers)
	{
		if (customer.getCustomerId() == id)
		{
			customer.displayDetails("individual");
			//confirm delete
			string choice;
			cout << "Are you sure you want to delete this customer? [y/n]: ";
			cin >> choice;
			if (choice == "Y" || choice == "y")
			{
				customer.setToDelete(true);
				cout << "Deleted successfully\n";
				Sleep(1500);
				return;
			}

			return;
		}
	}
	cout << "Not Found\n";
}

void viewAllCustomers()
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Admin Menu > Customer Options > View All Customers\n\n" << white;
	for (const auto& customer : customers)
	{
		customer.displayDetails("all");
		cout << endl
			<< endl;
	}
	system("Pause");
}

void displayCustomerMenu()
{


	int id = 0, choice = 0;
	string loopChoice;
	do
	{
		system("cls");
		cout << green << endl;
		header();
		cout << "\n\n\n\n";
		cout << "Main Menu > Admin Menu > Customer Options\n\n" << white;

		cout << "1.Add new customer\n2.Delete existing customer\n3.Update existing customer\n4.Search existing customer\n5.View all customers\n6.Go back\n";
		cin >> choice;
		if (choice == 2 || choice == 3 || choice == 4)
		{
			cout << "Enter the id of the customer: ";
			cin >> id;
		}
		switch (choice)
		{
		case 1:
			addCustomer();
			break;
		case 2:
			deleteCustomer(id);
			break;
		case 3:
			updateCustomer(id);
			break;
		case 4:
			searchCustomer(id);
			break;
		case 5:
			viewAllCustomers();
			break;
		case 6:
			cout << "Going Back..." << endl;
			return;
		default:
			cout << "Invalid choice\n";
			break;
		}

	} while (true);
}

void adminLogin()
{
	system("cls");


	cout << green << endl;
	header();


	cout << "\n\n\n\n";
	cout << "Main Menu > Admin Login\n\n" << white;

	string email, password;
	cout << "Enter the email: ";
	cin.ignore();    //email ka phla alphabet gayab ho rha tha
	getline(cin, email);

	cout << "Enter the password: ";
	getline(cin, password);
	if (email == admin.getEmail() && password == admin.getPassword())
	{
		cout << "Logged in successfully\n";

		Sleep(2000);
		system("cls");
		displayAdminMenu();
	}
	else
	{
		cout << "Invalid email or password\n";


		Sleep(2000);

		system("cls");
	}
}

void addProduct(ProductCategoryNode* category)
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Seller Menu > Manage Products > Add Product\n\n" << white;
	string name;
	int price, quantity;
	cout << "Enter product name: ";
	getline(cin, name);
	cin >> name;
	if (name == "")
	{
		cout << "Name cannot be empty\n";
		Sleep(1500);
		return;
	}
	try {
		cout << "Enter product price: ";
		cin >> price;
		cout << "Enter product quantity: ";
		cin >> quantity;
	}
	catch (const exception& e) {
		cout << "An error occurred: " << e.what() << endl;

		system("Pause");
		return;
	}
	// producttree of logged in seller
	category->getProdutTree().insert(name, price, quantity," ", sellers[loggedInSellerId].getUniqueID());

	cout << "\nProduct added...\n";
	Sleep(1500);
	return;

}

void deleteProduct(ProductCategoryNode* category)
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Seller Menu > Manage Products > Delete Product\n\n" << white;
	cout << "\nAll products in this category: ";
	viewAllProducts(category);

	string name;
	cout << "Enter product name: ";
	cin >> name;

	//confirmation
	char c;
	cout << "Are you sure you want to delete this product? [y/n]: ";
	cin >> c;
	if (c == 'y' || c == 'Y')
	{
		category->getProdutTree().deleteNode(name);
		cout << name << " Deleted";
		Sleep(1500);
		return;

	}
	else
		cout << "Deletion cancelled";




	return;
}
void updateProduct(ProductCategoryNode* category,bool onlyUpdateQuantity)
{ //if onlyUpdateQuantity  is 1 we will ony update quantity
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Seller Menu > Manage Products > Update Product\n\n" << white;

	string name;
	int price, quantity;
	try {
		cout << "Enter product name: ";
		cin >> name;
		if (!onlyUpdateQuantity) {
		cout << "Enter product price: ";
		cin >> price;

		}
		cout << "Enter product quantity: ";
		cin >> quantity;
	}
	catch (const exception& e) {
		cout << "An error occurred: " << e.what() << endl;
		return;
	}
	ProductNode* product = category->getProdutTree().search(name);

	if (product != NULL)
	{
		if (!onlyUpdateQuantity) {
		product->productPrice = price;

		}
		product->quantity = quantity;
	}
	else
	{
		cout << "Product not found\n";
	}
	cout << name << "  updated";
	Sleep(1500);
	return;
}
void searchProduct(ProductCategoryNode* category)
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Seller Menu > Manage Products > Search Product\n\n" << white;

	string name;
	cout << "Enter product name: ";
	cin >> name;
	ProductNode* product = category->getProdutTree().search(name);

	if (product != NULL)
	{
		cout << "Product found\n";
		cout << "Name: " << product->productName << endl;
		cout << "Price: " << product->productPrice << endl;
		cout << "Quantity: " << product->quantity << endl;
		cout << "Seller ID: " << product->sellerID << endl;
		system("Pause");

	}
	else
	{
		cout << "Product not found\n";
		Sleep(1500);
	}
	return;
}
void viewAllProducts(ProductCategoryNode* category)
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Seller Menu > Manage Products > View All Products\n\n" << white;
	category->getProdutTree().inorder();
	category->getProdutTree().levelorder();
	Sleep(1500);

	return;
}

void manageProducts()
{
	int choice = 0;
	char yt;
	do
	{
		system("cls");
		cout << green << endl;
		header();
		cout << "\n\n\n\n";
		cout << "Main Menu > Seller Menu > Manage Products\n\n" << white;
		sellers[loggedInSellerId].getProductCategoryTree().inorder();

		cout << "\nEnter name of category in which you want to manage Product: ";
		string str;
		cin >> str;
		system("cls");
		cout << green << endl;
		header();
		cout << "\n\n\n\n";
		cout << "Main Menu > Seller Menu > Manage Products\n\n" << white;

		ProductCategoryNode* category = sellers[loggedInSellerId].getProductCategoryTree().validCategory(str);
		if (category)
		{

			cout << "1.Add Product\n";
			cout << "2.Delete Product\n";
			cout << "3.Update Product\n";
			cout << "4.Search Product\n";
			cout << "5.View All Products\n";
			cout << "6. Update quantity\n";
			cout << "7.Go Back\n";

			cin >> choice;
			switch (choice)
			{
			case 1:
				addProduct(category);
				break;
			case 2:
				deleteProduct(category);
				break;
			case 3:
				updateProduct(category,0);
				break;
			case 4:
				searchProduct(category);
				break;
			case 5:
				viewAllProducts(category);
				break;
			case 7:
				cout << "Going back...\n";
				return;
			case 6:
				updateProduct(category, 1);
			default:
				cout << "Invalid choice\n";
				Sleep(1500);
				break;
			}
		}
		else
		{
			cout << "\nIncorrect category name...";
			Sleep(1500);

		}
		cout << "Do you want to go stay? Press Y: ";
		
		cin >> yt;

	} while (yt=='Y'||yt=='y');
}
// seller menu

void dispatchOrders() {
	orderQueue.sellerDispatch(sellers[loggedInSellerId].getUniqueID());
}
void viewHistory() {
	orderQueue.orderHistory(sellers[loggedInSellerId].getUniqueID());

}
void viewNotifications() {
	sellers[loggedInSellerId].getProductCategoryTree().checkCategories(); //counting products here
	//if product is zero we show notifcation
}
void manageOrders()
{
	int choice = 0;
	
	do
	{
		system("cls");
		cout << green << endl;
		header();
		cout << "\n\n\n\n";
		cout << "Main Menu > Seller Menu > Manage Orders\n\n" << white;

		cout << "1. View Orders\n";
		cout << "2. Dispatch Orders\n";
	
		cout << "3. Go Back\n";

		cin >> choice;
		switch (choice)
		{
		case 1:
			// pass seller id to view orders
			for (auto& seller : sellers)
			{
				if (seller.getSellerId() == loggedInSellerId)
				{
					orderQueue.display("null", seller.getUniqueID());
				}
			}
			break;
		case 2:
			dispatchOrders();
			system("pause");
			break;
		case 3:
			cout << "Going back...\n";
			return;
	
		default:
			cout << "Invalid choice\n";
			break;
		};
	} while (true);
}

void sellerMenu()
{
	int choice = 0;
	char yt;
	do
	{

		system("cls");
		cout << green << endl;
		header();
		cout << "\n\n\n\n";
		cout << "Main Menu > Seller Menu\n\n" << white;
		cout << "1. Manage Categories\n";
		cout << "2. Manage Products\n";
		cout << "3. Manage Orders\n";
		cout << "4. View Profile\n";
		cout << "5. Update Profile\n";
		cout << "6. View History\n";
		cout << "7. Check notifications\n";
		cout << "8. Logout\n";

		cin >> choice;
		switch (choice)
		{
		case 1:
			manageCategories();
			break;
		case 2:
			manageProducts();
			break;
		case 3:
			manageOrders();
			break;
		case 4:
			// viewProfile();
			break;
		case 5:
			 //updateProfile();
			break;
		case 6:
			 viewHistory();
			break;
		case 8:
			cout << "Logging out...\n";
			Sleep(2000);
			return;
		case 7:
			viewNotifications();
			break;
		default:
			cout << "Invalid choice\n";
			Sleep(1500);
			break;
		}

	} while (true);
}

void SellerLogin()
{

	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Seller Login\n\n" << white;
	string email, password;
	cout << "Enter the email: ";
	cin.ignore();
	getline(cin, email);
	cout << "Enter the password: ";
	getline(cin, password);
	for (const auto& seller : sellers)
	{
		if (email == seller.getEmail() && password == seller.getPassword())
		{
			cout << "Logged in successfully\n";
			loggedInSellerId = seller.getSellerId();
			system("Pause");
			system("cls");
			sellerMenu();
			return;
		}
	}
	cout << "Invalid email or password\n";
	Sleep(2000);
	system("cls");
}

void viewCategories()
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > View Categories\n\n" << white;

	// total size of all the categories
	int sizeTotalCategories = 0;
	for (auto& seller : sellers)
	{
		sizeTotalCategories += seller.getProductCategoryTree().size();
	}
	// dynamic array of that size
	string* allCategories = new string[sizeTotalCategories];
	int j = 0;
	for (auto& seller : sellers)
	{
		string* categories = seller.getProductCategoryTree().convertToArray();
		int size = seller.getProductCategoryTree().size();
		for (int i = 0; i < size; i++)
		{
			allCategories[j] = categories[i];
			j++;
		}
		delete[] categories;
	}

	// Remove duplicates

	// Display unique categories
	cout << "Available Categories:\n";
	// two inner loops to check if category is duplicate
	Table table;
	table.add_row({ "Sr No","Category Name"  });
	for (int i = 0; i < sizeTotalCategories; i++)
	{
		bool isDuplicate = false;
		for (int j = 0; j < i; j++)
		{
			if (allCategories[i] == allCategories[j])
			{
				isDuplicate = true;
				break;
			}
		}
		if (!isDuplicate)
		{
			table.add_row({ to_string(i+1),allCategories[i] });
		}

	}
	//make firs column gren
	for(int i=0;i<table.size();i++)
	{
		table[i][0].format().font_color(Color::green);
	}
	cout<<table<<endl;

	// customer will select a category
	// then we will show products of that category
	cout << "Enter the category name: ";
	string str;
	cin >> str;
	cout<<"============================="<<endl;
	// get all the products of that category name of all sellers
	// show to customer
	// search for category
	// if any product found then show products of that category
    bool foundCategory=false;
	for (auto& seller : sellers)
	{
		ProductCategoryNode* category = seller.getProductCategoryTree().search(str);
		if (category)
		{
			cout << "Seller ID: " << seller.getSellerId() << endl;
			category->getProdutTree().inorder();
			foundCategory=true;
			

		}
	}
	if(!foundCategory)
	{
		cout<<"Category not found\n";
	}
	system("Pause");

	return;
}

void viewProfile()
{
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > View Profile\n\n" << white;

	// details of logged in customer
	for (const auto& customer : customers)
	{
		if (customer.getCustomerId() == loggedInCustomerId)
		{
			customer.displayDetails("individual");
			system("Pause");
			return;
			break;
		}
	}
	return;
}

void updateProfile()
{
	// update details of logged in customer
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Customer Menu > Update Profile\n\n" << white;
	for (auto& customer : customers)
	{
		if (customer.getCustomerId() == loggedInCustomerId)
		{
			customer.displayDetails("individual");
			int choice, points;
			string update;
			cout << "1.Edit Email\n2.Edit Password\n3.Edit Address\n4.Go back\n";
			cin >> choice;
			cin.ignore();
			switch (choice)
			{
			case 1:
				cout << "Enter the new email: ";
				getline(cin, update);
				customer.setEmail(update);
				break;
			case 2:
				cout << "Enter the new password: ";
				getline(cin, update);
				customer.setPassword(update);
				break;

			case 3:
				cout << "Enter the new address: ";
				getline(cin, update);
				customer.setAddress(update);
				break;
			default:
				cout << "Invalid choice\n";
				break;
			}
			cout << "Updated successfully\n";
			cout << "Updated Profile Details:\n";
			customer.displayDetails("individual");
			system("Pause");
			return;
		}
	}
	cout << "Not Found\n";
	return;
}

// stack for search history

void searchProduct()
{
	// search product for customer
	// show search history of logged in customer
	system("cls");
	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Customer Menu > Search Product\n\n" << white;
	cout << "\nSearch History:\n";
	for (auto& customer : customers)
	{
		if (customer.getCustomerId() == loggedInCustomerId)
		{
			customer.getSearchHistory().display();
			break;
		}
	}
	cout << "====================================\n";
	cout << "Enter product name to search: ";
	string name;
	cin.ignore();
	getline(cin, name);

	// Add search term to search history
	for (auto& customer : customers)
	{
		if (customer.getCustomerId() == loggedInCustomerId)
		{
			customer.getSearchHistory().push(name);
			break;
		}
	}

	// Search for the product in all sellers' categories
	bool found = false;
	Table table;
	table.add_row({ "Seller ID","Category Name","Product Name","Price","Quantity" });
	for (auto& seller : sellers)
	{
		ProductCategoryNode* category = seller.getProductCategoryTree().root;
		queue<ProductCategoryNode*> q;
		if (category)
			q.push(category);
		while (!q.empty())
		{
			ProductCategoryNode* current = q.front();
			q.pop();
			ProductNode* product = current->getProdutTree().search(name);
			if (product && product->quantity!=0)
			{
				table.add_row({ to_string(seller.getSellerId()),current->categoryName,product->productName,to_string(product->productPrice),to_string(product->quantity) });
				found = true;
			}
			if (current->left)
				q.push(current->left);
			if (current->right)
				q.push(current->right);
		}
	}
	if(found){
		for(int i=0;i<table.size();i++)
		{
			table[i][0].format().font_color(Color::green).font_align(FontAlign::center).font_style({FontStyle::bold});
		}
		cout<<table<<endl;
	}



	if (!found)
	{
		cout << "Product not found\n";
		system("Pause");
		system("cls");
		return;
	}


	// order and add to cart
	cout << "Do you want to order this product? [y/n]: ";
	string choice;
	cin >> choice;
	
	if (choice == "Y" || choice == "y")
	{// by seller id
		int sellerId;
		cout << "Enter the seller id: ";
		cin >> sellerId;
		// order
		// add to cart
		// ask for quantity
		int quantity;
		try {
			cout << "Enter the quantity: ";

			cin >> quantity;
		}
		catch (const exception& e) {
			cout << "An error occurred: " << e.what() << endl;
			return;
		}
		if (quantity <= 0)
		{
			cout << "Invalid quantity\n";
			system("Pause");
			return;
		}

		// Search all products from all categories of that seller and add to cart of customer
		for (auto& seller : sellers)
		{
			if (seller.getSellerId() == sellerId)
			{
				queue<ProductCategoryNode*> q;
				if (seller.getProductCategoryTree().root)
					q.push(seller.getProductCategoryTree().root);
				while (!q.empty())
				{
					ProductCategoryNode* current = q.front();
					q.pop();
					ProductNode* product = current->getProdutTree().search(name);
					if (product)
					{
						if (product->quantity < quantity)
						{
							cout << "Not enough quantity\n";
							system("Pause");
							return;
						}
						for (auto& customer : customers)
						{
							if (customer.getCustomerId() == loggedInCustomerId)
							{
								customer.getCart().push(product, quantity);
								
								cout << "Product added to cart\n";
								system("Pause");


								break;
							}
						}
					}
					if (current->left)
						q.push(current->left);
					if (current->right)
						q.push(current->right);
				}
			}
		}
	}
}

void customerMenu()
{
	int choice = 0;

	do
	{
		system("cls");
		cout << green << endl;
		header();
		cout << "\n\n\n\n";
		cout << "Main Menu > Customer Menu\n\n" << white;

		cout << "1. View Categories\n";
		cout << "2. View Cart\n";
		cout << "3. View Orders\n";
		cout << "4. View Profile\n";
		cout << "5. Search Product\n";
		cout << "6. Update Profile\n";
		cout << "7. View History\n";
		cout << "8. Logout\n";

		cin >> choice;
		switch (choice)
		{
		case 1:
			viewCategories();
			break;
		case 2:
			viewCart();
			break;
		case 3:
			viewOrders();
			break;
		case 4:
			viewProfile();
			break;
		case 5:
			searchProduct();
			break;
		case 6:
			updateProfile();
			break;
		case 7:
			// viewHistory();
			break;
		case 8:
			cout << "Logging out...\n";
			Sleep(2000);
			return;
		default:
			cout << "Invalid choice\n";
			break;
		}

	} while (true);
}

void customerLogin()
{

	system("cls");

	cout << green << endl;
	header();
	cout << "\n\n\n\n";
	cout << "Main Menu > Customer Login\n\n" << white;
	string email, password;
	cout << "Enter the email: ";
	cin.ignore();
	getline(cin, email);
	cout << "Enter the password: ";
	getline(cin, password);
	for (const auto& customer : customers)
	{
		if (email == customer.getEmail() && password == customer.getPassword())
		{
			cout << "Logged in successfully\n";
			loggedInCustomerId = customer.getCustomerId();
			system("Pause");
			system("cls");
			customerMenu();
			return;
		}
	}
	cout << "Invalid email or password\n";
	Sleep(2000);
	system("cls");
}

void writeCustomersToFile()
{
	outputFile.open("customer.txt", ios::trunc);
	outputFile.close();
	outputFile.clear();
	outputFile.open("customer.txt", ios::app);
	if (outputFile.is_open())
	{
		for (const auto& customer : customers)
		{
			if (!customer.getToDelete())
			{
				outputFile << customer.getEmail() << endl;
				outputFile << customer.getUniqueID() << endl;
				outputFile << customer.getPassword() << endl;
				outputFile << customer.getAddress() << endl;
				outputFile << customer.getLoyaltyPoints() << endl;
			}
		}
		outputFile.close();
		outputFile.clear();
	}
	else
	{
		cout << "Error: Could not open file for writing.\n";
	}
}

void writeSellersToFile()
{
	string category_id;
	outputFile.open("seller.txt", ios::trunc);
	outputFile.close();
	outputFile.clear();
	fout_product.open("product.txt", ios::trunc);
	fout_product.close();
	fout_product.clear();
	fout.open("category.txt", ios::trunc);
	fout.close();
	fout.clear();
	int size = sellers.size();
	outputFile.open("seller.txt", ios::app);
	if (outputFile.is_open())
	{
		for (int i = 0; i < size; i++)
		{
			if (!sellers[i].getToDelete())
			{
				outputFile << sellers[i].getEmail() << endl;
				outputFile << sellers[i].getUniqueID() << endl;
				outputFile << sellers[i].getPassword() << endl;
				outputFile << sellers[i].getAddress() << endl;
				outputFile << sellers[i].getProductStock() << endl;

				fout.open("category.txt", ios::app);
				if (fout.is_open())
				{
					ProductCategoryTree* root = &sellers[i].getProductCategoryTree();
					if (root)
					{

						//root->writeCategoriesInFile(outputFile);
						//outputFile << "Products" << endl;
						category_id = root->writeCategoriesInFile(fout, sellers[i].getUniqueID());
						fout_product.open("product.txt", ios::app);
						if (fout_product.is_open())
						{//root->writeProductsInFile(outputFile);
							root->writeProductsInFile(fout_product);

						}
						fout_product.close();
						fout_product.clear();
					}
				}
			}
			fout.close();
			fout.clear();
		}
		outputFile.close();
		outputFile.clear();
	}
	else
	{
		cout << "Error: Could not open file for writing.\n";
	}
}


void readCustomersFromFile()
{
	inputFile.open("customer.txt");
	string email, password, address, unqiueid;
	int points = 0;
	if (inputFile.is_open())
	{
		while (inputFile >> email >> unqiueid >> password >> address >> points)
		{
			Customer temp;
			temp.setEmail(email);
			temp.setPassword(password);
			temp.setAddress(address);
			temp.setLoyaltyPoints(points);
			temp.setUniqueID(unqiueid);
			customers.push_back(temp);
		}
		inputFile.close();
		inputFile.clear();
	}
	else
	{
		cout << "Error: Could not open file for reading.\n";
	}
}

//void readSellersFromFile()
//{
//	inputFile.open("seller.txt");
//	string email, password, address, uniqueid, category_id, product_category_id, product_id, pname, cname;
//	int stock = 0, price = 0;
//	if (inputFile.is_open())
//	{
//		while (inputFile >> email >> uniqueid >> password >> address >> stock)
//		{
//			Seller temp;
//			ProductCategoryTree category;
//			ProductTree tree;
//			temp.setEmail(email);
//			temp.setUniqueID(uniqueid);
//			temp.setPassword(password);
//			temp.setAddress(address);
//			temp.setProductStock(stock);
//			fin.open("category.txt");
//			if (fin.is_open())
//			{
//				while (fin >> uniqueid)
//				{
//					if (temp.getUniqueID() == uniqueid)
//					{
//						fin >> category_id >> cname;
//						category.insert(cname, category_id);
//						fin_product.open("product.txt");
//						if (fin_product.is_open())
//						{
//							while (fin_product >> product_category_id)
//							{
//								if (category_id == product_category_id)
//								{
//									fin_product >> product_id >> pname >> price >> stock;
//									tree.insert(pname, price, stock, product_id);
//								}
//							}
//							category.root->getProdutTree().setProductTree(tree.root);
//							fin_product.close();
//							fin_product.clear();
//						}
//					}
//				}
//				temp.setProductCategoryTree(category.root);
//				fin.close();
//				fin.clear();
//			}
//			sellers.push_back(temp);
//		}
//		inputFile.close();
//		inputFile.clear();
//	}
//	else
//	{
//		cout << "Error: Could not open file for reading.\n";
//	}
//}
void readSellersFromFile()
{
	inputFile.open("seller.txt");
	string email, password, address, uniqueid, category_id, product_category_id, product_id, pname, cname;
	int stock = 0, price = 0;

	if (inputFile.is_open())
	{
		while (inputFile >> email >> uniqueid >> password >> address >> stock)
		{
			Seller temp;
			ProductCategoryTree Realcategory;
			

			temp.setEmail(email);
			temp.setUniqueID(uniqueid);
			temp.setPassword(password);
			temp.setAddress(address);
			temp.setProductStock(stock);

			fin.open("category.txt");
			if (fin.is_open())
			{
				while (fin >> uniqueid) // Read category data
				{
					if (temp.getUniqueID() == uniqueid)
					{
						ProductCategoryTree category;
						fin >> category_id >> cname; // Read category ID and name
						category.insert(cname, category_id); // Insert the category
						ProductTree tree;

						fin_product.open("product.txt"); // Open the product file
						if (fin_product.is_open())
						{
							// Loop through all products to find matches for the category
							while (fin_product >> product_category_id)
							{
								if (product_category_id[0] == 't' && category_id == product_category_id)
								{
									// Match found: Read product details
									fin_product >> product_id >> pname >> price >> stock;
									tree.insert(pname, price, stock, product_id, uniqueid); // Insert product into tree
								}
								/*else if (product_category_id[0] != 't')
									break;*/
							}

							// Assign the populated tree to the current category
							category.root->getProdutTree().setProductTree(tree.root);
							Realcategory.insertTree(category);
							
							// Reset product file stream for next category
							fin_product.close();
							fin_product.clear();
						}
					}
				}

				// Assign the populated category tree to the seller
				temp.setProductCategoryTree(Realcategory.root);

				// Reset category file stream for next seller
				fin.close();
				fin.clear();
			}

			// Add the seller to the list
			sellers.push_back(temp);
		}

		// Close the seller file
		inputFile.close();
		inputFile.clear();
	}
	else
	{
		cout << "Error: Could not open seller file for reading.\n";
	}
}
void menus()
{
	char c;

	do
	{

		//clear screen
		system("cls");
		cout << green << endl;
		header();
		cout << "\n\n\n\n";
		cout << "Main Menu\n" << white;
		cout << "\n1. Admin Menu";
		cout << "\n2. Seller Menu";
		cout << "\n3. Customer Menu";
		cout << "\n4. Exit\n";
		int choice;
		cout << "\nYour choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			adminLogin();
			break;
		case 2:
			SellerLogin();
			break;
		case 3:
			customerLogin();
			break;
		case 4:
			cout << "Exiting...\n";
			return;
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}


		/*if (c != 'y' && c != 'Y')
			break;*/
	} while (true);
}

int main()
{

	/*Seller s1;
	s1.setEmail("abc@xyz.com");
	s1.setPassword("123");
	s1.setAddress("Lahore");
	sellers.push_back(s1);
	Customer c1;
	c1.setEmail("abc@xyz.com");
	c1.setPassword("123");
	c1.setAddress("Lahore");
	customers.push_back(c1);*/

	outputFile.open("customer.txt", ios::app);
	outputFile.close();
	outputFile.clear();
	outputFile.open("seller.txt", ios::app);
	outputFile.close();
	outputFile.clear();
	outputFile.open("category.txt", ios::app);
	outputFile.close();
	outputFile.clear();
	outputFile.open("product.txt", ios::app);
	outputFile.close();
	outputFile.clear();
	readCustomersFromFile();
	readSellersFromFile();
	menus();
	writeSellersToFile();
	writeCustomersToFile();
	return 0;
}
