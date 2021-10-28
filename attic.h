
#include <iostream>  // evident use
#include <cstdlib>   // randomness and booleans
#include <ctime>     // randomness
#include <fstream>   // for files
#include <string>    // for strings
#include <windows.h> // for 'Sleep()' and 'system("cls")', waiting and clearing the screen

// important constants
const int PAIRS_IN_DECK = 9;
const int LINES_IN_CARD = 10;
const int CHARS_IN_LINE = 26;

std::string ANIMAL_PACK = "animals.dat"; // currently used
std::string ADDITIONAL_PACK = "additional.dat"; // not used yet, not ready
std::string UNKNOWNS_PACK = "unknowns.dat"; // contains unknown card and empty card




class Card{
private:
    int id;                                // used to check if cards are the same
    int position;                          // unique to every card, used to select the card
    std::string image[LINES_IN_CARD];      // the image on the card, each line is a string
public:
    Card(const int card_in_file_and_id, std::ifstream &my_file);  //card_in_file_and_id : the card chosen from the file and id

    // setters and getters
    const int get_position() {return position;}
    const int get_id() {return id;}
    void set_position(int a) {position = a;}
    std::string get_line(int i) {return (image[i]).substr(0, /*(image[i]).size() - 2*/ 25);};

    // test function, not used in final program
    void print_image_for_test();

    };


class Board{
private:
    Card *deck[PAIRS_IN_DECK * 2];      // the real deck, contains Card pointers, will not be printed or directly interacted with
    Card *unknown[PAIRS_IN_DECK * 2];   // the shown deck, will be printed, copies Card addresses from the real deck to print out the chosen cards
    Card *no_card;                      // or "empty card", its address is copied to any successfully found pair of cards

    void shuffle();                     // self explanatory
    void swap_cards(int a, int b);      // used in 'shuffle()'
    void position();                    // "position : verb", used to set the initial card positions before shuffling

public:
    Board(std::string path);            // constructor
    void print_the_unknown();           // printing deck of unknowns
    bool is_there_unknown();            // used to terminate the game
    void select_two();                  // important function used in 'main()'

    // test functions, not used in final program
    void print_cards_for_test();
    void print_unkowns_for_test();
    void print_card_for_test(int i) {(deck[i])->print_image_for_test();};
    void print_the_deck_test();
    };


// free functions' declarations

int random();   // returns random position, used in 'shuffle()'
void jump_cards(int num_of_cards, std::ifstream &my_file);    // not used, was going to be used in reading card images from file
void wait();    // wait 3 seconds after choosing two cards
