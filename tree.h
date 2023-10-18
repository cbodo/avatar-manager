//Craig Bodo, CS 202, May 2018
//This file defines the 2-3 tree data structure and the Node and Tree
//class interfaces.
//Node class is derived from node. Tree is derived from Node.
#include "avatar.h"

class node: public chest
{
  public:
    node();
	  node(node data[2], node * child[3]);
    node(const chest &);
    node(const node &);
    ~node();
    node & insert_achievement(const chest &);
    bool has_none();
    bool has_one();
    bool has_two();
    bool is_leaf();
    bool two_node();
    bool three_node();
    node *& left();
    node *& middle();
    node *& right();
    node operator + (const chest &) const;
    node & operator += (const chest &);
    node & operator += (const node & to_add);
    bool operator < (const node &);
    bool operator < (const chest &);
    bool operator > (const node &);
    bool operator > (const chest &);
    bool operator <= (const node &);
    bool operator <= (const chest &);
    bool operator >= (const node &);
    bool operator >= (const chest &);
    bool operator == (const node &) const;
    bool operator == (const chest &) const;
    bool operator != (const node &);
    bool operator != (const chest &);
    node & operator = (const node &);	
	  friend ostream & operator << (ostream &, const node &);
  protected:
    chest data[2];
    node * child[3];
};

class tree: public node
{
  public:
    tree();
    tree(const tree &);
    ~tree();
	  void new_tree(const chest &);
    //Functions for Operator Overloading
    tree operator + (const node &) const;
    tree & operator += (const node &);
    tree & operator = (const tree &);
    bool operator < (const tree &);
    bool operator < (const node &);
    bool operator > (const tree &);
    bool operator > (const node &);
    bool operator <= (const tree &);
    bool operator <= (const node &);
    bool operator >= (const tree &);
    bool operator >= (const node &);
    bool operator == (const tree &) const;
    bool operator == (const node &) const;
    bool operator != (const tree &);
    bool operator != (const node &);
    friend ostream & operator << (ostream &, const tree &);
    friend istream & operator >> (istream &, const tree &);
  protected:
	  void copy_tree(node *, const node *& root);
	  node *& traverse(node *& root) const;
    void remove_all(node * root);
    node * root;
    int balance_factor;
};
