#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
 
using namespace std;
 
//function prototypes
bool check_coordinate(int i , int j, int row, int col);
vector<string> placeword(vector<string> grid,string &word, vector<string> &invalid, int row,int col,int i , int j, int index,string &direction, bool &place);
vector<vector<string> >placeWordbyDirection(vector<string> grid,string &word,vector<string>&invalid, int row,int col,int i , int j, int index);
vector<vector<string> >generate_ordering(vector<string> &valid);
void group_of_words(vector<vector<string> > &order, vector<string> &valid, vector<string> grid, vector<string> &invalid, int row, int col, int index);
void print_board(vector<string> board,ofstream& out);
 
bool check_coordinate(int i , int j, int row, int col) {
    return ((i < row && j < col) && (i >= 0 && j >= 0));
}
 
/*function to place word recursively using direction
if it succeds push_back to temporary vector else keep searching*/
vector<vector<string> > placeWordbyDirection(vector<string>grid,string &word,vector<string>&invalid, int row,int col,int i , int j, int index) {
    vector<vector<string> >temp;
    string direction = "down";
    vector<string> temp1;
    bool successfulplacement=false;                            //flag to indicate if sucessful or not
    temp1 = placeword(grid,word,invalid,row,col,i,j,index,direction, successfulplacement);
    if (temp1.size() != 0) {                  //recursively tries to place word in down direction 
        temp.push_back(temp1);                //if sucessful push back 
    }
    direction = "right";
    successfulplacement=false;
    temp1 = placeword(grid,word,invalid,row,col,i,j,index,direction, successfulplacement);
    if(temp1.size() != 0) {                 //rest instructions works similar but for different directions
        temp.push_back(temp1);
    }
    direction = "left";
    successfulplacement=false;
    temp1 = placeword(grid,word,invalid,row,col,i,j,index,direction, successfulplacement);
    if(temp1.size() != 0) {
        temp.push_back(temp1);  
    }
    direction = "up";
    successfulplacement=false;
    temp1 = placeword(grid,word,invalid,row,col,i,j,index,direction, successfulplacement);
    if(temp1.size() != 0) {
        temp.push_back(temp1);
    }
    direction = "dia_right_down";
    successfulplacement=false;
    temp1 = placeword(grid,word,invalid,row,col,i,j,index,direction, successfulplacement);
    if(temp1.size() != 0) {
        temp.push_back(temp1);
    }
    direction = "dia_left_down";
    successfulplacement=false;
    temp1 = placeword(grid,word,invalid,row,col,i,j,index,direction, successfulplacement);
    if(temp1.size() != 0) {
        temp.push_back(temp1);
    }
    direction = "dia_right_up";
    successfulplacement=false;
    temp1 = placeword(grid,word,invalid,row,col,i,j,index,direction, successfulplacement);
    if(temp1.size() != 0) {
        temp.push_back(temp1);
    }
    direction = "dia_left_up";
    successfulplacement=false;
    temp1 = placeword(grid,word,invalid,row,col,i,j,index,direction, successfulplacement);
    if(temp1.size() != 0) {
        temp.push_back(temp1);
    }
    return temp;                                                         
}   
 
//generate different orderings and permutation
vector<vector<string> >generate_ordering(vector<string> &valid) {
    vector<vector<string> >order;
    do {
     vector<string> temp;
        for (int i = 0 ; i < valid.size();i++) {
            temp.push_back(valid[i]);
        }
        order.push_back(temp);
    }
    while (std::next_permutation(valid.begin(), valid.end()));         //next permutation generates all different permuation
    return order;
}
 
 
//function to print 1D board
void print_board(vector<string> board,ofstream &out) {
    out<<"Board:"<<endl;
    for (int i = 0 ; i < board.size();i++) {
        out<<"  "<<board[i]<<endl;
    }
}
 
//this function mergest 2D vectors
void merge(vector<vector<string> > &v1, vector<vector<string> > &v2){
    for(int i=0; i<v2.size(); ++i){
        v1.push_back(v2[i]);
    }
}
 
bool search_word_from_pos(std::vector<std::string> &grid, std::string &word, int curr_index, int start_x, int start_y, int row, int col, string &direction){
     
    if(!check_coordinate(start_x, start_y, row, col)){
        return false;
    }
    if(grid[start_x][start_y]!=word[curr_index]){
        return false;
    }
    if(curr_index==word.length()-1){
        return true;
    }
    if(direction=="right"){
        if(search_word_from_pos(grid, word, curr_index+1, start_x+1, start_y, row, col, direction))
        { return true; } //right
    }
    else if(direction=="left"){
        if(search_word_from_pos(grid, word, curr_index+1, start_x-1, start_y, row, col, direction))
            { return true; }
    }//left
    else if(direction=="down"){
        if(search_word_from_pos(grid, word, curr_index+1, start_x, start_y+1, row, col, direction))
            { return true; }
    }//down
    else if(direction=="up"){
        if(search_word_from_pos(grid, word, curr_index+1, start_x, start_y-1, row, col, direction))
            { return true; }
    }//upwards
    else if(direction=="diag_down_right"){
        if(search_word_from_pos(grid, word, curr_index+1, start_x+1, start_y+1, row, col, direction))
            { return true; }
    }//diag_down_right
    else if(direction=="diag_up_left"){
     if(search_word_from_pos(grid, word, curr_index+1, start_x-1, start_y-1, row, col, direction))
        { return true; }
    }//diag_up_left
    else if(direction=="diag_down_left"){
        if(search_word_from_pos(grid, word, curr_index+1, start_x-1, start_y+1, row, col, direction))
        { return true;} //diag_down_left
    }
    else if(direction=="diag_up_right"){
        if(search_word_from_pos(grid, word, curr_index+1, start_x+1, start_y-1, row, col, direction))
        { return true; } //diag_up_right
    }
    return false;
}
 
//function to search word in the possible grids
bool search_word(std::vector<std::string> &grid, std::string &word, int row, int col){
    for(int i=0; i<row; ++i){
        for(int j=0; j<col; ++j){
            std::string dir="right";
            if(search_word_from_pos(grid, word, 0, i, j, row, col, dir)){
                return true;
            }
            dir="left";
            if(search_word_from_pos(grid, word, 0, i, j, row, col, dir)){
                return true;
            }
            dir="down";
            if(search_word_from_pos(grid, word, 0, i, j, row, col, dir)){
                return true;
            }
            dir="up";
            if(search_word_from_pos(grid, word, 0, i, j, row, col, dir)){
                return true;
            }
            dir="diag_down_right";
            if(search_word_from_pos(grid, word, 0, i, j, row, col, dir)){
                return true;
            }
            dir="diag_up_left";
            if(search_word_from_pos(grid, word, 0, i, j, row, col, dir)){
                return true;
            }
            dir="diag_down_left";
            if(search_word_from_pos(grid, word, 0, i, j, row, col, dir)){
                return true;
            }
            dir="diag_up_right";
            if(search_word_from_pos(grid, word, 0, i, j, row, col, dir)){
                return true;
            }
             
        }
    }
    return false;
}
 
/*After words are place in grid make sure that all valid words are in grid
recursively search whole grid*/
bool checkValidSolution(vector<string> &curr_config, vector<string> &valid, vector<string> &invalid, int row, int col){
    for(int i=0; i<valid.size(); ++i){
        if(!search_word(curr_config, valid[i], row, col)){
            return false;
        }
    }
     
    for(int j=0; j<invalid.size(); ++j){
        if(search_word(curr_config, invalid[j], row, col)){
            return false;
        }
    }
     
    return true;
}
 
//if current states of soltuin consist of invalid words then neglect those solution
vector<vector<string> > eliminateInvalidSolutions(vector<vector<string> > &curr_config, vector<string> &valid, vector<string> &invalid, int row, int col){
    vector<vector<string> > valid_solutions;
    for(int i=0; i<curr_config.size(); ++i){
        if(checkValidSolution(curr_config[i], valid, invalid, row, col)){      //checks if the solution is valid
            valid_solutions.push_back(curr_config[i]);
        }
    }
    return valid_solutions;
}
 
 
/*Earlier we were only using string word but these function 
takes whole valid vector and tries to place them in grid*/
vector<vector<string> > group_of_words(vector<string> &valid, vector<string> grid, vector<string> &invalid, int row, int col, int index) {
    vector<vector<string> > board_states;
    board_states.push_back(grid);
    for (int x = 0; x < valid.size();x++) {
        vector<vector<string> > before_board_states;
            for(int i = 0; i < grid.size(); ++i){
                for(int j = 0; j < grid[i].size(); ++j){
                vector<vector<string> > modified_board_states;
                    for (int k = 0 ; k < board_states.size();k++) {
                        vector<vector<string> > curr_board_states = placeWordbyDirection(board_states[k],valid[x],invalid,row,col,i ,j,index);
                        merge(modified_board_states, curr_board_states);
                    }
                    merge(before_board_states, modified_board_states);
            }
          }
          if(before_board_states.size()!=0){
             board_states.clear();
          }
          merge(board_states, before_board_states);
    }
    return board_states;
}
 
vector<vector<string> > emptyspots(vector<string> &valid, vector<string> grid, vector<string> &invalid, int row, int col, int index) {
    vector<vector<string> >board = group_of_words(valid,grid,invalid,row,col,index);
    vector<pair<int,int> >temp;
    for (int x = 0 ; x < board.size();x++) {
        for (int y = 0 ; y < board[x].size();y++) {
                if (board[x][y] == ' ') {
                     temp.push_back(make_pair(x,y));    
                    }
                }
            }
        }
    return board;
}
//checks if two board have same elements checks for duplicateb boards
bool are_equal_board_config(vector<string> &grid1, vector<string> &grid2){
    for(int i=0; i<grid1.size(); ++i){
        for(int j=0; j<grid1[i].size(); ++j){
            if(grid1[i][j]!=grid2[i][j]){                            
                return false;
            }
        }
    }
    return true;
}
 
//if there are duplicate board, remove it
vector<vector<string> > remove_duplicates(vector<vector<string> > &all_solutions_config, vector<vector<string> > &curr_config){
    vector<vector<string> > removed_duplicates;                      //final 2D vector that doesnt contain duplicate boards
    for(int i=0; i<curr_config.size(); ++i){
        bool already_present=false;
        for(int j=0; j<all_solutions_config.size(); ++j){
            if(are_equal_board_config(all_solutions_config[j], curr_config[i])){       //check if duplicate
                already_present=true;       
            }
        }
        if(!already_present){
            removed_duplicates.push_back(curr_config[i]);         //if not duplicate then push to vector
        }
    }
    return removed_duplicates;
}
 
/*function that prints solutions depending upton integer which says 1 (one solution) or 2 
for all solution*/
void solutions(int type,ofstream& out,vector<string> grid, vector<string> &valid, vector<string> &invalid,int row, int col, int i, int j, int index) {
    vector<vector<string> > all_solutions_configurations;
    vector<vector<string> > possibly;
    possibly = generate_ordering(valid);
    for(unsigned int x=0; x<possibly.size(); ++x){
            vector<vector<string> > curr_config;
            curr_config=group_of_words(possibly[x], grid, invalid, row, col, index);
            curr_config=remove_duplicates(all_solutions_configurations, curr_config);
            merge(all_solutions_configurations, curr_config);
    }
        all_solutions_configurations=eliminateInvalidSolutions(all_solutions_configurations, valid, invalid, row, col); //calling function to eliminate invalid solution
            for (int l = 0 ; l < possibly.size();i++) {
                for (int m = 0 ; m < possibly[i].size();m++) {
                    emptyspots(possibly[i],grid,invalid,row,col,index);
                }
            }
            if (all_solutions_configurations.size() == 0) {
                out<<"No solutions found"<<endl;
                return;
            }
            if (type == 1) {            //1 is for one solution
            print_board(all_solutions_configurations[0],out);
            }
            else {
            out<<all_solutions_configurations.size()<<" solution(s)"<<endl;
            }
            for (int l = 0 ; l < all_solutions_configurations.size();l++) {
                vector<string> soln=all_solutions_configurations[l];
                if ( type == 2) {
                 
                print_board(all_solutions_configurations[l],out);
                }
            }
     
    group_of_words(valid,grid,invalid,row,col,index);
}
 
 
//this function  tired all postions in grid and tried to place character by character
//return when the word is placed, if not sucessful to place any words return empty vector
vector<string> placeword(vector<string> grid,string &word, vector<string> &invalid, int row,int col,int i , int j, int index,string &direction, bool &place) {
  vector<string> progress_grid(0);
  if (check_coordinate(i,j,row,col) && grid[i][j] == ' ') {
    if (index <= word.length()-1) {
        grid[i][j] = word[index];
        if (direction == "down") {
            progress_grid=placeword(grid,word,invalid,row,col,i+1,j,index+1,direction, place);            
        }
        if (direction == "right") {
            progress_grid=placeword(grid,word,invalid,row,col,i,j+1,index+1,direction, place);  
        }
        if (direction == "dia_right_down") {
            progress_grid=placeword(grid,word,invalid,row,col,i+1,j+1,index+1,direction, place);          
        }   
        if (direction == "left") {
            progress_grid=placeword(grid,word,invalid,row,col,i,j-1,index+1,direction, place); 
        }
        if (direction == "dia_left_down") {
            progress_grid=placeword(grid,word,invalid,row,col,i+1,j-1,index+1,direction, place);
        }
        if (direction == "dia_right_up") {
            progress_grid=placeword(grid,word,invalid,row,col,i-1,j+1,index+1,direction, place);
        }
        if (direction == "dia_left_up") {
            progress_grid=placeword(grid,word,invalid,row,col,i-1,j-1,index+1,direction, place);
        }
        if (direction == "up") {
            progress_grid=placeword(grid,word,invalid,row,col,i-1,j,index+1,direction, place);
        }
    }
   }else{
     
        if(index==word.length()){                                    //if word fits
            place=true;
            return grid;
        }
     
        if (!check_coordinate(i,j,row,col)) {
            return vector<string>(0);                                 //return empty vector
        }
        if (grid[i][j] != ' ') {
            return vector<string>(0);                            
        }   
   }
        if(place){                                                            
            return progress_grid;
        }
            return vector<string>(0);
}
 
int main(int argc,char *argv[]) {
     //using input instead  od cin since we are reading file
    string line;        
    ifstream input(argv[1]);    
    //open text file i.e arg 1
    if(!input.good()){
        std::cerr<<"Cannot open "<<argv[3]<<"to read.."<<std::endl;       //error message is file is not good
    }
    vector<string>words;          //storing whiole text file into vector of strings
    int col;
    int row;
    input>>col;
    input>>row;
    while(input>>line) {              //read word by word in a line till end of line
        words.push_back(line);        
    }
    vector<string> valid;             //vecotr with '+'' words
    vector<string> invalid;           //vector with '-' words
    int type;
    vector<string> grid(row, "");
        for (int i = 0; i < words.size();i++) {
            if (words[i] == "+") {
              valid.push_back(words[i+1]);
            }
            if (words[i] == "-") {
            invalid.push_back(words[i+1]);
            }
        }
    for (int i = 0 ; i < row; i++) {
        for (int j = 0; j < col ;j++) {
            grid[i] += " ";
        }
    }
    //vector<pair<int,int> > temp;
    ofstream out_str(argv[2]);       //output file
    if (string(argv[3]) == string("one_solution")) {    //arguments are compared andd renders accordingly
        solutions(1,out_str,grid,valid,invalid,row,col,0,0,0);  // stsrting at origin so x and y is 0,0)
    }
     
    if (string(argv[3]) == string("all_solutions")) {   
        solutions(2,out_str,grid,valid,invalid,row,col,0,0,0);
    }
 }
