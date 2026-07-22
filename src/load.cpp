#include "load.h"
#include <QDebug>

Load::world Load::getWorldInformation()
{
    Load::world a_world_inf;

    QFile file(":/config/config/world.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open world.json:" << file.errorString();
        return a_world_inf;
    }

    QByteArray data = file.readAll();
    file.close();

    //json语法错误检查
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return a_world_inf;
    }

    QJsonObject root = doc.object();

    //地面组
    QJsonArray groundArray = root["ground"].toArray();
    for (const auto& val : groundArray) {
        QJsonObject ground = val.toObject();
        int x = ground["x"].toInt();
        int y = ground["y"].toInt();
        int w = ground["w"].toInt();
        int h = ground["h"].toInt();
        a_world_inf.grounds.push_back(QRect(x, y, w, h));
    }

    //玩家组
    QJsonArray playerArray = root["player"].toArray();
    for (const auto& val : playerArray) {
        QJsonObject player_obj = val.toObject();
        Load::PLAYER player;
        int x = player_obj["x"].toInt();
        int y = player_obj["y"].toInt();
        int w = player_obj["w"].toInt();
        int h = player_obj["h"].toInt();
        player.base_param.role_rect = QRect(x, y, w, h);
        player.base_param.max_jump = player_obj["max_jump"].toInt();
        player.base_param.hp = player_obj["hp"].toInt();

        a_world_inf.player.push_back(player);
    }
    
    //boss组
    QJsonArray bossrArray = root["boss"].toArray();
    for (const auto& val : bossrArray) {
        QJsonObject boss_obj = val.toObject();
        Load::BOSS boss;
        int x = boss_obj["x"].toInt();
        int y = boss_obj["y"].toInt();
        int w = boss_obj["w"].toInt();
        int h = boss_obj["h"].toInt();
        boss.base_param.role_rect = QRect(x, y, w, h);
        boss.base_param.max_jump = boss_obj["max_jump"].toInt();
        boss.base_param.hp = boss_obj["hp"].toInt();

        a_world_inf.boss.push_back(boss);
    }

    qDebug() << "Loaded" << a_world_inf.grounds.size() << "ground rects from JSON";
    return a_world_inf;
}