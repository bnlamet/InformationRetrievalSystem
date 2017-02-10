#ifndef NODE_HPP_
#define NODE_HPP_

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <list>

struct Node {
    
	std::list<Node*> neighboors;
	std::string data;
	std::string color;
	Node(std::string s);
	~Node();
	
};
#endif /* NODE_HPP_ */