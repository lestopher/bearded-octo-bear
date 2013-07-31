#ifndef NUMBER_NODE_H
#define NUMBER_NODE_H

class NumberNode {
  friend class AreaNode;
  
  private:
    int prefix;
    int suffix;
    NumberNode* next;

  // Do not modify anything above this line
  //------------------------------------------------------------------------

  // DO NOT make the phonebook class a friend class of this class

  // Add additional functions/variables here:
  public:
    int getPrefix();
    int getSuffix();

  private:
    NumberNode* prev;
};

#endif
