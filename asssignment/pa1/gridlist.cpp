// File:        gridlist.cpp
// Date:        2020-01-18 00:11
// Description: Contains partial implementation of GridList class
//              CPSC 221 2019W2 PA1
//              Function bodies to be completed by yourselves
//
// ADD YOUR FUNCTION IMPLEMENTATIONS IN THIS FILE
//

#include "gridlist.h"
#include "gridlist_given.cpp"
#include <stdbool.h>

// Creates a PNG of appropriate pixel dimensions according to the GridList's structure
//   and colours each pixel according the each GridNode's Block data.
// The fully coloured PNG is returned.
PNG GridList::Render() const
{
  PNG image;
  GridNode* nodes = northwest;
  if (nodes != NULL) {
      image.resize(dimx * (nodes->data.Dimension()), dimy * (nodes->data.Dimension()));
  }
  int currx = 0;
  int curry = 0;
  int counter = 0;
  while (nodes != NULL)
  {
      counter++;
      nodes->data.Render(image, curry, currx);
      if (counter % dimx == 0) {
          currx = 0;
          curry += nodes->data.Dimension();
      }
      else
      {
          currx += nodes->data.Dimension();
      }
      nodes = nodes->next;
  }
  return image;
}

// Allocates a new GridNode containing bdata and
//   attaches it to end of this list.
// Be careful of the special case of inserting into an empty list.
void GridList::InsertBack(const Block& bdata)
{
    GridNode* newNode = new GridNode();
    newNode->data = bdata;
    if(this->IsEmpty()) {
        southeast = newNode;
        northwest = newNode;
    }
    else
    {
        southeast->next = newNode;
        newNode->prev = southeast;
        southeast = southeast->next;
    }
}

// if this list has an odd number of column blocks, then the right side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two column blocks
//       inner list must have at least one column block
//       inner list must have the same vertical resolution, vertical block dimension, and block size
// POST: this list has nodes of the entire inner list in between the left and right halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_H(GridList& inner)
{
    if ((this != &inner) && (dimx >= 2) && (inner.dimx > 0) && (dimy == inner.dimy) && 
        (northwest->data.Dimension() == (inner.getNorthWest())->data.Dimension())) {
        int counter = 0;
        int xStart = dimx/2;
        bool even = (dimx % 2) == 0;
        GridNode* curr = northwest;
        dimx += inner.dimx;
        while (inner.northwest != NULL)
        {
            counter++;
            if (counter == xStart) {
                GridNode* next = curr->next;
                inner.northwest->prev = curr;
                curr->next = inner.northwest;
                for (int i = 0; i < inner.dimx ; i++) {
                    inner.northwest = inner.northwest->next;
                    curr = curr->next;
                }
                next->prev = curr;
                curr->next = next;

                counter = -xStart;
                if (!even) {
                    counter--;
                }
            }
            curr = curr->next;
        }

        inner.dimx = 0;
        inner.dimy = 0;
    }
    return;
}

// inner list must have the same horizontal resolution, horizontal block dimension, and block size
// if this list has an odd number of row blocks, then the bottom side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two row blocks
//       inner list must have at least one row block
//       inner list must have same horizontal resolution, horizontal block dimension, and block size
// POST: this list has nodes of the entire inner list in between the upper and lower halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_V(GridList& inner)
{
    if ((this != &inner) && (dimy >= 2) && (inner.dimy > 0) && (dimx == inner.dimx) &&
        (northwest->data.Dimension() == (inner.getNorthWest())->data.Dimension())) {
        int counter = 0;
        int xStart = (dimy / 2) * dimx;
        GridNode* curr = northwest;
        dimy += inner.dimy;
        while (inner.northwest != NULL)
        {
            counter++;
            if (counter == xStart) {
                GridNode* next = curr->next;
                inner.northwest->prev = curr;
                curr->next = inner.northwest;
                while (inner.northwest != NULL) {
                    inner.northwest = inner.northwest->next;
                    curr = curr->next;
                }
                next->prev = curr;
                curr->next = next;
            }
            curr = curr->next;
        }

        inner.dimx = 0;
        inner.dimy = 0;
    }
    return;
}


// PRE:  this list and otherlist have the same pixel dimensions, block dimensions, and block size
// POST: this list and otherlist are checkered with each other's nodes
//       each list's dimensions remain the same
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::CheckerSwap(GridList& otherlist)
{
    if (dimx != otherlist.dimx || dimy != otherlist.dimy) {
        return;
    }
    GridNode* curr1 = northwest;
    GridNode* curr2 = otherlist.northwest;
    bool change = false;
    bool even = (dimx % 2) == 0;
    int counter = 0;
    while (curr1->next != NULL) {
        counter++;
        if (change) {
            curr1->next->prev = curr2;
            curr2->next->prev = curr1;

            curr1->prev->next = curr2;
            curr2->prev->next = curr1;

            GridNode* temp = curr1->prev;
            curr1->prev = curr2->prev;
            curr2->prev = temp;

            temp = curr2->next;
            curr2->next = curr1->next;
            curr1->next = temp;

            change = false;
        }
        else {
            change = true;
        }
        if (even && ((counter) % dimx == 0)) {
            change = !change;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    if (even && change) {
        curr1->prev->next = curr2;
        curr2->prev->next = curr1;

        GridNode* temp = curr1->prev;
        curr1->prev = curr2->prev;
        curr2->prev = temp;
    }

}

// POST: this list has the negative effect applied selectively to GridNodes to form
//         a checkerboard pattern.
//       The northwest block is normal (does not have the negative effect applied).
// Ensure that the checkering looks correct for both odd and even horizontal block dimensions
void GridList::CheckerN()
{
    int counter = 1;
    int size = dimx * dimy;
    bool even = (dimx % 2) == 0;
    GridNode* curr = northwest;
    int change = 0;
    while (counter <= size) {
        if (counter % 2 == 0) {
            curr->data.Negative();
        }
        if ((counter - change) % dimx == 0) {
            if (even) {
                if (change) {
                    counter--;
                    change = 0;
                }
                else {
                    counter++;
                    change = 1;
                }
            }
        }
        curr = curr->next;
        counter++;
    }
}

// Deallocates any dynamic memory associated with this list
//   and re-initializes this list to an empty state
void GridList::Clear()
{
    GridNode* curr = northwest;
    while (curr != NULL) {
        GridNode* temp = curr;
        curr = curr->next;
        delete(temp);

    }
    northwest = NULL;
    southeast = NULL;
}

// Allocates new nodes into this list as copies of all nodes from otherlist
void GridList::Copy(const GridList& otherlist)
{
    GridNode* curr = otherlist.northwest;
    GridNode* newNodeF = new GridNode();
    newNodeF->data = curr->data;
    southeast = northwest = newNodeF;
    curr = curr->next;
    while (curr != NULL) {
        GridNode* newNode = new GridNode();
        newNode->data = curr->data;

        southeast->next = newNode;
        newNode->prev = southeast;
        southeast = newNode;

        curr = curr->next;
    }
}

// IMPLEMENT ANY PRIVATE FUNCTIONS YOU HAVE ADDED BELOW
//
////
//GridNode::~GridNode() {
//    this->next = NULL;
//    this->prev = NULL;
//    //delete(this);
//}