#ifndef _BOSS_H
#define _BOSS_H
#include "base_role.h"
#include "load.h"
class Boss: public BaseRole{
public:
    Boss(Load::BOSS& w);

public:
    void update(double fixed_step) override;   //boss自身逻辑更新


public:
    int hp() const;
    void change_hp(int hp);
private:
    int hp_;

};


#endif //_BOSS_H