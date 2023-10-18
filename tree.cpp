//Craig Bodo, CS 202, May 2018
//This file implements the Node and Tree class member functions.
#include "tree.h"

//Node class member function implementations
//
//Default constructor
node::node() 
{
	for(int i = 0; i < 2; ++i)
		data[i] = NULL;
	for(int j = 0; j < 3; ++j)
		child[j] = NULL;
}

//Constructor initializating chest object data
node::node(const chest & to_add) 
{
	if(has_none())
		data[0] = to_add;
	else if(has_one())
	{
		if(data[0] <= to_add)
		{
			data[1] = to_add;
		}
		else
		{
			data[1] = data[0];
			data[0] = to_add;
		}
	}
}

//Copy constructor
node::node(const node & to_copy): chest(to_copy)
{
	*this = to_copy;
}

//Destructor
node::~node()
{
	for(int j = 0; j < 3; ++j)
	{
		if(child[j])
			delete child[j];
		child[j] = NULL;
	}
}

//Adds a new achievement
node & node::insert_achievement(const chest & to_insert) 
{
	return (*this = to_insert);
}

//Returns true if there are no data items
bool node::has_none()
{
	if(!data[0].exists())
		return true;
	else
		return false;
}

//Returns true if node has one data item
bool node::has_one()
{
	if(data[0].exists() && !data[1].exists())
		return true;
	else return false;
}

//Returns true if node has two data items
bool node::has_two()
{
	if(data[1].exists())
		return true;
	else return false;
}

//Returns true if node has no children
bool node::is_leaf()
{
	if(!child[0])
		return true;
	else
		return false;
}

//Returns true if node has 2 children
bool node::two_node()
{

	if(child[1] && !child[2])
		return true;
	else
		return false;
}

//Returns true if node has 3 children
bool node::three_node()
{
	if(child[2])
		return true;
	else
		return false;
}

//Returns current node's left child
node *& node::left()
{
	return child[0];
}

//Returns current node's middle child
node *& node::middle()
{
	return child[1];
}

//Returns current node's right child
node *& node::right()
{
	if(!child[2])
		return child[1];
	else
		return child[2];
}

//Functions for Operator Overloading
//
//Overloads the += operator for chest data
//Checks chest data against node's data and inserts
//at the corresponding location in the node
node & node::operator += (const chest & to_add)
{
	if(this->has_none())
		data[0] = to_add;	
	else if(this->has_one())
	{
		if(data[0] > to_add)
		{
			data[1] = data[0];
			data[0] = to_add;
		}
		else
			data[1] = to_add;
	}
	return *this;
}

//Function to overload the += operator for a node
//Checks node for existing data, then against
//chest data to insert at the correct location
node & node::operator += (const node & to_add)
{
	node * new_root = new node;
	node * add_left = new node;
	node * add_right = new node;

	//if this is empty
	if(this->has_none())
	{
		*this = to_add;
		delete new_root;
		delete add_left;
		delete add_right;
	}
	//if this contains only one data member
	else if(this->has_one())
	{
		//if to_add contains only one data member
		if(to_add.data[1] == NULL)
		{
			//if to_add's data is larger than this
			if(this->data[0] < to_add.data[0])
			{
				//add to_add as this' second data member
				this->data[1] = to_add.data[0];
			}
			//else if to_add's data is smaller than this
			else
			{
				//swap this' data into second index,
				//add to_add's data to this' first index
				this->data[1] = this->data[0];
				this->data[0] = to_add.data[0];
			}
		}
		//if to_add contains two data members
		else
		{
			//if to_add's first data is smaller than this' data
			//but to_add's second data is larger than this' data
			if(this->data[0] > to_add.data[0] && this->data[0] < to_add.data[1])
			{
				//to_add's first data becomes this' left child
				add_left->data[0] = to_add.data[0];
				//to_add's second data becomes this' right child
				add_right->data[0] = to_add.data[1];
				this->left() = add_left;
				this->right() = add_right;
			}
			//if to_add's data is larger than this' data
			else if(this->data[0] < to_add.data[0])
			{
				//to_add's first data is new root
				new_root->data[0] = to_add.data[0];
				//this' data is root's left child
				add_left->data[0] = this->data[0];
				//to_add's second data is root's right child
				add_right->data[0] = to_add.data[1];
				new_root->left() = add_left;
				new_root->right() = add_right;
			}
		}
	}
	//if this contains two data[] members
	else if(this->has_two())
	{
		//if to_add contains only one data[] member
		if(to_add.data[1] == NULL)
		{
			//if to_add's data is smaller than this' first data
			if(this->data[0] > to_add.data[0])
			{
				//to_add is root's left child
				add_left->data[0] = to_add.data[0];
				//this' second data is root's right child
				add_right->data[0] = this->data[1];
				//remove second data from root
				this->data[1] = NULL;
				this->left() = add_left;
				this->right() = add_right;
			}
			//if to_add's data is larger than this' first data...
			else
			{
				//...and to_add's data is larger than this' second data
				if(this->data[1] < to_add.data[0])
				{
					//this' second data is root
					new_root->data[0] = this->data[1];
					//this' first data is root's left child
					add_left->data[0] = this->data[0];
					//to_add's data is root's right child
					add_right->data[0] = to_add.data[0];
					new_root->left() = add_left;
					new_root->right() = add_right;
				}
				//...and to_add's data is smaller than this' second data
				else
				{
					//to_add's data is root
					new_root->data[0] = to_add.data[0];
					//this's first data is root's left child
					add_left->data[0] = this->data[0];
					//this's second data is root's right child
					add_right->data[0] = this->data[1];
					new_root->left() = add_left;
					new_root->right() = add_right;
				}
			}
		}
		//if both this and to_add contain two data[] members
		else
		{
			//if all of two_add's data are smaller than this' first data
			if(this->data[0] > to_add.data[1])
			{
				//to_add's second data is root's first data
				//and this's first data is root's second data
				new_root->data[0] = to_add.data[1];
				new_root->data[1] = this->data[0];
				//to_add's first data is root's left child
				add_left->data[0] = to_add.data[0];
				//this' second data is root's right child
				add_right->data[0] = this->data[1];
				new_root->left() = add_left;
				new_root->right() = add_right;
			}
			//if to_add->data[1] is larger than this->data[0]...
			else if(this->data[0] <= to_add.data[1])
			{
				//...and to_add->data[1] is smaller than this->data[1]
				if(this->data[1] > to_add.data[1])
				{
					//but to_add->data[0] is smaller than this->data[0]
					if(this->data[0] > to_add.data[0])
					{
						//this's first data is root's first data
						//to_add's second data is root's second data
						new_root->data[0] = this->data[0];
						new_root->data[1] = to_add.data[1];
						//to_add's first data is root's left child
						add_left->data[0] = to_add.data[0];
						//this's second data is root's right child
						add_right->data[0] = this->data[1];
						new_root->left() = add_left;
						new_root->right() = add_right;
					}
					//but to_add->data[0] is larger than this->data[0]
					else
					{
						//to_add's data is root
						new_root->data[0] = to_add.data[0];
						new_root->data[1] = to_add.data[1];
						//this' first data is root's left child
						add_left->data[0] = this->data[0];
						//this's second data is root's right child
						add_right->data[0] = this->data[1];
						new_root->left() = add_left;
						new_root->right() = add_right;
					}
				}
				//...and to_add->data[1] is larger than this->data[1]
				else
				{
					//and to_add->data[0] is smaller than this->data[0]
					if(this->data[1] > to_add.data[0])
					{
						//to_add's first data is root's left child
						add_left->data[0] = to_add.data[0];
						//to_add's second data is root's right child
						add_right->data[0] = to_add.data[1];
						this->left() = add_left;
						this->right() = add_right;
					}
					//or to_add->data[0] is larger than this->data[0]
					else
					{
						//to_add's first data is root's first data
						new_root->data[0] = to_add.data[0];
						//this's second data is root's second data
						new_root->data[1] = this->data[1];
						//this' first data is root's left child
						add_left->data[0] = this->data[0];
						//to_add's first data is root's right child
						add_right->data[0] = to_add.data[1];
						new_root->left() = add_left;
						new_root->right() = add_right;
					}
				}

			}
			//if to_add->data[0] is larger than this->data[1]
			else
			{
				//root's first child is this' second and to_add's first children
				new_root->data[0] = this->data[1];
				new_root->data[1] = to_add.data[0];
				//this' first data is root's left child
				add_left->data[0] = this->data[0];
				//to_add's second child is root's right child
				add_right->data[0] = to_add.data[1];
				new_root->left() = add_left;
				new_root->right() = add_right;
			}
		}
	}
	else
	{
		delete new_root;
		delete add_left;
		delete add_right;
	}
	return *this;
}

//Overloads the < operator for a node class object
bool node::operator < (const node & to_compare)
{	
	return (*this->data < *to_compare.data);
}

//Overloads the < operator for a chest class object
bool node::operator < (const chest & to_compare)
{	
	return (*this->data < to_compare);
}

//Overloads the > operator for a node class object
bool node::operator > (const node & to_compare)
{
	return (*this->data > *to_compare.data);
}

//Overloads the > operator for a chest class object
bool node::operator > (const chest & to_compare)
{
	return (*this->data > to_compare);
}

//Overloads the <= operator for a node class object
bool node::operator <= (const node & to_compare)
{
	return (*this->data <= *to_compare.data);
}

//Overloads the <= operator for a chest class object
bool node::operator <= (const chest & to_compare)
{
	return (*this->data <= to_compare);
}

//Overloads the >= operator for a node class object
bool node::operator >= (const node & to_compare)
{
	return (*this->data >= *to_compare.data);
}

//Overloads the >= operator for a chest class object
bool node::operator >= (const chest & to_compare)
{
	return (*this->data >= to_compare);
}

//Overloads the == operator for a node class object
bool node::operator == (const node & to_compare) const
{
	return (*this->data == *to_compare.data);
}

//Overloads the == operator for a chest class object
bool node::operator == (const chest & to_compare) const
{
	return (*this->data == to_compare);
}

//Overloads the != operator for a node class object
bool node::operator != (const node & to_compare)
{
	return (*this->data != *to_compare.data);
}

//Overloads the != operator for a chest class object
bool node::operator != (const chest & to_compare)
{
	return (*this->data != to_compare);
}

//Overloads the = operator for a node class object
node & node::operator = (const node & add)
{
	if(this == &add)
		return *this;
	for(int i = 0; i < 2; ++i)
		data[i] = add.data[i];
	for(int j = 0; j < 3; ++j)
		child[j] = add.child[j];

	return *this;
}

//Overloads the << operator for a node class object
ostream & operator << (ostream & out, const node & display)
{
	out << static_cast<const chest&>(display);
	for(int i = 0; i < 2; ++i)
		out << "\t\t" << display.data[i] << endl;
	return out;
}

//Tree class member function implementations
//
//Default constructor
tree::tree(): root(NULL) {}

//Copy constructor
tree::tree(const tree & to_copy):
  node(to_copy), root(NULL), balance_factor(0) 
{
	if(!root)
	{
		root = new node;
		root = to_copy.root;
	}
}

//Copy constructor
tree::~tree()
{
	if(root)
	{
		delete root;
		root = NULL;
	}
}

//Creates a new tree
void tree::new_tree(const chest & to_add)
{
	static_cast<node&>(*root) += to_add;
}

//Functions for Operator Overloading
//Overloads the + operator
tree tree::operator + (const node & to_add) const
{
}

//Overloads the += operator
tree & tree::operator += (const node & to_add)
{
	if(to_add == NULL) return *this;
	if(!this->root)
	{
		*this->root = to_add;
		root->left() = root->middle() = root->right() = NULL;
	}
	else if(this->root->is_leaf())
		*this->root += to_add;
	else if(this->root->two_node())
	{
		if(*this->root > to_add)
			*this->root->left() += to_add;
		if(*this->root <= to_add)
			*this->root->right() += to_add;
	}
	else
	{
		if(*this->root > to_add)
			*this->root->left() += to_add;
		if(*this->root <= to_add)
		{
			if(*this->root->middle() <= to_add)
				*this->root->right() += to_add;
			else
				*this->root->middle() += to_add;
		}
	}
	return *this;
}

//Overloads the = operator
tree & tree::operator = (const tree & to_copy)
{
	if(this == &to_copy) 
		return *this;
	if(root)
		remove_all(root);
	root = new node;
	if(!to_copy.root)
		root = NULL;
	else
	{
		node * dest = root;
		node * source = to_copy.root;
		while(source)
		{
			traverse(source);
			if(source->is_leaf())
				dest = source;
			if(source->two_node())
			{	
				dest->left() = source->left();
				dest->right() = source->right();
			}
			else
			{
				dest->left() = source->left();
				dest->middle() = source->middle();
				dest->right() = source->right();
			}
		}
	}

	return *this;
}

//Overloads the < operator
bool tree::operator < (const tree & to_compare)
{
	return (this->root < to_compare.root);
}

//Overloads the < operator
bool tree::operator < (const node & to_compare)
{
	return (*this->root < to_compare);
}

//Overloads the > operator
bool tree::operator > (const tree & to_compare)
{
	return (this->root > to_compare.root);
}

//Overloads the > operator
bool tree::operator > (const node & to_compare)
{
	return (*this->root > to_compare);
}

//Overloads the <= operator
bool tree::operator <= (const tree & to_compare)
{
	return (this->root <= to_compare.root);
}

//Overloads the <= operator
bool tree::operator <= (const node & to_compare)
{
	return (*this->root <= to_compare);
}

//Overloads the >= operator
bool tree::operator >= (const tree & to_compare)
{
	return (this->root >= to_compare.root);
}

//Overloads the >= operator
bool tree::operator >= (const node & to_compare)
{
	return (*this->root >= to_compare);
}

//Overloads the == operator
bool tree::operator == (const tree & to_compare) const
{
	return (this->root == to_compare.root);
}

//Overloads the == operator
bool tree::operator == (const node & to_compare) const
{
	return (*this->root == to_compare);
}

//Overloads the != operator
bool tree::operator != (const tree & to_compare)
{
	return (this->root != to_compare.root);
}

//Overloads the != operator
bool tree::operator != (const node & to_compare)
{
	return (*this->root != to_compare);
}

//Overloads the << operator
ostream & operator << (ostream & out, const tree & display)
{
	// out << static_cast<const node&>(*display.root);
	out << display.name;
	out << display.email;
	return out;
}

//Overloads the >> operator
istream & operator >> (istream & in, const tree & input)
{
	in >> input.name;
	in >> input.email;
	return in;
}

//Protected tree class member functions
//
//Function for 2-3 tree traversal
node *& tree::traverse(node *& root) const
{
	if(!root) return (root = NULL);
	if(root->is_leaf()) 
		return root;
	else if(root->two_node())
	{
		traverse(root->left());
		traverse(root->right());
	}
	else 
	{
		traverse(root->left());
		traverse(root->middle());
		traverse(root->right());
	}
}

//Removes all nodes in the 2-3 tree
void tree::remove_all(node * root)
{
	if(!root) return;
	if(root->is_leaf())
	{
		delete root;
		root = NULL;
	}
	else if(root->two_node())
	{
		remove_all(root->left());
		remove_all(root->right());
	}
	else
	{
		remove_all(root->left());
		remove_all(root->middle());
		remove_all(root->right());
	}
}
