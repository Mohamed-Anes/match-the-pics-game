// This is a program made by MIHOUBI Mohamed Anes, as a project for the MIT ocw course "Introduction to C++"
//course number 6.096 January IAP 2011
// This is a picture matching game, where in each turn the player picks two cards to flip and their
//contents and they should match, where they will be excluded until all pa




#include"attic.h"  // check this first

int main()
{
    // seed for random numbers
    srand(time(0));

    // Board class instance
    Board my_board(ANIMAL_PACK);


    // looping until all matching cards are found
    while((my_board.is_there_unknown()) != 0){
        system("cls");
        my_board.print_the_unknown();

        my_board.select_two();
        }
    std::cout << "\n\n" << "CONGRATULATIONS!!!" << "\n\n";


    return 0;
}

















int random(){
    return (rand() % (PAIRS_IN_DECK * 2));

    }

void Board::shuffle(){
    std::cout << "shuffling.." << std::endl;
    for(int i = 0; i < 30; ++i){
        swap_cards(random(), random());
        }
    position();
    }

void Board::swap_cards(int a, int b){
    Card *temp;
    temp = deck[a];
    deck[a] = deck[b];
    deck[b] = temp;
    }

void Board::position(){
    for(int i = 0; i < PAIRS_IN_DECK * 2; ++i){
        deck[i]->set_position(i);
        }
    }

Board::Board(std::string path){
    std::ifstream my_file;
    my_file.open(path);
    for(int i = 0; i < PAIRS_IN_DECK * 2; ++i){
        std::cout << "generating card number " << i << std::endl;
        if(i == PAIRS_IN_DECK){
            my_file.close();
            my_file.open(path);
            }
        deck[i] = new Card(i % PAIRS_IN_DECK, my_file);
        std::cout << "done" << std::endl;
        }

    shuffle();
    my_file.close();


    std::ifstream unknowns_file;
    for(int i = 0; i < PAIRS_IN_DECK * 2; ++i){
        unknowns_file.open(UNKNOWNS_PACK);

        unknown[i] = new Card(1, unknowns_file);

        if(i != ((PAIRS_IN_DECK * 2) - 1))
            unknowns_file.close();
        }
    no_card = new Card(0, unknowns_file);
    unknowns_file.close();
    }

Card::Card(const int card_in_file_and_id, std::ifstream &my_file){
    id = card_in_file_and_id;

    //jump_cards(/*card_in_file_and_id*/ 1, my_file); // numbering of cards starts from 0

    for(int i = 0; i < LINES_IN_CARD; ++i){
        char temp;

        for(int j = 0; j < CHARS_IN_LINE; ++j){

            my_file.get(temp);
            image[i] += temp;
            }
        }
    }

void jump_cards(int num_of_cards, std::ifstream &my_file){
    char temp;
    for(int i = 0; i < num_of_cards * LINES_IN_CARD; ++i){

        for(int j = 0; j < CHARS_IN_LINE; ++j){

            my_file.get(temp);
            }
        }
    }

void Card::print_image_for_test(){
    std::cout << "card number " << position << std::endl;

    for(int i = 0; i < LINES_IN_CARD; ++i){
        //std::cout << (image[i]).size() << std::endl << image[i];
        std::cout << image[i];
        std::cout << int((image[i])[26]);
        }

    }

void Board::print_cards_for_test(){
    for(int i = 0; i < PAIRS_IN_DECK * 2; ++i){
        (*deck[i]).print_image_for_test();
        std::cout << "\n\n\n";
        }
    }

void Board::print_unkowns_for_test(){
    for(int i = 0; i < PAIRS_IN_DECK * 2; ++i){
        (*unknown[i]).print_image_for_test();
        std::cout << "\n\n\n";
        }
    (*no_card).print_image_for_test();
    }


void Board::print_the_deck_test(){

    for(int k = 6; k < 19; k += 6){
        for(int i = 0; i < LINES_IN_CARD; ++i){
            for(int j = k - 6; j < k; ++j){
                std::cout << (deck[j])->get_line(i) << "  ";
                }
            std::cout << std::endl;
            }
        }
    }

void Board::print_the_unknown(){

    for(int k = 6; k < ((PAIRS_IN_DECK * 2) + 1); k += 6){
        for(int i = 0; i < LINES_IN_CARD - 1; ++i){
            for(int j = k - 6; j < k; ++j){
                std::cout << (unknown[j])->get_line(i) << "  ";
                }
            std::cout << std::endl;
            }
        for(int j = k - 6; j < k; ++j){
                if(j < 9){
                    std::cout << (unknown[j])->get_line(LINES_IN_CARD - 1) << "\b" << j+1 << "  ";
                    }
                else{
                    std::cout << (unknown[j])->get_line(LINES_IN_CARD - 1) << "\b\b" << j+1 << "  ";
                    }
                }
            std::cout << std::endl;
        }
    }



// returns 1 if there are still unknown cards in the deck, 0 if all are empty cards
bool Board::is_there_unknown(){
    for(int i = 0; i < PAIRS_IN_DECK * 2; ++i){
        if((unknown[i]->get_id()) == 1){
            return 1;
            }
        }
    return 0;
    }


void Board::select_two(){
    std::cout << "enter two card numbers : ";
    int a, b;

    do{
        std::cin >> a >> b;
        if((a < (PAIRS_IN_DECK * 2) && a >= 0) && (b < (PAIRS_IN_DECK * 2) && b >= 0)){
            break;
            }
        std::cout << "invalid" << std::endl << " : ";
        }while(1);
    --a;
    --b;

    Card *temp_a = unknown[a];
    Card *temp_b = unknown[b];

    unknown[a] = deck[a];
    unknown[b] = deck[b];


    system("cls");
    print_the_unknown();

    if(((unknown[a])->get_id()) == ((unknown[b])->get_id())){
        unknown[a] = no_card;
        unknown[b] = no_card;
        std::cout << "great!!" << std::endl;
        }
    else{
        unknown[a] = temp_a;
        unknown[b] = temp_b;
        std::cout << "try again" << std::endl;
        }

    wait();



    }

void wait(){
    std::cout << "...";
    for(int i = 3; i >= 0; --i){
        std::cout << "\b" << i;
        Sleep(1000);
        }
    }

