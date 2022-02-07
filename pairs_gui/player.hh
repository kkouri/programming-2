/* Class Player
 * Implements a player for the pairs game.
 */

#ifndef PLAYER_HH
#define PLAYER_HH

#include "card.hh"
#include <QString>
#include <vector>


class Player
{
public:
    Player(const QString& name);

    QString get_name();
    void add_pair(const QChar& letter);
    int get_pair_amount();
    void set_default();


private:
    QString name_;
    std::vector<QChar> pairs_;
};

#endif // PLAYER_HH
