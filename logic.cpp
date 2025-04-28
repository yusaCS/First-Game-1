#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    ifstream inFS;                 //inFS is the operator I'm using to open and read file.
    inFS.open(fileName);           //I open the file the file in format filename.txt

    if(!inFS.is_open()){                           //I checked that the file is opened without any problem?
        cout << "I couldn't open file" << endl;
        return nullptr;
    }

    while(!(inFS >> maxRow)){
        cout << "Error: read non-integer value";   // I checked that maxRow value is valid for an integer
        return nullptr; 
    }

    while(!(inFS >> maxCol)){
        cout << "Error: read non-integer value";   // I checked that maxCol value is valid for an integer
        return nullptr; 
    }

    while(!(inFS >> player.row)){
        cout << "Error: read non-integer value";   // I checked that player.row value is valid for an integer
        return nullptr; 
    }

    while(!(inFS >> player.col)){
        cout << "Error: read non-integer value";   // I checked that player.col value is valid for an integer
        return nullptr; 
    }

    if((maxCol < 1)||(maxRow < 1)){
        cout << "Column and row numbers are smaller than 1, map cannot created" << endl;
        return nullptr;
    }

    if((player.col < 0)||(player.col >= maxCol)||(player.row < 0)||(player.row >= maxRow)){
        cout << "The adventurer's starting point is out-of-boundary, cannot locate on the map" << endl;
        return nullptr; 
    }

    if(INT32_MAX/maxRow < maxCol){
        return nullptr;
    }

    char** map = createMap(maxRow, maxCol);       // A map is created which has maxRow rows and maxCol columns and filled by TILE_OPEN.

    char currentChar;                        // I will read every char in file and assign to currentChar variable and I fill the map.
    bool dorOrExit = false;

    for (int a = 0; a < maxRow; a++){
        for(int b = 0; b < maxCol; b++){
            while(!(inFS >> currentChar)){                   //I read the characters from the file
                cout << "Error: read non-character value";   // I checked that current char value is valid for a char
                return nullptr; 
            }

            if(currentChar == TILE_OPEN){                    // I'm checking the read character and inserting the character into map.
                map[a][b] = TILE_OPEN;
            
            }else if(currentChar == TILE_TREASURE){
                map[a][b] = TILE_TREASURE;
                
            }else if(currentChar == TILE_AMULET){
                map[a][b] = TILE_AMULET;
                
            }else if(currentChar == TILE_MONSTER){
                map[a][b] = TILE_MONSTER;
                
            }else if(currentChar == TILE_PILLAR){
                map[a][b] = TILE_PILLAR;
                
            }else if(currentChar == TILE_DOOR){
                dorOrExit = true;
                map[a][b] = TILE_DOOR;
                
            }else if(currentChar == TILE_EXIT){
                dorOrExit = true;
                map[a][b] = TILE_EXIT;
                
            }else {
                cout << "There is an unrecognized character in file" << endl;
                return nullptr;
            }
        }
    }

    if(dorOrExit == false){
        return nullptr;
    }

    
    while(inFS >> currentChar){
        return nullptr;
    }

    

    if (map[player.row][player.col] != TILE_OPEN){          //I'm checking the availability of the location of the adventurer's starting point.
        cout << "There is an obstacle at the starting point of adventurer, I cannot locate it." << endl;
        return nullptr;
    }

    map[player.row][player.col] = TILE_PLAYER;     // located the adventurer on the map.

    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {

    if (input == MOVE_UP){
        nextRow = nextRow - 1;
        nextCol = nextCol;

    }else if (input == MOVE_DOWN){
        nextRow = nextRow + 1;
        nextCol = nextCol;

    }else if (input == MOVE_LEFT){
        nextRow = nextRow;
        nextCol = nextCol - 1;

    }else if (input == MOVE_RIGHT){
        nextRow = nextRow;
        nextCol = nextCol + 1;

    }else{
        nextRow = nextRow;                          // LAST CHANGE
        nextCol = nextCol;                          // LAST CHANGE
    }
    
    
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    char** map = new char*[maxRow];             //I create a double pointer it map. Map is an array ,has maxRow elements, which carry pointers for each row.

    for(int i = 0; i < maxRow; i++){            // first for loop reach the row pointers in the map array
        map[i] = new char[maxCol];               // I declare the size of each row pointer in the map array.
        for (int x = 0; x < maxCol; x++){        // second for loop reaches the element of each row
            map[i][x] = TILE_OPEN;               // I assign each element of row arrays as "-"(TILE_OPEN)
        }
    }

    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if (map == nullptr){
        maxRow = 0;
        return;
    }
    
    for (int d = 0; d < maxRow; d++){
        delete[] map[d];                              //what happens if I delete map[d] and delete map???
    }                                   
    delete[] map;
    map = nullptr;    //Am I update map to be nullptr correctly?         //LAST CHANGE
    maxRow = 0;        //Am I update maxRow to be zero?                  //LAST CHANGE
    
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    if (map == nullptr){
        return nullptr;
    }
    if ((maxRow <= 0)||(maxCol <= 0)){
        return nullptr;
    }

    int TWOmaxRow = maxRow*2;                   // I create a new variable for the doubled size row
    int TWOmaxCol = maxCol*2;                   // I create a new variable for the doubled size column
    char** TWOmap = new char*[TWOmaxRow];        // I create a new double pointer for bigger size map
    for (int f = 0; f < TWOmaxRow; f++){         // this for loop assign every element(pointer) of array with a an array which size is double row.
        TWOmap[f] = new char[TWOmaxCol];
    }

    for (int g = 0; g < maxRow; g++){            // I will fill the new map in 4 for loop.
        for (int h = 0; h < maxCol; h++){        // I'm filling the upper left part of the new map in this loop
            TWOmap[g][h] = map[g][h];
        }
    }

    for (int d = 0; d < maxRow; d++){            // I'm filling the upper right part of the new map in this loop
        for (int e = 0; e < maxCol; e++){        
            if (map[d][e] == TILE_PLAYER){
                TWOmap[d][e+maxCol] = TILE_OPEN;
            }else {
                TWOmap[d][e+maxCol] = map[d][e];
            }
        }
    }

    for (int p = 0; p < maxRow; p++){            // I'm filling the below left part of the new map in this loop
        for (int r = 0; r < maxCol; r++){  
            if (map[p][r] == TILE_PLAYER){
                TWOmap[p+maxRow][r] = TILE_OPEN;
            }else{    
                TWOmap[p+maxRow][r] = map[p][r];
            }
        }
    }

    for (int u = 0; u < maxRow; u++){            // I'm filling the below right part of the new map in this loop
        for (int v = 0; v < maxCol; v++){  
            if (map[u][v] == TILE_PLAYER){
                TWOmap[u+maxRow][v+maxCol] = TILE_OPEN;
            }else {   
                TWOmap[u+maxRow][v+maxCol] = map[u][v];
            }
        }
    }

    deleteMap(map, maxRow);            // I delete the previous map to avoid memory leak
    map = TWOmap;                      // I assign the map double pointer with new big map double pointer variable;
    maxRow = TWOmaxRow;                // I doubled the maxRow
    maxCol = TWOmaxCol;                // I doubled the maxCol


    return map;                         // I return the double pointer map
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    //cout << maxRow << " " << maxCol << " " << nextRow << " " << nextCol << endl;


    if((nextRow < 0)||(nextRow >= maxRow)||(nextCol < 0)||(nextCol >= maxCol)){        // I covered the case for moving out-of-map first
        nextRow = player.row;                                                          // player cannot move, so nextRow is current row
        nextCol = player.col;                                                          // and nextCol is current column
        return STATUS_STAY;                                                         
    
    }else if((map[nextRow][nextCol] == TILE_MONSTER)||(map[nextRow][nextCol] == TILE_PILLAR)){  // I cover the case moving onto monster and obstacle
        nextRow = player.row;                                                                      // player cannot move, so nextRow is current row                                      
        nextCol = player.col;                                                                      // and nextCol is current column
        return STATUS_STAY;
    
    }else if(map[nextRow][nextCol] == TILE_TREASURE){                     // I cover the case moving onto treasure
        player.treasure++;                                                // I increment the treasure
        map[player.row][player.col] = TILE_OPEN;                          // I update the tile before we move to TILE_OPEN
        player.row = nextRow;                                             // current row become the nextRow (we are moving)
        player.col = nextCol;                                             // current column become the nextCol (we are moving)
        map[nextRow][nextCol] = TILE_PLAYER;                              // I update the TILE_PLAYER
        return STATUS_TREASURE;

    }else if(map[nextRow][nextCol] == TILE_AMULET){                        // I cover the case moving onto amulet
        map[player.row][player.col] = TILE_OPEN;                           // I update the tile before we move to TILE_OPEN
        player.row = nextRow;                                             // current row become the nextRow (we are moving)
        player.col = nextCol;                                             // current column become the nextCol (we are moving)
        map[nextRow][nextCol] = TILE_PLAYER;                              // I update the TILE_PLAYER
        return STATUS_AMULET;

    }else if(map[nextRow][nextCol] == TILE_DOOR){                          // I cover the case moving onto door
        map[player.row][player.col] = TILE_OPEN;                           // I update the tile before we move to TILE_OPEN
        player.row = nextRow;                                             // current row become the nextRow (we are moving)
        player.col = nextCol;                                             // current column become the nextCol (we are moving)
        map[nextRow][nextCol] = TILE_PLAYER;                              // I update the TILE_PLAYER
        return STATUS_LEAVE;

    }else if((map[nextRow][nextCol] == TILE_EXIT)&&(player.treasure > 0)){   // I cover the case moving onto exit and has treasure
        map[player.row][player.col] = TILE_OPEN;                           // I update the tile before we move to TILE_OPEN
        player.row = nextRow;                                             // current row become the nextRow (we are moving)
        player.col = nextCol;                                             // current column become the nextCol (we are moving)
        map[nextRow][nextCol] = TILE_PLAYER;                              // I update the TILE_PLAYER
        return STATUS_ESCAPE;

    }else if((map[nextRow][nextCol] == TILE_EXIT)&&(player.treasure < 1)){    // I cover the case moving onto exit and has no treasure
        nextRow = player.row;                                                 // player cannot move, so nextRow is current row                                      
        nextCol = player.col;                                                 // and nextCol is current column
        return STATUS_STAY;

    }else if(map[nextRow][nextCol] == TILE_OPEN){
        map[player.row][player.col] = TILE_OPEN;                           // I update the tile before we move to TILE_OPEN
        player.row = nextRow;                                             // current row become the nextRow (we are moving)
        player.col = nextCol;                                             // current column become the nextCol (we are moving)
        map[nextRow][nextCol] = TILE_PLAYER;                              // I update the TILE_PLAYER
        return STATUS_MOVE;
    }

    cout << "non of the else-if statement executed in doPlayerMove function, error" << endl;
    return 6;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    for(int k = (player.row-1); k >= 0; k--){     // I'm checking the above of the adventurer
        if(map[k][player.col] == TILE_PILLAR){     // if there is a pillar checking will stop
            break;
        }else if(map[k][player.col] == TILE_MONSTER){  //if there is a monster 
            map[k][player.col] = TILE_OPEN;            // monster's previous location will be open_tile.
            map[k+1][player.col] = TILE_MONSTER;      //monster get closer (moving down)
        }                                              // I didn't break the for loop because if there is another monster above, it has to move too.
    }

    for(int l = (player.row+1); l < maxRow; l++){      // I'm checking the below of the adventurer
        if(map[l][player.col] == TILE_PILLAR){           // if there is a pillar checking will stop
            break;
        }else if(map[l][player.col] == TILE_MONSTER){  //if there is a monster 
            map[l][player.col] = TILE_OPEN;            // monster's previous location will be open_tile.
            map[l-1][player.col] = TILE_MONSTER;      //monster get closer (moving up)(also if there is a treasure or something like that it will be destroyed)
        }                                              // I didn't break the for loop because if there is another monster above, it has to move too.
    }

    for(int m = (player.col-1); m >= 0; m--){          //I'm checking the left side of the adventurer
        if(map[player.row][m] == TILE_PILLAR){         // if there is a pillar checking will stop
            break;
        }else if (map[player.row][m] == TILE_MONSTER){      // if there is a monster 
            map[player.row][m] = TILE_OPEN;                 // the monster's previous location will updated to tile_open
            map[player.row][m+1] = TILE_MONSTER;            //monster will move 1 step right (getting closer to adventurer)
        }                                                   // the for loop keep working there might be another monster in the same row.
    }

    for(int n = (player.col+1); n < maxCol; n++){          //I'm checking the right side of the adventurer
        if(map[player.row][n] == TILE_PILLAR){         // if there is a pillar checking will stop
            break;
        }else if (map[player.row][n] == TILE_MONSTER){      // if there is a monster 
            map[player.row][n] = TILE_OPEN;                 // the monster's previous location will updated to tile_open
            map[player.row][n-1] = TILE_MONSTER;            //monster will move 1 step left (getting closer to adventurer)
        }                                                   // the for loop keep working there might be another monster in the same row.
    }                                       
                                        // if the adventurer is at the one edge of the map, one of the for loop won't executed automatically.
    if (map[player.row][player.col] == TILE_MONSTER){
        return true;
    }else if (map[player.row][player.col] != TILE_MONSTER){
        return false;
    }
       
    cout << "In doMonsterMove function else if statement is not working, error" << endl;
    return false;
}
