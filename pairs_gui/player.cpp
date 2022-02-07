#include "player.hh"

Player::Player(const QString& name):
    name_(name)
{

}

QString Player::get_name()
{
    return name_;
}

void Player::add_pair(const QChar& letter)
{
    pairs_.push_back(letter);
}

int Player::get_pair_amount()
{
    return pairs_.size();
}

void Player::set_default()
{
    pairs_.clear();
}

