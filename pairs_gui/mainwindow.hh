#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "player.hh"
#include "card.hh"

#include <QMainWindow>
#include <QString>
#include <QTextBrowser>
#include <QLineEdit>
#include <QPushButton>
#include <vector>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    // Tool functions
    void set_restart();
    void delete_players();
    void delete_cards();

    // Init functions
    void init_info_text_browser();
    void init_player_line_edit();
    void init_start_button();
    void init_close_button();
    void init_cards();

    // Helper functions
    QString set_random_order();
    int calculate_columns();
    void set_number_of_pairs();
    void set_number_of_players();
    void add_player();

    // Info functions
    void print_info(const QString& text);
    void print_turn();
    void print_winners();

    // Widget signal functions
    void handle_player_line_edit();
    void handle_start_push_button();
    void handle_close_push_button();
    void handle_card_button_click();

    // Animation functions
    void turn_hidden();
    void disable_all_cards();
    void remove_cards();

    // Game functions
    void play_turn();
    bool is_pairs();



private:
    Ui::MainWindow *ui;

    // Space between elements, both horizontally and vertically
    const int MARGIN = 10;

    // Constants for cards
    const int CARD_BUTTON_WIDTH = 75;
    const int CARD_BUTTON_HEIGHT = 105;

    // Standard height used in buttons and line edit
    const int STANDARD_HEIGHT = 30;

    // Constants for function buttons
    const int FUNCTION_BUTTON_WIDTH = 70;

    // Size of the text browser
    const int DISPLAY_WIDTH = 150;
    const int DISPLAY_HEIGHT = 90;

    // Delay for animations
    int DELAY = 2000;

    // Vital game info
    int number_of_players_;
    int number_of_pairs_;
    int pairs_found_ = 0;
    int input_counter_ = 0;

    std::vector<Card*> cards_;
    std::vector<Player*> players_;
    std::vector<Card*> turned_cards_;

    Player* player_in_turn_;
    bool cards_enabled_= true;

    // Widgets
    QTextBrowser* info_text_browser_;
    QLineEdit* player_line_edit_;
    QPushButton* start_push_button_;
    QPushButton* close_push_button_;



    // Animals
    std::map<QChar, QString> animals_ = {{'A',"alligator"},
                                         {'B',"bird"},
                                         {'C',"caterpillar"},
                                         {'D',"dog"},
                                         {'E',"elephant"},
                                         {'F',"flamingo"},
                                         {'G',"giraffe"},
                                         {'H',"horse"},
                                         {'I',"iguana"},
                                         {'J',"jellyfish"},
                                         {'K',"kangaroo"},
                                         {'L',"lion"},
                                         {'M',"monkey"},
                                         {'N',"narwhal"},
                                         {'O',"owl"},
                                         {'P',"penguin"},
                                         {'Q',"quail"},
                                         {'R',"rabbit"},
                                         {'S',"snake"},
                                         {'T',"tiger"},
                                         {'U',"urraca"},
                                         {'V',"vampire bat"},
                                         {'W',"worm"},
                                         {'X',"xeruz"},
                                         {'Y',"yak"},
                                         {'Z',"zebra"},
                                         };
};
#endif // MAINWINDOW_HH
