
#ifndef ROTATINGROOM_H
#define ROTATINGROOM_H

#include "Room.h"
#include "RoundRoom.h"
#include "CorridorRoom.h"
#include "./../Globals.h"
#include <iostream>
#include <string>

class RotatingRoom: public RoundRoom{
  public:
    RotatingRoom(const int initialDirection=N, const bool areOtherExitsVisible=false, const bool isVisible=true, bool* whichExits=NULL, const std::string description="");
    ~RotatingRoom();

    virtual void setExit(const int whichDirection, RoomExit* roomExit);

    virtual void linkRooms(const int whichDirection, Room* room=NULL, RoomExit* roomExit=NULL, const int toWhichDirection=OPPOSITE);

    Room* getAxisRoom() const;
    bool isDirectionOnAxis(const int whichDirection) const;
    virtual bool isExitBlocked(const int whichDirection) const;
    virtual bool isExitAccessible(const int whichDirection) const;
    bool areThereNoAxisExits() const;
    bool areAllAxisExitsHidden() const;
    bool areOtherExitsVisible() const;

    void rotate(const int interval);

    virtual void displayExits(std::ostream& o) const;
    virtual void display(std::ostream& o) const;

    virtual bool activate(const int action=0, const int state=0, const int direction=0, Object* target=NULL, const int extra=0);

    int getAxisRoomExitDirection(const int whichExitIndex=0) const;

  protected:
    bool m_areOtherExitsVisible;
    CorridorRoom* m_axisRoom;
};

#endif
