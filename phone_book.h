#ifndef PHONE_BOOK_H
#define PHONE_BOOK_H

#include "area_node.h"

class PhoneBook
{
  private:
    AreaNode* head;
   
  public:
    PhoneBook();
    void insertPhoneNumber (int, int, int);
    void removePhoneNumber (int, int, int);
    bool search (int, int, int);
    void print ();
    int numNumbers ();
    int numAreaCodeNumbers (int);
    int numAreaCodeAndPrefixNumbers (int, int);
    void readFromFile (std::string);
    void split (int, int, int);

  // Do not modify anything above this line
  //------------------------------------------------------------------------

  // Add additional functions/variables here:

    AreaNode* tail;
};

#endif
