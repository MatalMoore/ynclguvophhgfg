
#ifndef CORRIDORROOM_H
#define CORRIDORROOM_H

#include "Room.h"
#include "./../Globals.h"
#include <iostream>
#include <string>

class CorridorRoom: public Room{
  public:
    CorridorRoom(const int initialDirection=N, const bool isVisible=true, bool* whichExits=NULL, const std::string description="");
    ~CorridorRoom();

    void setDirection(const int whichDirection);
    int getDirection() const;

    virtual int directionToIndex(const int whichDirection) const;
    
    virtual int getRoomExitDirection(const int whichExitIndex=0) const{
      if(whichExitIndex == 0){
        return m_direction;
      }
      else{
        return oppositeDirection(m_direction);
      }
    }

  protected:
    int m_direction;
};

#endif
