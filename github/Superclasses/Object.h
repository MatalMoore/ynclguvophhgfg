
#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Object{
  public:
    Object(std::string name="", std::string description="");
    ~Object(){}

    void setName(std::string description);
    void setDescription(std::string description);

    std::string getName() const;
    std::string getDescription() const;

    virtual bool activate(int arg0=0, int arg1=0, int arg2=0, Object* argObj=NULL);

  protected:
    std::string m_name;
    std::string m_description;
};

#endif