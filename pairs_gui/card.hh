/* Class Card
 * Implements a card for the pairs game.
 */

#ifndef CARD_HH
#define CARD_HH

#include <QChar>
#include <QPushButton>

class Card
{
public:
    Card(QChar& letter, QPushButton* button);

    QChar get_letter();
    QPushButton* get_button();
    void set_hidden();
    bool is_hidden();

private:
    QChar letter_;
    QPushButton* button_;
    bool is_hidden_ = true;
};

#endif // CARD_HH
