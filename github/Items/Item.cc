
#include "./../Globals.h"
#include "Item.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

unsigned int Item::s_nextItemID;
unsigned int Item::s_itemCount = 0;
unsigned int Item::s_itemMax;
Item** Item::s_items;

//------------------------------------------------------
// #Item (Constructor)
//------------------------------------------------------
Item::Item(bool isObtainable, bool isObtained, std::string description){
  if(s_itemCount == 0){
    s_nextItemID = 0;
    s_itemMax = 100;
    s_items = new Item*[s_itemMax];
    if(SHOW_MESSAGES){
      cerr << "s_items: Allocated" << endl
        << endl;
    }
  }

  s_itemCount++;

  m_type = ITEM;

  m_itemType = ITEM;

  stringstream charsOfID;

  charsOfID.width(4);
  charsOfID.fill('0');

  m_itemID = s_nextItemID++;
  if(m_itemID >= s_itemMax){
    Item** itemsHold = new Item*[s_itemMax*2];
    for(int i=0; i<s_itemMax; i++){
      itemsHold[i] = s_items[i];
      itemsHold[s_itemMax+i] = NULL;
      s_items[i] = NULL;
    }
    delete[] s_items;
    s_items = itemsHold;
    s_itemMax *= 2;
  }
  s_items[m_itemID] = this;

  charsOfID << m_itemID;
  charsOfID >> m_name;

  m_name.insert(0, "Item");

  if(SHOW_MESSAGES){
    cerr << m_name << ": Creating" << endl;
  }

  m_isObtainable = isObtainable;
  m_isObtained = false;

  if(SHOW_MESSAGES){
    cerr << m_name << ": Created" << endl
      << endl;
  }
}
//------------------------------------------------------
// #~Item (Destructor)
//------------------------------------------------------
Item::~Item(){
  if(SHOW_MESSAGES){
    cerr << m_name << ": Deleting -" << getItemType() << "-" << endl;
  }

  s_items[m_itemID] = NULL;

  s_itemCount--;

  if(SHOW_MESSAGES){
    cerr << m_name << ": Deleted" << endl
      << endl;
  }

  if(s_itemCount == 0){
    delete[] s_items;
    if(SHOW_MESSAGES){
      cerr << "s_items: Deallocated" << endl
        << endl;
    }
  }
}

//------------------------------------------------------
// #setObtainable
//------------------------------------------------------
void Item::setObtainable(bool boolean){
  m_isObtainable = boolean;
}
//------------------------------------------------------
// #setObtained
//------------------------------------------------------
void Item::setObtained(bool boolean){
  m_isObtained = boolean;
}

//------------------------------------------------------
// #isObtainable
//------------------------------------------------------
bool Item::isObtainable() const{
  return m_isObtainable;
}
//------------------------------------------------------
// #isObtained
//------------------------------------------------------
bool Item::isObtained() const{
  return m_isObtained;
}

//------------------------------------------------------
// #getItemType
//------------------------------------------------------
string Item::getItemType() const{
  return m_itemType;
}

//------------------------------------------------------
// #activate
//------------------------------------------------------
bool Item::activate(int action, int state, int direction, Object* target, int extra){
  switch(action){
    case OBTAINABLE_SET:
      setObtainable(state);
      return true;

    case OBTAIN_SET:
      setObtained(state);
      return true;

    case OBTAINABLE_TOGGLE:
      setObtainable(!isObtainable());
      return true;

    case OBTAIN_TOGGLE:
      setObtained(!isObtained());
      return true;

    default:
      return Container::activate(action, state, direction, target, extra);
  }
}
