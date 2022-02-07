#include "card.hh"

Card::Card(QChar& letter, QPushButton* button):
    letter_(letter), button_(button)
{

}

QChar Card::get_letter()
{
    return letter_;
}

QPushButton *Card::get_button()
{
    return button_;
}

void Card::set_hidden()
{
    is_hidden_ = !is_hidden_;
}

bool Card::is_hidden()
{
    return is_hidden_;
}


