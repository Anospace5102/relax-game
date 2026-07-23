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
        double hp;
        double basic_damage;
    };
    struct PLAYER{
        Load::BASR_ROLE base_param;
        
    };

    struct BOSS{
        Load::BASR_ROLE base_param;
    };
    struct BULLET{
        int type_id;
        QString shape;
        double radius;
        double velocity;
    };

    struct world{
        std::vector<QRect> grounds;
        std::vector<Load::PLAYER> player;
        std::vector<Load::BOSS>   boss;
        std::vector<Load::BULLET> bullets;
    };
    Load::world getWorldInformation();

};


#endif // LOAD_H