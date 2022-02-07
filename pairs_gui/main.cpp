/* Pairs - Animal Alphabet
 *
 * The program implements a memory game.
 *  At the beginning of the game the program asks for a number of pairs, number
 * of players and the names of the players.
 *  The game begins by pressing a start button which deals the cards face down
 * in random order and sets the first players turn. The program can be quit
 * using the close button.
 *  At each turn players click two cards on the screen which will be turned
 * visible. If a pair is found the player gets counted +1 pair and they can
 * continue. The pair is removed from the game board. The game also informs
 * which pair is found and how many pairs does the player have.
 *  If the two cards don't make a pair the cards are turned back face down and
 * the turn is set for the next player.
 *  The game continues for as long as there are cards on the game board. When
 * all the pairs are found the game informs about the winners and tells how
 * many cards they have. The game is also set up for the possible restart and
 * the start button activates as a restart button.
 *  The game can be played with the given parameters for as many rounds as
 * players want but the card amount, the player amount or the player names
 * cannot be changed.
 *
 * The game includes pictures taken from the internet with a permission to use.
 * Credit:
 * <a href="https://www.freepik.com/vectors/design">Design vector created by
 * pikisuperstar - www.freepik.com</a>
 */

#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
