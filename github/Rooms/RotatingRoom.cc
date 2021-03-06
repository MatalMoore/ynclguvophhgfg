
#include "RotatingRoom.h"
#include "CorridorRoom.h"
#include "./../Globals.h"
#include "./../Characters.h"
#include <string>
#include <iostream>
using namespace std;

//------------------------------------------------------
// #RotatingRoom() (Constructor)
//------------------------------------------------------
RotatingRoom::RotatingRoom(int initialDirection, bool areOtherExitsVisible, bool isVisible, bool* whichExits, string description){
  int i;
  int exitDirection;

  m_roomType = ROTATING_ROOM;

  m_axisRoom = new CorridorRoom(initialDirection, isVisible);

  //This is to prevent m_axisRoom from having its own ID
  s_nextRoomID--;
  s_rooms[s_nextRoomID] = NULL;

  if(SHOW_MESSAGES){
    cerr << m_axisRoom->getName()
      << " is now ";
    m_axisRoom->setName(m_name + "_a");
    cerr << m_axisRoom->getName() << endl
      << endl;
  }
  else{
    m_axisRoom->setName(m_name + "_a");
  }

  m_areOtherExitsVisible = areOtherExitsVisible;
  m_visibility = isVisible;

  if(whichExits == NULL){
    m_whichExits = new bool[getMaxExits()];

    for(i=0; i<getMaxExits(); i++)
      m_whichExits[i] = false;
  }
  else{
    m_whichExits = whichExits;
  }

  m_exits = new RoomExit*[getMaxExits()];

  for(i=0; i<getMaxExits(); i++){
    if(exitExists(getRoomExitDirection(i))){
      m_exits[i] = new RoomExit();
    }
    else{
      m_exits[i] = NULL;
    }
  }

  m_title = "rotating room";
  m_descriptor = "a";

  if(description.empty()){
    m_description = "You are on an axis in a round room.";
  }
  else{
    m_description = description;
  }
}
//------------------------------------------------------
// #~RotatingRoom() (Destructor)
//------------------------------------------------------
RotatingRoom::~RotatingRoom(){
  delete m_axisRoom;
}

//------------------------------------------------------
// #setExit()
//------------------------------------------------------
void RotatingRoom::setExit(int whichDirection, RoomExit* roomExit){
  RoundRoom::setExit(whichDirection, roomExit);
  if(isDirectionOnAxis(whichDirection)){
    m_axisRoom->setExit(whichDirection, roomExit);
  }
}

//------------------------------------------------------
// #linkRooms()
//------------------------------------------------------
void RotatingRoom::linkRooms(int whichDirection, Room* room, RoomExit* roomExit, int toWhichDirection){
  RoundRoom::linkRooms(whichDirection, room, roomExit, toWhichDirection);
  if(isDirectionOnAxis(whichDirection)){
    m_axisRoom->setExit(whichDirection, getExit(whichDirection));
  }
}

//------------------------------------------------------
// #getAxisRoom()
//------------------------------------------------------
Room* RotatingRoom::getAxisRoom() const{
  return m_axisRoom;
}
//------------------------------------------------------
// #isDirectionOnAxis()
//------------------------------------------------------
bool RotatingRoom::isDirectionOnAxis(int whichDirection) const{
  return m_axisRoom->isInputValid(whichDirection);
}
//------------------------------------------------------
// #isExitBlocked
//------------------------------------------------------
bool RotatingRoom::isExitBlocked(int whichDirection) const{
  if(!areOtherExitsVisible()){
    if(!isInputValid(whichDirection)){
      displayInvalidInput(whichDirection, "isExitBlocked");

      return false;
    }
    if(exitExists(whichDirection)){
      if(!isDirectionOnAxis(whichDirection)){
        return true;
      }
      else{
        return getExit(whichDirection)->isBlocked();
      }
    }
    else{
      return false;
    }
  }
  else{
    return RoundRoom::isExitBlocked(whichDirection);
  }

}
//------------------------------------------------------
// #isExitAccessible
//------------------------------------------------------
bool RotatingRoom::isExitAccessible(int whichDirection) const{
  if(!isInputValid(whichDirection)){
    displayInvalidInput(whichDirection, "isExitAccessible");

    return false;
  }
  if(exitExists(whichDirection)){
    return isDirectionOnAxis(whichDirection);
  }
  else{
    return false;
  }
}
//------------------------------------------------------
// #areThereNoAxisExits()
//------------------------------------------------------
bool RotatingRoom::areThereNoAxisExits() const{
  int maxExits = getAxisRoom()->getMaxExits(); 

  for(int i=0; i<maxExits; i++){
    if(exitExists(getAxisRoomExitDirection(i))){
      return false;
    }
  }

  return true;
}
//------------------------------------------------------
// #areAllAxisExitsHidden()
//------------------------------------------------------
bool RotatingRoom::areAllAxisExitsHidden() const{
  int maxExits = getAxisRoom()->getMaxExits(); 

  for(int i=0; i<maxExits; i++){
    if(!isExitHidden(getAxisRoomExitDirection(i))){
      return false;
    }
  }

  return true;
}
bool RotatingRoom::areOtherExitsVisible() const{
  return m_areOtherExitsVisible;
}

//------------------------------------------------------
// #rotate()
//------------------------------------------------------
void RotatingRoom::rotate(int interval){
  // This assumes the directions are in a clockwise
  //  order from 0 to DIRECTION_MAX

  int i;
  int newDirection;
  int axisRoomDirection = getAxisRoomExitDirection();
  int directionHold;
  bool isExitHiddenHold;
  bool isExitBlockedHold;
  Object* holdObject;
  RoomExit* roomExitHold = NULL;
  Room* roomHold = NULL;

  if(interval%2 != 0){
    cerr << m_name << " must be rotated by a multiple of 2 intervals";
    return;
  }

  newDirection = rotateDirection(axisRoomDirection, interval);

  if(newDirection == axisRoomDirection){
    return;
  }

  m_axisRoom->setDirection(newDirection);

  for(i=0; i<2; i++){
    m_axisRoom->setExit(newDirection, getExit(newDirection));
    newDirection = oppositeDirection(newDirection);
  }

  for(i=0; i<m_objectNext; i++){
    holdObject = m_objects[i];

    if(holdObject == NULL){
      continue;
    }

    if(m_areOtherExitsVisible){
      if(holdObject->getSubDescription() == FLOOR){
        holdObject->setPosition(rotateDirection(holdObject->getPosition(), interval));
      }
      else{
        continue;
      }
    }
    else{
        holdObject->setPosition(rotateDirection(holdObject->getPosition(), interval));
    }
  }

  if(Character::PLAYER->isCurrentRoom(this)){
    cout << "The room rotates with a rumble." << endl;
  }
}

//------------------------------------------------------
// #displayExits()
//------------------------------------------------------
void RotatingRoom::displayExits(std::ostream& o) const{
  int stringCount = 0;

  if(RoundRoom::areAllExitsHidden()
      || RoundRoom::areThereNoExits()
    ){
    return;
  }
  else{
    string* exitStrings = new string[getMaxExits()];

    for(int i=0; i<getMaxExits(); i++){
      if(!isDirectionOnAxis(getRoomExitDirection(i))
          && exitExists(getRoomExitDirection(i))
          && !isExitHidden(getRoomExitDirection(i))
        ){
        exitStrings[stringCount]
          = compassDirectionToString(getRoomExitDirection(i));
        stringCount++;
      }
    }
    if(stringCount > 0){
      o << "\n"
        << "\nObvious inaccessible exits are: ";
    }

    o << stringsToSequence(exitStrings, stringCount);

    for(int i=0; i<getMaxExits(); i++){
      if(!isDirectionOnAxis(getRoomExitDirection(i))
          && exitExists(getRoomExitDirection(i))
          && isExitBlocked(getRoomExitDirection(i))
        ){
        o << "\nThe "
          << compassDirectionToString(getRoomExitDirection(i))
          << " exit is blocked.";
      }
    }
  }

  return;
}
//------------------------------------------------------
// #display
//------------------------------------------------------
void RotatingRoom::display(std::ostream& o) const{
  int axisDirection0 = getAxisRoomExitDirection(0);
  int axisDirection1 = getAxisRoomExitDirection(1);

  int minDirection = min(axisDirection0, axisDirection1);
  int maxDirection = max(axisDirection0, axisDirection1);

  if(m_areOtherExitsVisible){
    o << "\n";
    o << DISPLAY_LINE << "\n";
    o << getDescription() << "\n";
    o << "The axis runs "
      << compassDirectionToString(minDirection)
      << " to "
      << compassDirectionToString(maxDirection)
      << ".\n";
    o << "\n";
    if(m_objectCount > 0){
      displayObjects(o);
      o << "\n";
    }
    if(isVisible()
        &&(areAllAxisExitsHidden()
          || areThereNoAxisExits()
          )
      ){
      o << "There are no obvious accessible exits.";
    }
    else{
      m_axisRoom->displayExits(o);
      displayExits(o);
    }
    o << "\n";
    o << DISPLAY_LINE;
  }
  else{
    o << "\n";
    o << DISPLAY_LINE << "\n";
    o << m_axisRoom->getDescription() << "\n";
    o << "\n";
    if(m_objectCount > 0){
      displayObjects(o);
      o << "\n";
    }
    m_axisRoom->displayExits(o);
    o << "\n";
    o << DISPLAY_LINE;
  }
}

//------------------------------------------------------
// #activate
//------------------------------------------------------
bool RotatingRoom::activate(int action, int state, int direction, Object* target, int extra){
  switch(action){
    case ROTATE:
      rotate(state);
      return true;

    case ROTATE_SET:
      if(isInputValid(direction)){
        rotate(direction - getAxisRoomExitDirection());
        return true;
      }
      else{
        return false;
      }

    default:
      return RoundRoom::activate(action, state, direction, target, extra);
  }
}

//------------------------------------------------------
// #getAxisRoomExitDirection()
//------------------------------------------------------
int RotatingRoom::getAxisRoomExitDirection(int whichExitIndex) const{
  return m_axisRoom->getRoomExitDirection(whichExitIndex);
}

