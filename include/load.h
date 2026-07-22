#ifndef LOAD_H
#define LOAD_H

#include <vector>
#include <QRect>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>

namespace Load{
    struct BASR_ROLE{
        QRect role_rect;
        int max_jump;
        int hp;
    };
    struct PLAYER{
        Load::BASR_ROLE base_param;
        
    };

    struct BOSS{
        Load::BASR_ROLE base_param;
    };

    struct world{
        std::vector<QRect> grounds;
        std::vector<Load::PLAYER> player;
        std::vector<Load::BOSS>   boss;
    };
    Load::world getWorldInformation();

};


#endif // LOAD_H