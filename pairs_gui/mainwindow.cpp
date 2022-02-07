#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QValidator>
#include <QTime>
#include <QTimer>
#include <algorithm>
#include <random>

const QString START_SCREEN = "Pairs game\n\nEnter the amount of pairs "
                             "(3-26)";
const QString PLAYER_AMOUNT = "Enter the amount of players (1-4)";
const QString PLAYER_NAMES = "Enter player names separately";


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Pairs - Animal Alphabet");
    this->resize(400,300);
    init_info_text_browser();
    init_player_line_edit();
}

MainWindow::~MainWindow()
{
    delete_players();
    delete_cards();
    delete ui;
}

// Restores game to a beginning  state
void MainWindow::set_restart()
{
    delete_cards();

    input_counter_ = 0;
    pairs_found_ = 0;
    player_in_turn_ = players_.at(0);

    for (Player* player : players_)
    {
        player->set_default();
    }
    start_push_button_->setStyleSheet("QPushButton {background-color:rgb(130,180,110); color: white;}");
    start_push_button_->setText("Restart");
    start_push_button_->setEnabled(true);
}

void MainWindow::delete_players()
{
    for (Player* player_to_be_deleted : players_)
    {
        delete player_to_be_deleted;
    }
}

void MainWindow::delete_cards()
{
    if (cards_.empty())
    {
        return;
    }
    for (Card* card_to_be_deleted : cards_)
    {
        delete card_to_be_deleted;
    }
    cards_.clear();
}

// Inits the info display
void MainWindow::init_info_text_browser()
{
    info_text_browser_ = new QTextBrowser(this);
    info_text_browser_->setGeometry(MARGIN, MARGIN, DISPLAY_WIDTH,
                                    DISPLAY_HEIGHT);
    info_text_browser_->setText(START_SCREEN);
}

// Inits input line edit
void MainWindow::init_player_line_edit()
{
    player_line_edit_ = new QLineEdit(this);
    player_line_edit_->setGeometry(MARGIN, MARGIN + MARGIN + DISPLAY_HEIGHT,
                                   DISPLAY_WIDTH, STANDARD_HEIGHT);

    player_line_edit_->setValidator( new QIntValidator(3, 26, this) );

    connect(player_line_edit_, SIGNAL(editingFinished()),
            this, SLOT(handle_player_line_edit()));
}

void MainWindow::init_start_button()
{
    start_push_button_ = new QPushButton(this);
    start_push_button_->setGeometry(MARGIN, MARGIN + MARGIN + DISPLAY_HEIGHT,
                                    FUNCTION_BUTTON_WIDTH, STANDARD_HEIGHT);
    start_push_button_->setStyleSheet("QPushButton {background-color:"
                                      "rgb(130,180,110); color: white;}");
    start_push_button_->setText("Start");
    start_push_button_->setVisible(true);

    connect(start_push_button_, SIGNAL(clicked()),
            this, SLOT(handle_start_push_button()));
}

void MainWindow::init_close_button()
{
    close_push_button_ = new QPushButton(this);
    close_push_button_->setGeometry(MARGIN + MARGIN + FUNCTION_BUTTON_WIDTH,
                                    MARGIN + MARGIN + DISPLAY_HEIGHT,
                                    FUNCTION_BUTTON_WIDTH, STANDARD_HEIGHT);
    close_push_button_->setStyleSheet("QPushButton {background-color:"
                                      "rgb(250,120,120); color: white;}");
    close_push_button_->setText("Close");
    close_push_button_->setVisible(true);

    connect(close_push_button_, SIGNAL(clicked()),
            this, SLOT(handle_close_push_button()));
}

// Deals the cards to the game board face down. Creates new Card objects and
// stores them
void MainWindow::init_cards()
{
    QString order = set_random_order();
    int columns = calculate_columns();

    int column = 0;
    int row = 0;
    int x_coordinate = 0;
    int y_coordinate = 0;

    for(QChar c: order)
    {
        if (column == columns)
        {
            row += 1;
            column = 0;
        }

        QPushButton* pushButton = new QPushButton(this);

        x_coordinate = MARGIN + MARGIN + DISPLAY_WIDTH +
                       column * (MARGIN + CARD_BUTTON_WIDTH);
        y_coordinate = MARGIN + row * (MARGIN + CARD_BUTTON_HEIGHT);
        pushButton->setGeometry(x_coordinate, y_coordinate,
                                CARD_BUTTON_WIDTH, CARD_BUTTON_HEIGHT);

        QString border_image = "border-image:url(:/backside.jpg);";
        pushButton->setStyleSheet(border_image);
        pushButton->setVisible(true);

        connect(pushButton, &QPushButton::clicked,
                this, &MainWindow::handle_card_button_click);

        Card* new_card = new Card(c, pushButton);
        cards_.push_back(new_card);

        ++column;
    }
    // Resize mainwindow so all cards can be seen
    this->resize(x_coordinate + CARD_BUTTON_WIDTH + MARGIN,
                 y_coordinate + CARD_BUTTON_HEIGHT + MARGIN);
}

// Creates a random order for the card
// Returns: QString order
QString MainWindow::set_random_order()
{
    // Get the seed number from current time seconds
    int seed = QTime::currentTime().second();

    QString order = "";
    // Create the card values
    int i = 0;
    char c = 'A';
    while (i < number_of_pairs_)
    {
        order += c;
        order += c;
        ++c;
        ++i;
    }

    // Shuffle the order
    shuffle(order.begin(), order.end(), std::default_random_engine(seed));
    return order;
}

// Finds factors that are as close together as possible.
// Returns: int columns
int MainWindow::calculate_columns()
{
    int number_of_cards = 2 * number_of_pairs_;
    int rows = 1;
    for(int i = 1; i * i <= number_of_cards; ++i)
    {
        if(number_of_cards % i == 0)
        {
            rows = i;
        }
    }
    // Colums is always the bigger of two
    int columns = number_of_cards/rows;
    return columns;
}

// Sets the game for certain number of pairs given as a user input
// Input: int number of pairs
void MainWindow::set_number_of_pairs()
{
    number_of_pairs_ = player_line_edit_->text().toInt();
    player_line_edit_->clear();

    // Set validator for aqcuiring number of players
    player_line_edit_->setValidator(new QIntValidator(1, 4, this));
}

// Sets the game for certain number of players given as a user input
// Input: int number of players
void MainWindow::set_number_of_players()
{
    number_of_players_ = player_line_edit_->text().toInt();
    player_line_edit_->clear();

    // Delete the validator for naming the players
    delete player_line_edit_->validator();
}

// Sets the name for each player and creates a new Player object
// Input: QString player name
void MainWindow::add_player()
{
    QString player_name = player_line_edit_->text();
    player_line_edit_->clear();
    Player* new_player = new Player(player_name);

    players_.push_back(new_player);

    // Disable and hide line edit after acquiring all data
    if (input_counter_ - 2 == number_of_players_)
    {
        // Set the first player
        player_in_turn_ = players_.at(0);

        player_line_edit_->setDisabled(true);
        player_line_edit_->setVisible(false);

        // Init buttons
        init_start_button();
        init_close_button();

        // Restore input counter to 0
        // since it will be needed for managing turns
        input_counter_ = 0;
    }

    QString text = "Player " + player_name + " added";
    print_info(text);
}

// Small print function for ease of use
void MainWindow::print_info(const QString& text)
{
    info_text_browser_->setText(text);
}

// Prints the info about who is taking turn.
void MainWindow::print_turn()
{
    QString text = player_in_turn_->get_name() + "'s turn";
    print_info(text);
}

// Checks for winners and prints the info on the screen
void MainWindow::print_winners()
{
    // Evaluates winners
    std::vector<Player*> winners = {};
    for (Player* player : players_)
    {
        if (winners.empty())
        {
            winners.push_back(player);
        }
        else if (player->get_pair_amount() > winners.at(0)->get_pair_amount())
        {
            winners.clear();
            winners.push_back(player);
        }
        else if (player->get_pair_amount() == winners.at(0)->get_pair_amount())
        {
            winners.push_back(player);
        }
    }

    // Print winners
    QString text = "Game over!\n";
    if (winners.size() == 1)
    {
        text += "The winner is: \n\n";
    }
    else
    {
        text += "It's a tie.\n\n";
    }
    for (Player* winner : winners)
    {
        text += winner->get_name() + ", ";
    }
    text.chop(2);
    text += " - " + QString::number(winners.at(0)->get_pair_amount())
            + " pairs";
    print_info(text);
}

// Manages user inputs. Doesn't really do anything itself other than call
// the right functions at the right time
void MainWindow::handle_player_line_edit()
{
    input_counter_ += 1;

    // First input is the number of cards
    if (input_counter_ == 1)
    {
        set_number_of_pairs();
        print_info(PLAYER_AMOUNT);
        return;
    }

    // Second input is the amount of players
    if (input_counter_ == 2)
    {
        set_number_of_players();
        print_info(PLAYER_NAMES);
        return;
    }

    // Rest of the inputs are for adding new players
    add_player();
}

// Starts the game and disables the start button
void MainWindow::handle_start_push_button()
{
    start_push_button_->setDisabled(true);
    start_push_button_->setStyleSheet("QPushButton {background-color:"
                                      "rgb(200,240,170); color: white;}");
    print_turn();
    init_cards();
}

// Closes the game
void MainWindow::handle_close_push_button()
{
    close();
}

// Handles the input signal of a card button and turns the card visible.
void MainWindow::handle_card_button_click()
{
    // Find the button which was clicked
    QPushButton* clicked_button = static_cast<QPushButton*>(sender());

    // Find the correspondin card object
    for (Card* card : cards_)
    {
        if (card->get_button() == clicked_button)
        {
            // Disable card so it cannot be clicked twice
            card->get_button()->setDisabled(true);

            // Set card as visible
            card->set_hidden();

            QChar c = card->get_letter();
            QString border_image = "border-image:url(:/" +
                                    animals_.at(c) + ".jpg);";
            card->get_button()->setStyleSheet(border_image);

            turned_cards_.push_back(card);
        }
    }
    // Continue with a turn
    play_turn();
}

// Turns cards back face down
void MainWindow::turn_hidden()
{
    for (Card* card : cards_)
    {
        if (card->is_hidden() == false)
        {
            card->set_hidden();
            QString border_image = "border-image:url(:/backside.jpg);";
            card->get_button()->setStyleSheet(border_image);
        }
    }
    turned_cards_.clear();
    disable_all_cards();
}

// Disables all cards so they cannot be clicked during animations
void MainWindow::disable_all_cards()
{
    cards_enabled_ = !cards_enabled_;
    for (Card* card : cards_)
    {
        card->get_button()->setEnabled(cards_enabled_);
    }
}

// Removes the pair from the game board
void MainWindow::remove_cards()
{
    for (Card* card : turned_cards_)
    {
        card->get_button()->setVisible(false);
    }
    turned_cards_.clear();
    disable_all_cards();
}

// Handles each turn of a game.
void MainWindow::play_turn()
{
    // If two cards have been turned, check for pair
    if (turned_cards_.size() == 2)
    {
        // No cards can be clicked while two are visible
        disable_all_cards();

        // Checks the turned cards for pairs
        if (not is_pairs())
        {
            // set the next player in turn;
            if (input_counter_ < number_of_players_ - 1)
            {
                input_counter_ += 1;
            }
            else
            {
                input_counter_ = 0;
            }
            player_in_turn_ = players_.at(input_counter_);
        }
        else
        {
            // if game is over
            if (pairs_found_ == number_of_pairs_)
            {
                // print celebrations
                print_winners();

                // Set game to the beginning state
                QTimer::singleShot(DELAY, this, SLOT(set_restart()));
                return;
            }
        }
        // Call to inform who is taking a turn next
        QTimer::singleShot(DELAY, this, SLOT(print_turn()));
    }
}

// Checks if turned cards make a pair and manages accordingly
bool MainWindow::is_pairs()
{
    Card* card_1 = turned_cards_.at(0);
    Card* card_2 = turned_cards_.at(1);

    // If pair is found
    if ( card_1->get_letter() == card_2->get_letter() )
    {
        pairs_found_ += 1;

        // Add card to the player
        QChar letter = card_1->get_letter();
        player_in_turn_->add_pair(letter);

        // Inform that a pair has been found and how many pairs they now have
        QString text = "Pair found: " + animals_.at(letter) + "\n\n" +
                       player_in_turn_->get_name() + " has " +
                       QString::number(player_in_turn_->get_pair_amount()) +
                       " pairs";
        print_info(text);

        // Call to remove cards from game board
        QTimer::singleShot(DELAY, this, SLOT(remove_cards()));

        return true;
    }
    // Call to turn the cards back if pair was not found
    QTimer::singleShot(DELAY, this, SLOT(turn_hidden()));

    print_info("Pair not found");
    return false;
}

