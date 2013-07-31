#include <iostream>
#include "area_node.h"

using namespace std;

#define NUM_TO_PRINT_PER_LINE 5

AreaNode::AreaNode (int area)
{
  _size = NULL;
  areaCode = area;
  next  = NULL;
  prev  = NULL;
  head  = NULL;
}
//-----------------------------------------------------------------------
// DO NOT MODIFY THIS PRINT FUNCTION

void
AreaNode::print ( ) {

  NumberNode* temp = head;
  for ( int x = 0; x < size ( ) && temp != NULL; 
        x += NUM_TO_PRINT_PER_LINE ) {
    cout << "       " << flush;
    for ( int y = 0; y < NUM_TO_PRINT_PER_LINE && temp != NULL; 
          y ++, temp = temp->next ) {
      cout << temp->prefix << "-" << flush << temp->suffix << ", " << flush;
    }
    cout << endl;
  }
}

//-----------------------------------------------------------------------

int
AreaNode::size () {
  NumberNode* temp_ptr = head;
  int count = 0;

  while (temp_ptr != NULL)
  {
    count++;
    temp_ptr = temp_ptr->next;
  }

  return count;
}

//-----------------------------------------------------------------------
void
AreaNode::addAreaCode (int area)
{
  // Find out if it exists first
  AreaNode* areaCodePtr = this->getMatchingAreaNode(area);

  if (areaCodePtr != NULL)
  {
    areaCodePtr = this;

    while (areaCodePtr->next != NULL)
      areaCodePtr = areaCodePtr->next;

    areaCodePtr->next = new AreaNode(area);
    areaCodePtr->next->prev = areaCodePtr;
  }
  else
  {
    cout << "Area code already exists. Nothing to be done\n";
  }

}

void
AreaNode::addNumber(int prefix, int suffix)
{
  NumberNode* newNumber = new NumberNode();
  newNumber->prefix = prefix;
  newNumber->suffix = suffix;

  if (this->head != NULL)
  {
    newNumber->next = this->head;
    this->head->prev = newNumber;
    this->head = newNumber;
    this->head->prev = NULL;
  }
  else
  {
    this->head = newNumber;
    this->head->prev = NULL;
  }
}

AreaNode*
AreaNode::getMatchingAreaNode (int area)
{
  AreaNode* areaNodePtr = this;

  while (areaNodePtr != NULL)
  {
    if (areaNodePtr->areaCode == area)
      break;
    else
      areaNodePtr = areaNodePtr->next;
  }

  return areaNodePtr;
}

NumberNode*
AreaNode::getMatchingNumber (int prefix, int suffix)
{
  NumberNode* numberNodePtr = this->head;

  while (numberNodePtr != NULL)
  {
    if (numberNodePtr->prefix == prefix && numberNodePtr->suffix == suffix)
      return numberNodePtr;
    else
      numberNodePtr = numberNodePtr->next;
  }

  return numberNodePtr;
}

void
AreaNode::removeNumber (int prefix, int suffix)
{
  NumberNode* numberNodePtr = this->getMatchingNumber(prefix, suffix);

  if (numberNodePtr != NULL)
  {
    // Don't break the linked lists...
    if (numberNodePtr->prev != NULL)
      numberNodePtr->prev->next = numberNodePtr->next;
    if (numberNodePtr->next != NULL)
      numberNodePtr->next->prev = numberNodePtr->prev;

    if (this->head == numberNodePtr && numberNodePtr->next != NULL)
    {
      this->head = numberNodePtr->next;
      this->head->prev = NULL;
    }
    else if (this->head == numberNodePtr)
    {
      this->head = NULL;
    }

    numberNodePtr->next = NULL;
    numberNodePtr->prev = NULL;
    delete numberNodePtr;
  }    
}

void
AreaNode::removeAreaCode()
{
  AreaNode* areaCodePtr = this;

  areaCodePtr->next = NULL;
  areaCodePtr->prev = NULL;
  delete areaCodePtr;
}

int 
AreaNode::countPrefix (int prefix)
{
  int count = 0;
  NumberNode* numberNodePtr = this->head;
  
  while (numberNodePtr != NULL)
  {
    if (numberNodePtr->prefix == prefix)
      count++;

    numberNodePtr = numberNodePtr->next;
  }

  return count;
}

std::vector<NumberNode*>
AreaNode::disconnectNumberNodes (int prefix)
{
  NumberNode* numberNodePtr = this->head;
  std::vector<NumberNode*> v;

  while (numberNodePtr != NULL)
  {
    if (numberNodePtr->prefix == prefix)
    {
      if (numberNodePtr->prev != NULL)
        numberNodePtr->prev->next = numberNodePtr->next;
      if (numberNodePtr->next != NULL)
        numberNodePtr->next->prev = numberNodePtr->prev;

      if (this->head == numberNodePtr)
      {
        this->head = numberNodePtr->next;
        if (this->head != NULL)
          this->head->prev = NULL;
      }

      v.push_back(numberNodePtr);
    }

    numberNodePtr = numberNodePtr->next;
  }

  return v;
}

void
AreaNode::connectNumberNodes (std::vector<NumberNode*> v)
{
  NumberNode* nodeToConnect;

  while (v.size() > 0)
  {
    nodeToConnect = v.back();
    nodeToConnect->next = NULL;
    nodeToConnect->prev = NULL;

    if (this->head != NULL)
    {
      nodeToConnect->next = this->head;
      this->head->prev = nodeToConnect;
    }

    this->head = nodeToConnect;
    this->head->prev = NULL;

    v.pop_back();
  }
}