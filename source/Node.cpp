#include "Node.h";

Node::Node(int _x, int _y, float _g, Node * _parent) {
	x = _x;
	y = _y;
	g = _g;
	next = NULL;
	parent = _parent;
}

Node::~Node() {
}
