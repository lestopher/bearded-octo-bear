#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "phone_book.h"

using namespace std;

//------------------------------------------------------------------------
// Constructor sets head to NULL value
PhoneBook::PhoneBook ()
{
  head = NULL;
  tail = NULL;
}


//-------------------------------------------------------------------------

void
PhoneBook::readFromFile (string fileName)
{
  char* cstr;
  char* s;
  ifstream infile ;
  int area;
  int count = 0;
  int prefix;
  int suffix;
  string line;

  infile.open(fileName.c_str()); 

  while (!infile.eof())
  {
    infile >> line;
    
    cstr = new char [line.length() + 1];
    strcpy(cstr, line.c_str());

    s = strtok(cstr, "-");

    while (s != NULL)
    {
      if (count%3 == 0)
        area = atoi(s);
      else if (count%3 == 1)
        prefix = atoi(s);
      else if (count%3 == 2)
        suffix = atoi(s);

      s  = strtok(NULL, "-");
      count++;
    } 

    this->insertPhoneNumber(area, prefix, suffix);
  }

  delete[] cstr;
}

//-------------------------------------------------------------------------

void
PhoneBook::removePhoneNumber (int area, int prefix, int suffix)
{
  AreaNode* areaCodePtr = this->head->getMatchingAreaNode(area);

  if (areaCodePtr != NULL)
  {
    if (areaCodePtr->getMatchingNumber(prefix, suffix))
    {
      areaCodePtr->removeNumber(prefix, suffix);
      if (areaCodePtr->size() == 0)
      {
        if (this->head == areaCodePtr && areaCodePtr->next != NULL)
          this->head = areaCodePtr->next;

        areaCodePtr->removeAreaCode();
      }
    }
  }
  else
    cout << "No such number exists.\n";
}

//-------------------------------------------------------------------------

void
PhoneBook::insertPhoneNumber (int area, int prefix, int suffix)
{
  if (this->head == NULL)
  {
    this->head = new AreaNode(area);
    this->head->next = NULL;
    this->head->prev = NULL;
    this->tail = this->head;
    this->head->addNumber(prefix, suffix);
    return;
  }
  else
  {
    AreaNode* areaCodePtr = this->head->getMatchingAreaNode(area);

    // No such areacode exists, we need to add a new area node
    if (areaCodePtr == NULL) 
    {
      AreaNode* newAreaCode = new AreaNode(area);
      newAreaCode->next = this->head;
      this->head->prev = newAreaCode;
      this->head = newAreaCode;
      areaCodePtr = newAreaCode;
    }

    // Number already exists
    if (areaCodePtr->getMatchingNumber(prefix, suffix) != NULL)
    {
      printf("The number (%i) %i-%i already exists\n", area, prefix, suffix);
    }
    else
    {
      areaCodePtr->addNumber(prefix, suffix);
    }
  }
}

//-------------------------------------------------------------------------

bool
PhoneBook::search (int area, int prefix, int suffix)
{
  AreaNode* areaCodePtr = this->head->getMatchingAreaNode(area);

  if (areaCodePtr == NULL)
    return false;

  return areaCodePtr->getMatchingNumber(prefix, suffix) == NULL ? false : true;
}

//-------------------------------------------------------------------------
// DO NOT MODIFY THIS PRINT FUNCTION

void
PhoneBook::print ( ) {

  if ( head == NULL ) {
    cout << "Phonebook is empty" << endl;
  }
  else {
    for ( AreaNode* temp = head; temp != NULL; temp = temp->next ) {
      cout << "( " << temp->areaCode << " )" << endl;
      temp->print ( );
    }
  }

}

//-------------------------------------------------------------------------

int 
PhoneBook::numNumbers ()
{
  int total = 0;
  AreaNode* areaCodePtr = this->head;

  while (areaCodePtr != NULL)
  {
    total += areaCodePtr->size();
    areaCodePtr = areaCodePtr->next;
  }

  return total;
}

//-------------------------------------------------------------------------

int
PhoneBook::numAreaCodeNumbers (int area)
{
  AreaNode* areaCodePtr = this->head; 

  if (areaCodePtr == NULL)
    return 0;

  while (areaCodePtr->areaCode != area)
    areaCodePtr = areaCodePtr->next;

  return areaCodePtr->size();
}

//-------------------------------------------------------------------------

int
PhoneBook::numAreaCodeAndPrefixNumbers (int area , int prefix)
{
  AreaNode* an = this->head->getMatchingAreaNode(area);
  if (an != NULL)
    return an->countPrefix(prefix);
  else
    return 0;
}

//-------------------------------------------------------------------------

void
PhoneBook::split (int oldAreaCode, int prefix, int newAreaCode)
{
  AreaNode* areaCodePtr = this->head->getMatchingAreaNode(oldAreaCode);

  if (areaCodePtr != NULL)
  {
    std::vector<NumberNode*> v = areaCodePtr->disconnectNumberNodes(prefix);

    if (areaCodePtr->size() == 0)
    {
      if (this->head == areaCodePtr && areaCodePtr->next != NULL)
        this->head = areaCodePtr->next;

      if (areaCodePtr->prev != NULL)
        areaCodePtr->prev->next = areaCodePtr->next;

      if (areaCodePtr->next != NULL)
        areaCodePtr->next->prev = areaCodePtr->prev;

      areaCodePtr->removeAreaCode();
    }

    areaCodePtr = this->head->getMatchingAreaNode(newAreaCode);

    if (areaCodePtr == NULL)
    {
      areaCodePtr = new AreaNode(newAreaCode);
      areaCodePtr->next = this->head;
      this->head->prev = areaCodePtr;
      this->head = areaCodePtr;
    }

    areaCodePtr->connectNumberNodes(v);
  }
}

//-------------------------------------------------------------------------
