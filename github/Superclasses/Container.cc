
#include "Container.h"
#include <string>
using namespace std;

//------------------------------------------------------
// #Container (Constructor)
//------------------------------------------------------
Container::Container(string name, string description){
  m_objects = NULL;

  m_name = name;
  m_description = description;
}

//------------------------------------------------------
// #~Container (Destructor)
//------------------------------------------------------
Container::~Container(){
  if(m_objects != NULL){
    delete[] m_objects;
  }
}
