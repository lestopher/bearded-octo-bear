#ifndef AREA_NODE_H
#define AREA_NODE_H

#include "number_node.h"
#include <vector>

class AreaNode
{
  friend class PhoneBook;

  private:
    int areaCode;
    AreaNode* next;
    NumberNode* head;

  public:
    void print ();
    int size ();

  // Do not modify anything above this line
  //------------------------------------------------------------------------

  // Add additional functions/variables here:

  private:
    int _size;
    AreaNode* prev;

  public:
    AreaNode(int);
    AreaNode* getMatchingAreaNode(int);
    NumberNode* getMatchingNumber(int, int);
    std::vector<NumberNode*> disconnectNumberNodes(int);
    void connectNumberNodes(std::vector<NumberNode*>);
    int countPrefix(int);
    void addAreaCode(int);
    void addNumber(int, int);
    void removeNumber(int, int);
    void removeAreaCode();
};

#endif
