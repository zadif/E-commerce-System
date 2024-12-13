
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <chrono>
// #include"utils/Table.h"
#include <cstdlib>
using namespace std;
using namespace chrono;

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
class ProductCategoryTree;
class ProductCategoryNode;
class ProductTree;
class ProductNode;

ifstream inputFile;
ofstream outputFile;

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
	ProductNode(string name, int price, int quantity, string sellerid)
	{
		productName = name;
		productPrice = price;
		this->quantity = quantity;
		left = right = NULL;
		// generate random id
		productId = generateUniqueID('p');
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
	void insert(string name, int price, int quantity, string id)
	{
		root = insertRec(root, name, price, quantity, id);
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
	ProductNode* insertRec(ProductNode* node, string name, int price, int quantity, string id)
	{
		if (node == nullptr)
		{
			return new ProductNode(name, price, quantity, id);
		}
		if (name < node->productName)
		{
			node->left = insertRec(node->left, name, price, quantity, id);
		}
		else if (name > node->productName)
		{
			node->right = insertRec(node->right, name, price, quantity, id);
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
		inorderRec(root);
	}
	void inorderRec(ProductNode* root)
	{
		if (root != NULL)
		{
			inorderRec(root->left);

			// make table
			/*std::vector<std::string> headers = {"Name", "Age", "Country"};
	std::vector<std::vector<std::string>> data = {
		{"Alice", "30", "USA"},
		{"Bob", "25", "UK"},
		{"Charlie", "35", "Canada"}
	};

	Table table(headers, data);
	table.display();
	return 0;
	vector<std::string> headers = { "Name", "Price", "Quantity" };
	vector<std::vector<std::string>> data;
	data.push_back({ root->productName, "1", "1" });
	Table table(headers, data);*/

			cout << root->productName << " " << root->productPrice << " " << root->quantity << endl;
			inorderRec(root->right);
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
	void writeProductsInFile(ofstream& os)
	{
		if (root)
		{
			queue<ProductNode*> q;

			q.push(root);
			while (!q.empty())
			{
				ProductNode* n = q.front();
				q.pop();
				outputFile << n->productId << endl;
				outputFile << n->productName << endl;
				outputFile << n->productPrice << endl;
				outputFile << n->quantity << endl;

				if (n->left)
					q.push(n->left);
				if (n->right)
					q.push(n->right);
			}
		}
	}
	void readProductsFromFile(ifstream& inputFile ,bool& userFound) {
		string productid, productname;
		int price, quantity;
		string cat;
		if (inputFile.is_open())
		{
			while (inputFile >> productid && productid != "User")
			{
				inputFile >> productname>>price>>quantity;

				
				insert(productname,price,quantity,productid);
			}
			if (productid == "User") {
				userFound = true;
			}
		}
		else
		{
			cout << "Error: Could not open file for reading.\n";
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
};
class ProductCategoryNode
{
public:
	string categoryName;
	ProductCategoryNode* left;
	ProductCategoryNode* right;
	ProductTree productTree;
	int height;
	ProductCategoryNode(string name)
	{
		categoryName = name;
		left = right = NULL;
		// generate random id
		height = 1;
	}
	ProductTree& getProdutTree() { return this->productTree; }
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
	void insert(string name)
	{
		root = insertRec(root, name);
		// return this->;
	}
	ProductCategoryNode* insertRec(ProductCategoryNode* node, string name)
	{
		if (node == nullptr)
			return new ProductCategoryNode(name);
		if (name < node->categoryName)
			node->left = insertRec(node->left, name);
		else if (name > node->categoryName)
			node->right = insertRec(node->right, name);
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
	void writeCategoriesInFile(ofstream& os)
	{
		if (root)
		{
			queue<ProductCategoryNode*> q;
			q.push(root);
			while (!q.empty())
			{
				ProductCategoryNode* n = q.front();
				q.pop();
				outputFile << n->categoryName << endl;
				if (n->left)
					q.push(n->left);
				if (n->right)
					q.push(n->right);
			}
		}
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
				n->getProdutTree().writeProductsInFile(os);
				if (n->left)
					q.push(n->left);
				if (n->right)
					q.push(n->right);
			}
		}
	}
	void readCategoriesFromFile(ifstream& input) {
		string cat;
		if (inputFile.is_open())
		{
			while (inputFile >> cat)
			{
				if (cat == "Products") {
					break;
				}
				insert(cat);
			}

		}
		else
		{
			cout << "Error: Could not open file for reading.\n";
		}

	}
	void readProductsFromFile(ifstream& is) {
		bool userFound = false;
		if (root)
		{
			queue<ProductCategoryNode*> q;
			q.push(root);
			while (!q.empty())
			{
				ProductCategoryNode* n = q.front();
				q.pop();
				n->getProdutTree().readProductsFromFile(is,userFound);
				if (n->left)
					q.push(n->left);
				if (n->right)
					q.push(n->right);
			}
		}
	}
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
			cout << "ID: " << sellerId << endl;
			cout << "Email: " << email << endl;
			cout << "Password: " << password << endl;
			cout << "Address: " << address << endl;
			cout << "Role: " << role << endl;
			cout << "Product Stock: " << productStock << endl;
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
		}
		while (temp)
		{
			cout << temp->product->productName << " " << temp->product->productPrice << " " << temp->quantity << endl;
			temp = temp->next;
		}
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
		// increase quantity
		temp->product->quantity += temp->quantity;
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
		while (temp)
		{
			cout << temp->name << " " << endl;
			temp = temp->next;
		}
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
	Customer() : customerId(++customerIdCounter), email(""), password(""), address(""), role("customer"), toDelete(false), loyaltyPoints(0), uniqueID(generateUniqueID('p')) {}
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
	void displayDetails() const
	{
		if (!toDelete)
		{
			cout << "ID: " << customerId << endl;
			cout << "Email: " << email << endl;
			cout << "Password: " << password << endl;
			cout << "Address: " << address << endl;
			cout << "Role: " << role << endl;
			cout << "Loyalty Points: " << loyaltyPoints << endl;
		}
	}
};

// queue for orders
class OrderItem
{
public:
	ProductNode* product;
	string status;
	int orderID;
	string sellerID;
	string customerID;
	OrderItem* next;
	OrderItem(ProductNode* product, string status, int orderID, string sellerID, string customerID)
	{
		this->product = product;
		this->status = status;
		this->orderID = orderID;
		this->sellerID = sellerID;
		this->customerID = customerID;

		next = NULL;
	}
};

class Order
{
public:
	OrderItem* front;
	OrderItem* rear;
	Order()
	{
		front = rear = NULL;
	}
	void enqueue(ProductNode* ProductNode, string status, int orderID, string sellerID, string customerID)
	{
		OrderItem* temp = new OrderItem(ProductNode, status, orderID, sellerID, customerID);
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

	void changeStatus(int orderID, string status)
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

	void cancelStatus() {
		OrderItem* temp = front;
		while (temp)
		{
			if (temp->status == "Pending") {
				temp->status = "Cancelled";
				//change quantity
				temp->product->quantity += temp->product->quantity;
			}
			temp = temp->next;
		}
	}



	void display()
	{
		/**	vector<string> headers = {"Name", "Price", "Quantity", "Status", "OrderID", "SellerID", "CustomerID"};
			vector<vector<string>> data;

			OrderItem* temp = front;
			while (temp) {
				data.push_back({temp->name, to_string(temp->price), to_string(temp->quantity), temp->status, to_string(temp->orderID), to_string(temp->sellerID), to_string(temp->customerID)});
				temp = temp->next;
			}

			Table table(headers, data);
			table.display();*/
		OrderItem* temp = front;
		while (temp)
		{
			cout << temp->product->productName << " " << temp->product->productPrice << " " << temp->product->quantity << " " << temp->status << " " << temp->orderID << " " << temp->sellerID << " " << temp->customerID << endl;
		}
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
};

int Customer::customerIdCounter = 0;
int Seller::sellerStaticId = 0;

vector<Customer> customers;
vector<Seller> sellers;
Admin admin("a", "a");

void manageCategories()
{
	int choice = 0;
	string loopChoice;
	do
	{
		cout << "\n\nMANAGE Category\n";
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
			sellerMenu();
			return;
		default:
			cout << "Invalid choice\n";
			break;
		}
		cout << "Do you want to manage another category? [y]: ";
		cin >> loopChoice;
	} while (loopChoice == "Y" || loopChoice == "y");
}

void addCategory()
{
	string name;

	cout << "Enter Category name: ";
	cin.ignore();
	getline(cin, name);
	if (name == "")
	{ // if name is empty
		addCategory();
		return;
	}

	// productTree of logged in seller
	sellers[loggedInSellerId].getProductCategoryTree().insert(name);

	cout << "\nCategory added\n";
	return;
}

void updateCategory()
{
	string name;
	cout << "Enter Category name: ";
	cin >> name;

	ProductCategoryNode* product = sellers[loggedInSellerId].getProductCategoryTree().search(name);
	if (product != NULL)
	{
		cout << "\nEnetr new name: ";
		product->categoryName = name;
	}
	else
	{
		cout << "Category not found\n";
	}
	cout << name << "  updated";
	return;
}
void searchCategory()
{
	string name;
	cout << "Enter Category name: ";
	cin >> name;
	ProductCategoryNode* product = sellers[loggedInSellerId].getProductCategoryTree().search(name);
	if (product != NULL)
	{
		cout << "Category found\n";
		cout << "Name: " << product->categoryName << endl;
		return;
	}
	else
	{
		cout << "Category not found\n";
	}
}
void viewAllCategory()
{
	sellers[loggedInSellerId].getProductCategoryTree().inorder();

}

void displayAdminMenu()
{
	int choice = 0;
	cout << "ADMIN MENU\n";
	cout << "1. Customer options\n2. Seller options\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
		displayCustomerMenu();
		break;
	case 2:
		displaySellerMenu();
		break;
	default:
		cout << "Invalid choice\n";
		break;
	}
}

void addSeller()
{
	cin.ignore();
	Seller seller;
	seller.insertDetails();
	sellers.push_back(seller);
	cout << "Added successfully\n";
}

void deleteSeller(int id)
{
	for (auto& seller : sellers)
	{
		if (seller.getSellerId() == id)
		{
			seller.setToDelete(true);
			cout << "Deleted successfully\n";
			return;
		}
	}
	cout << "Not Found\n";
}

void updateSeller(int id)
{
	system("cls");
	for (auto& seller : sellers)
	{
		if (seller.getSellerId() == id)
		{
			seller.displayDetails();
			int choice;
			string update;
			cout << "1. To edit email\n2. To edit password\n3. To edit address\n";
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
			default:
				cout << "Invalid choice\n";
				break;
			}
			cout << "Updated successfully\n";
			system("Pause");
			system("cls");
			seller.displayDetails();
			return;
		}
	}
	cout << "Not Found\n";
}

void searchSeller(int id)
{
	for (const auto& seller : sellers)
	{
		if (seller.getSellerId() == id)
		{
			seller.displayDetails();
			return;
		}
	}
	cout << "Not Found\n";
}

void viewAllSellers()
{
	for (const auto& seller : sellers)
	{
		seller.displayDetails();
		cout << endl
			<< endl;
	}
}

void displaySellerMenu()
{
	int id = 0, choice = 0;
	string loopChoice;
	do
	{
		cout << "ADMIN MENU\nSELLER OPTIONS\n";
		cout << "1. To add new seller\n2. To delete existing seller\n3. To update existing seller\n4. To search existing seller\n5. To view all sellers\n";
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
		default:
			cout << "Invalid choice\n";
			break;
		}
		cout << "Do you want to perform another operation? [y]: ";
		cin >> loopChoice;
	} while (loopChoice == "Y" || loopChoice == "y");
}

void updateCustomer(int id)
{
	system("cls");
	for (auto& customer : customers)
	{
		if (customer.getCustomerId() == id)
		{
			customer.displayDetails();
			int choice, points;
			string update;
			cout << "1. To edit email\n2. To edit password\n3. To edit loyalty points\n4. To edit address\n";
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
			default:
				cout << "Invalid choice\n";
				break;
			}
			cout << "Updated successfully\n";
			system("Pause");
			system("cls");
			customer.displayDetails();
			return;
		}
	}
	cout << "Not Found\n";
}

void addCustomer()
{
	cin.ignore();
	Customer customer;
	customer.insertDetails();
	customers.push_back(customer);
	cout << "Added successfully\n";
}

void searchCustomer(int id)
{
	for (const auto& customer : customers)
	{
		if (customer.getCustomerId() == id)
		{
			customer.displayDetails();
			return;
		}
	}
	cout << "Not Found\n";
}

void deleteCustomer(int id)
{
	for (auto& customer : customers)
	{
		if (customer.getCustomerId() == id)
		{
			customer.setToDelete(true);
			cout << "Deleted successfully\n";
			return;
		}
	}
	cout << "Not Found\n";
}

void viewAllCustomers()
{
	for (const auto& customer : customers)
	{
		customer.displayDetails();
		cout << endl
			<< endl;
	}
}

void displayCustomerMenu()
{
	int id = 0, choice = 0;
	string loopChoice;
	do
	{
		cout << "ADMIN MENU\nCUSTOMER OPTIONS\n";
		cout << "1. To add new customer\n2. To delete existing customer\n3. To update existing customer\n4. To search existing customer\n5. To view all customers\n";
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
		default:
			cout << "Invalid choice\n";
			break;
		}
		cout << "Do you want to perform another operation? [y]: ";
		cin >> loopChoice;
	} while (loopChoice == "Y" || loopChoice == "y");
}

void adminLogin()
{
	string email, password;
	cout << "Enter the email: ";
	// cin.ignore();    //email ka phla alphabet gayab ho rha tha
	getline(cin, email);

	cout << "Enter the password: ";
	getline(cin, password);
	if (email == admin.getEmail() && password == admin.getPassword())
	{
		cout << "Logged in successfully\n";
		system("Pause");
		system("cls");
		displayAdminMenu();
	}
	else
	{
		cout << "Invalid email or password\n";

		system("Pause");
		system("cls");
	}
}

void addProduct(ProductCategoryNode* category)
{
	string name;
	int price, quantity;
	cout << "Enter product name: ";
	getline(cin, name);
	cin >> name;
	if (name == "")
	{
		addProduct(category);
		return;
	}
	cout << "Enter product price: ";
	cin >> price;
	cout << "Enter product quantity: ";
	cin >> quantity;
	// producttree of logged in seller
	category->getProdutTree().insert(name, price, quantity, sellers[loggedInSellerId].getUniqueID());

	cout << "\nproduct added\n";
	manageCategories();
}

void deleteProduct(ProductCategoryNode* category)
{
	cout << "\n~All products in this category: ";
	viewAllProducts(category);

	string name;
	cout << "Enter product name: ";
	cin >> name;
	category->getProdutTree().deleteNode(name);

	cout << name << " deleted";
	manageCategories();
}
void updateProduct(ProductCategoryNode* category)
{
	string name;
	int price, quantity;
	cout << "Enter product name: ";
	cin >> name;
	cout << "Enter product price: ";
	cin >> price;
	cout << "Enter product quantity: ";
	cin >> quantity;
	ProductNode* product = category->getProdutTree().search(name);

	if (product != NULL)
	{
		product->productPrice = price;
		product->quantity = quantity;
	}
	else
	{
		cout << "Product not found\n";
	}
	cout << name << "  updated";
	manageCategories();
}
void searchProduct(ProductCategoryNode* category)
{
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
	}
	else
	{
		cout << "Product not found\n";
	}
	return;
}
void viewAllProducts(ProductCategoryNode* category)
{
	category->getProdutTree().inorder();
	category->getProdutTree().levelorder();

	return;
}

void manageProducts()
{
	int choice = 0;
	string loopChoice;

	cout << "\n\n~~All categories: ";
	sellers[loggedInSellerId].getProductCategoryTree().inorder();

	cout << "\nEnter name of category in which you want to manage Product : ";
	string str;
	cin >> str;

	ProductCategoryNode* category = sellers[loggedInSellerId].getProductCategoryTree().validCategory(str);
	if (category)
	{
		cout << "\n\nMANAGE PRODUCTS\n";
		cout << "1.Add Product\n";
		cout << "2.Delete Product\n";
		cout << "3.Update Product\n";
		cout << "4.Search Product\n";
		cout << "5.View All Products\n";
		cout << "6.Go Back\n";

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
			updateProduct(category);
			break;
		case 4:
			searchProduct(category);
			break;
		case 5:
			viewAllProducts(category);
			break;
		case 6:
			sellerMenu();
			return;
		default:
			cout << "Invalid choice\n";
			break;
		}
	}
	else
	{
		cout << "\nIncorrect category name";
		cout << "\nRedirecting";
	}

}
// seller menu
void sellerMenu()
{
	int choice = 0;
	string loopChoice;
	do
	{
		cout << "SELLER MENU\n";
		cout << "1. Manage Categories\n";
		cout << "2. Manage Products\n";
		cout << "3. Manage Orders\n";
		cout << "4. View Profile\n";
		cout << "5. Update Profile\n";
		cout << "6. View History\n";
		cout << "7. Logout\n";

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
			// manageOrders();
			break;
		case 4:
			// viewProfile();
			break;
		case 5:
			// updateProfile();
			break;
		case 6:
			// viewHistory();
			break;
		case 7:
			cout << "Logging out...\n";
			menus();
			return;
		default:
			cout << "Invalid choice\n";
			break;
		}
		cout << "Do you want to perform another operation? [y]: ";
		cin >> loopChoice;
	} while (loopChoice == "Y" || loopChoice == "y");
}

void SellerLogin()
{
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
	system("Pause");
	system("cls");
}

void viewCategories()
{
	// view categories of all sellers to show to customer
	// show all categories only once if it comes twice
	// store categories names
	vector<string> categories;

	for (auto seller : sellers)
	{
		// do not show if the categroy name already exists
		for (auto category : categories)
		{
			if (category == seller.getProductCategoryTree().root->categoryName)
			{
				continue;
			}
			seller.getProductCategoryTree().inorder();
			categories.push_back(seller.getProductCategoryTree().root->categoryName);

		}
	}
	// customer will select a category
	// then we will show products of that category
	cout << "Enter the category name: ";
	string str;
	cin >> str;
	// get all the products of that category name of all sellers
	// show to customer
	// search for category
	for (auto& seller : sellers)
	{
		ProductCategoryNode* category = seller.getProductCategoryTree().search(str);
		if (category)
		{
			cout << "Seller Name: " << seller.getSellerId() << endl;
			category->getProdutTree().inorder();
			cout << "====================================\n";
		}
	}

	return;
}

void viewProfile()
{

	// details of logged in customer
	for (const auto& customer : customers)
	{
		if (customer.getCustomerId() == loggedInCustomerId)
		{
			customer.displayDetails();
			break;
		}
	}
	return;
}

void updateProfile()
{
	// update details of logged in customer
	for (auto& customer : customers)
	{
		if (customer.getCustomerId() == loggedInCustomerId)
		{
			customer.displayDetails();
			int choice, points;
			string update;
			cout << "1. To edit email\n2. To edit password\n3. To edit address\n";
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
			system("Pause");
			system("cls");
			customer.displayDetails();
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
	cout << "\nSearch History:\n";
	for (auto& customer : customers)
	{
		if (customer.getCustomerId() == loggedInCustomerId)
		{
			customer.getSearchHistory().display();
			break;
		}
	}
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
			if (product)
			{
				cout << "Product found in Seller, Name: " << seller.getName() << " ID: " << seller.getSellerId() << endl;
				cout << "Category: " << current->categoryName << endl;
				cout << "Name: " << product->productName << endl;
				cout << "Price: " << product->productPrice << endl;
				cout << "Quantity: " << product->quantity << endl;
				cout << "====================================\n";
				found = true;
			}
			if (current->left)
				q.push(current->left);
			if (current->right)
				q.push(current->right);
		}
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
	// by seller id
	int sellerId;
	cout << "Enter the seller id: ";
	cin >> sellerId;
	if (choice == "Y" || choice == "y")
	{
		// order
		// add to cart
		// ask for quantity
		cout << "Enter the quantity: ";
		int quantity;
		cin >> quantity;
		if (quantity <= 0)
		{
			cout << "Invalid quantity\n";
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
							return;
						}
						for (auto& customer : customers)
						{
							if (customer.getCustomerId() == loggedInCustomerId)
							{
								customer.getCart().push(product, quantity);
								// Decrease quantity
								product->quantity -= quantity;
								cout << "Product added to cart\n";
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


void viewCart()
{
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

	do
	{

		cout << "Do you want to delete an item from cart? [y/n]: ";
		string choice;
		cin >> choice;
		if (choice == "Y" || choice == "y")
		{
			cout << "Enter the name of the product to delete: ";
			string name;
			cin.ignore();
			getline(cin, name);
			for (auto& customer : customers)
			{
				if (customer.getCustomerId() == loggedInCustomerId)
				{
					customer.getCart().deleteItem(name);
					break;
				}
			}
		}
		else
		{
			break;
		}
	} while (true && customers[loggedInCustomerId].getCart().top != NULL);
	// checkout or go back
	cout << "Do you want to checkout? [y/n]: ";
	string choice;
	cin >> choice;
	if (choice == "Y" || choice == "y")
	{
		// checkout
		// add to orders

		// add to history
		// add loyalty points
		// empty cart
	}
	else
	{
		return;
	}
	return;
}

void viewOrders()
{
	// view orders of logged in customer
	//get orders from the order queue
	// display orders



}

void customerMenu()
{
	int choice = 0;
	string loopChoice;
	do
	{
		cout << "CUSTOMER MENU\n";
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
			// viewOrders();
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
			menus();
			return;
		default:
			cout << "Invalid choice\n";
			break;
		}
		cout << "Do you want to perform another operation? [y/n]: ";
		cin >> loopChoice;
	} while (loopChoice == "Y" || loopChoice == "y");
}

void customerLogin()
{
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
	system("Pause");
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
	outputFile.open("seller.txt", ios::trunc);
	outputFile.close();
	outputFile.clear();
	outputFile.open("seller.txt", ios::app);
	if (outputFile.is_open())
	{
		for (auto seller : sellers)
		{
			if (!seller.getToDelete())
			{
				outputFile << seller.getEmail() << endl;
				outputFile << seller.getUniqueID() << endl;
				outputFile << seller.getPassword() << endl;
				outputFile << seller.getAddress() << endl;
				outputFile << seller.getProductStock() << endl;
				ProductCategoryTree* root = &seller.getProductCategoryTree();
				if (root)
				{

					root->writeCategoriesInFile(outputFile);
					outputFile << "Products" << endl;
					root->writeProductsInFile(outputFile);
					outputFile << "User" << endl;

				}
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

void readSellersFromFile()
{
	inputFile.open("seller.txt");
	string email, password, address, uniqueid;
	int stock = 0;
	if (inputFile.is_open())
	{
		while (inputFile >> email >> uniqueid >> password >> address >> stock)
		{
			Seller temp;
			temp.setEmail(email);
			temp.setUniqueID(uniqueid);
			temp.setPassword(password);
			temp.setAddress(address);
			temp.setProductStock(stock);
			ProductCategoryTree* root = &temp.getProductCategoryTree();
			root->readCategoriesFromFile(inputFile);
			root->readProductsFromFile(inputFile);
			
			sellers.push_back(temp);
		}
		inputFile.close();
		inputFile.clear();
	}
	else
	{
		cout << "Error: Could not open file for reading.\n";
	}
}
void menus()
{
	do {
		cout << "\n1. Admin Menu";
		cout << "\n2. Seller Menu";
		cout << "\n3. Customer Menu";
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
		default:
			cout << "Invalid choice\n";
			break;
		}

		cout << "Want to login again? Enter y :  ";
		char c;
		cin >> c;
		if (c != 'y' && c != 'Y')
			break;
	} while (true);
}
int main()
{
	Seller s1;
	s1.setEmail("a");
	s1.setPassword("a");
	s1.setAddress("Lahore");
	sellers.push_back(s1);
	Customer c1;
	c1.setEmail("a");
	c1.setPassword("a");
	c1.setAddress("Lahore");
	customers.push_back(c1);

	outputFile.open("customer.txt", ios::app);
	outputFile.close();
	outputFile.clear();
	outputFile.open("seller.txt", ios::app);
	outputFile.close();
	outputFile.clear();
	readCustomersFromFile();
	readSellersFromFile();
	menus();
	writeSellersToFile();
	writeCustomersToFile();
	return 0;
}