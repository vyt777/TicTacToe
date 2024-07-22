#include <string>
#include <iostream>
#include <limits>
#include <map>
using namespace std;


typedef enum Results {draw, user_x, user_o} result;
typedef struct {
    string name;
    char move;
} UserName;
    
class TicTacToe
{
    UserName user1;
    UserName user2;
    static const int board_size = 4;
    char board[board_size][board_size+1];
public:
    TicTacToe();
    void set_user_name(UserName *user);
    void set_board();
    void play();
    void game();
    bool play_again();
    void print_board();
    bool check_move(std::istream& cin, int *x);
    void add_move(UserName user);
    Results game_finished();
};

TicTacToe::TicTacToe()
{
    user1.name = "Unknown";
    user2.name = "Unknown";
    user1.move = 'X';
    user2.move = 'O';
    char board[board_size][board_size+1] = {};
}

void TicTacToe::set_user_name(UserName *user)
{
    cout<<"Player "<<user->move<<", please enter your name\n";
    cin>>user->name;
}

void TicTacToe::set_board()
{
    cout<<"Preparing game board...\n";
    for(int i = 0; i < board_size; i++){
        for(int j = 0; j < board_size; j++){
            board[i][j] = '-';
        }
    }
}

void TicTacToe::play()
{
    // set names
    set_user_name(&user1);
    set_user_name(&user2);

    // game cycle
    while(true){
        game();
        print_board();
        if(!play_again()){
            break;
        }
    }
    return;
}

void TicTacToe::game(){
    Results result = draw;

    set_board();
    int turns_left = 8;
    while(turns_left){
        add_move(user1);
        result = game_finished();
        if(result){
            cout<<"Player "<<user1.name<<" won!\n";
            return;
        }
        add_move(user2);
        result = game_finished();
        if(result){
            cout<<"Player "<<user2.name<<" won!\n";
            return;
        }
        turns_left--;
    }
    cout<<"This is a tie\n";
    return;
}

bool TicTacToe::play_again(){
    while(true){
        cout<<"Do you want to play again?y/n\n";
        char play_again;
        cin>>play_again;
        switch (play_again){
            case 'y':
                return 1;  
            case 'n':
                return 0;                
            default:
                break;
        }
    }
}

bool TicTacToe::check_move(std::istream& cin, int *x){
    cin>>*x;
    if (!cin.fail() && (0 <= *x && *x <= 3)) {
        return 1;
    }
    cout<<"Need to provide a number from 0 to 3\n";
    return 0;
}

void TicTacToe::add_move(UserName user)
{
    while(true){
        print_board();
        int x, y;
        cout<<"User "<<user.name<<", please enter the coordinates of your move. First enter vertical\n";
        while(true){
            if(check_move(std::cin, &x)){
                break;
            }
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout<<"Now enter horizontal\n";
        while(true){
            if(check_move(std::cin, &y)){
                break;
            }
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        if(board[x][y] != '-'){
            cout<<"Can not place here\n";
        }
        else{
            board[x][y] = user.move;
            break;
        }
    }
}

void TicTacToe::print_board()
{
    cout<<"The board is:\n";
    for(int i = 0; i < board_size; i++){
        for(int j = 0; j < board_size; j++){
            cout<<"|"<<board[i][j]<<"|";
            if(j == 3){
                cout<<i;
            }
        }
        cout<<"\n";
    }
    for(int i = 0; i < board_size; i++){
        cout<<"|"<<i<<"|";
    }
    cout<<"\n";
}

Results TicTacToe::game_finished()
{
    string name;
    int num_x, num_o;
    
    // check horizontal
    for(int x = 0; x < board_size; x++){
        num_x = 0; 
        num_o = 0;
        for(int y = 0; y < board_size; y++){
            if(board[x][y] == '-'){
                break;
            }
            else if(board[x][y] == 'X'){
                num_x++;
            }            
            else if(board[x][y] == 'O'){
                num_o++;
            }     
            if(num_x >= board_size){
                return user_x;
            }         
            else if(num_o >= board_size){
                return user_o;
            }
        }
    }
    
    // check vertical
    for(int y = 0; y < board_size; y++){
        num_x = 0; 
        num_o = 0;
        for(int x = 0; x < board_size; x++){
            if(board[x][y] == '-'){
                break;
            }
            else if(board[x][y] == 'X'){
                num_x++;
            }            
            else if(board[x][y] == 'O'){
                num_o++;
            }     
            if(num_x >= board_size){
                return user_x;
            }         
            else if(num_o >= board_size){
                return user_o;
            }
        }
    }

    num_x = 0; 
    num_o = 0;
    // check diagonal, top left to down right
    for(int x = 0, y = 0; x < board_size; x++){
        y = x;
        if(board[x][y] == '-'){
            break;
        }
        else if(board[x][y] == 'X'){
            num_x++;
        }            
        else if(board[x][y] == 'O'){
            num_o++;
        }     
        if(num_x >= board_size){
            return user_x;
        }         
        else if(num_o >= board_size){
            return user_o;
        }
    }

    num_x = 0; 
    num_o = 0;
    // check diagonal, top right to down left
    for(int x = board_size - 1, y = 0; x >= 0, y < board_size; x--, y++){
        if(board[x][y] == '-'){
            break;
        }
        else if(board[x][y] == 'X'){
            num_x++;
        }            
        else if(board[x][y] == 'O'){
            num_o++;
        }     
        if(num_x >= board_size){
            return user_x;
        }         
        else if(num_o >= board_size){
            return user_o;
        }
    }

    return draw;
}
