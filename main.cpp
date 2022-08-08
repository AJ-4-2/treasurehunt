//An old class project I did
//Everything was in one file by the teachers request

#include <iostream>
#include <Windows.h>
#include <vector>
#include <time.h>
#include <iomanip>

using namespace std;

//const int NUM_ROW = 40;
//const int NUM_COLS = 150;

//class for creating the canvas and drawing everything to it
class Canvas
{
public:
    //create the main playfield
    int col = 150;
    int row = 40;

    char canvas[150][40];

    void display();
    void zeroCanvas();
};
void Canvas::display()
{
   string rowStr;
    //draws the screen
    for (int county = 0; county < row; county++)
    {
        for (int countx = 0; countx < col; countx++)
        {
            //put the row into a string (much faster rendering speed this way almost like instant render for each frame)
            //using cout to do each individual character was slow and took a second to render the tiles
            rowStr += canvas[countx][county];
        }
        rowStr += '\n';
    }
    cout << rowStr;
}
//zero out the canvas and draw the border
//this clears out the array, filling the middle with space character and the border with the appropriate border characters
//filling the array with spaces is important because otherwise random memory stuff will render and the whole thing will be a mess.
void Canvas::zeroCanvas()
{
    for (int county = 0; county < row; county++)
    {
        for (int countx = 0; countx < col; countx++)
        {
            //top and bottom border
            if ((county == 0 || county == row - 1) && (countx != 0 && countx != col - 1))
            {
                canvas[countx][county] = 205;
            }
            //left and right border
            else if ((countx == 0 || countx == col - 1) && (county != 0 && county != row - 1))
            {
                canvas[countx][county] = 186;
            }

            //the next four if's are for the corners
            else if ((countx == 0 && county == 0))
            {
                canvas[countx][county] = 201;
            }
            else if ((countx == col - 1 && county == 0))
            {
                canvas[countx][county] = 187;
            }
            else if ((countx == 0 && county == row - 1))
            {
                canvas[countx][county] = 200;
            }
            else if ((countx == col - 1 && county == row - 1))
            {
                canvas[countx][county] = 188;
            }
            //default the rest to a space character.
            else
            {
                canvas[countx][county] = ' ';
            }
        }
    }
}

class Lock
{
public:
    string question = "";
    string answers[4];
    char answer;
    char input;
    int whichQuestion;
    bool correct = true;
    bool askQuestion();
    void getQuestion();
};
bool Lock::askQuestion()
{
    system ("CLS");
    correct = true;
    cout << "There seems to be a lock on this door.  You try to unlock it.\n\n";
    cout << question << "\n\n";
    for (int c = 0; c < 4; c++)
    {
        cout << answers[c] << "\n";
    }
    cin >> input;
    if (input != answer)
    {
        correct = false;
        system ("CLS");
    }
    return correct;
}
//sets the question for the lock
void Lock::getQuestion()
{
    if (whichQuestion == 0)
    {
        question = "What following c++ statement contains no error?";
        answers[0] = "1: cout << \"Hello world\" ";
        answers[1] = "2: output > \"Hello world\" ";
        answers[2] = "3: cout << \"Hello world\";";
        answers[3] = "4: consoleOut < \"Hello world\";";
        answer = '3';
    }
    else if (whichQuestion == 1)
    {
        question = "What symbol signifies the end of a c++ statement?";
        answers[0] = "1:  ?";
        answers[1] = "2:  #";
        answers[2] = "3:  *";
        answers[3] = "4:  ;";
        answer = '4';
    }
    else if (whichQuestion == 2)
    {
        question = "What is used to send output to the console?";
        answers[0] = "1:  cout";
        answers[1] = "2:  output";
        answers[2] = "3:  consoleOut";
        answers[3] = "4:  out";
        answer = '1';
    }
    else if (whichQuestion == 3)
    {
        question = "What is C++";
        answers[0] = "1:  A markup Language";
        answers[1] = "2:  A programming Language";
        answers[2] = "3:  A brand of floor cleaner";
        answers[3] = "4:  My grade for the class";
        answer = '2';
    }
    else if (whichQuestion == 4)
    {
        question = "What is used to mark the beginning of a string?";
        answers[0] = "1:  \'";
        answers[1] = "2:  \"";
        answers[2] = "3:  <";
        answers[3] = "4:  -";
        answer = '2';
    }
    else if (whichQuestion == 5)
    {
        question = "What is the modulus operator?";
        answers[0] = "1:  &";
        answers[1] = "2:  @";
        answers[2] = "3:  #";
        answers[3] = "4:  %";
        answer = '4';
    }
}
//class for the message handler
class Message
{
public:
    //char msgArray[32][10];
    vector<string> msgLog;
    void pushMsg(string);
    void msgDisplay();
    void prime();
};
void Message::pushMsg(string msg)
{
    msgLog.push_back(msg);
}
void Message::msgDisplay()
{
    int s = msgLog.size();
    for (int c = s - 1; c > (s - 15); c--)
    {
        cout << msgLog[c];
    }
}
void Message::prime()
{
    for (int c = 0; c < 15; c++)
    {
        msgLog.push_back("");
    }
}

//class for creating the player object
class Player
{
public:
    int x, y;
    int staminaMax = 100;
    int stamina = staminaMax;
    string name;
    bool indoors = false;
    bool gameWon = false;
    bool OutOfStamina = false;
    //This template is the only way I could find to pass the 2d array at all, never mind by reference.
    template <size_t size_x, size_t size_y>
    string movement(char (&level)[size_x][size_y], int, int);
};
//class function to handle the player movement, as well as collision detection and message handling for movement
//and movement based actions (walking into a wall, using a campfire, movement direction, and stamina status)
template <size_t size_x, size_t size_y>
string Player::movement(char (&level)[size_x][size_y], int deltaX, int deltaY)
{
    string msg = "";
    bool door = false;
    if ((level[x + deltaX][y + deltaY]) == ' ' || (level[x + deltaX][y + deltaY]) == '#')
    {
        if ((level[x + deltaX][y + deltaY]) == '#')
        {
            msg = " opened a door.\n";
            door = true;
        }
        if (deltaX == 0 && deltaY == 1)
        {
            if (!door)
            {
                msg = " moved south.\n";
            }
            y += 1;
        }
        else if (deltaX == 0 && deltaY == - 1)
        {
            if (!door)
            {
                msg = " moved north.\n";
            }
            y -= 1;
        }
        else if (deltaX == 1 && deltaY == 0)
        {
            if (!door)
            {
                msg = " moved east.\n";
            }
            x += 1;
        }
        else if (deltaX == - 1 && deltaY == 0)
        {
            if (!door)
            {
                msg = " moved west.\n";
            }
            x -= 1;
        }

        stamina -= 1;
        if (stamina == 75)
        {
            msg = " is starting to feel slightly weary.\n.\n";
        }
        else if (stamina == 50)
        {
            msg = " is starting to feel tired.  Perhaps they should find camp soon.\n";
        }
        else if (stamina == 25)
        {
            msg = " is feeling very tired. They should find a camp to rest right away.\n";
        }
        else if (stamina == 10)
        {
            msg = " is extremely exhausted.  If they don't find camp now they will surely perish.\n";
        }
    }
    else if ((level[x + deltaX][y + deltaY]) == 'T')
    {
        gameWon = true;
    }
    else if ((level[x + deltaX][y + deltaY]) == '*')
    {
        stamina = staminaMax;
        msg = " rested at a campfire.\n";
    }
    else
    {
        msg = " walked into a wall.\n";
    }
    return msg;
}



class Room
{
public:
    int xSize, ySize, xPos, yPos, doorX, doorY, treasureX, treasureY, roomNumber, question;
    bool visible = false;
    bool treasure = false;
    bool locked = false;
    Lock lock;
/*
    Room(int xS, int yS, int xP, int yP)
    {
        xSize = xS;
        ySize = yS;
        xPos = xP;
        yPos = yP;
    }
    */
    //lock the room
    void lockRoom();
    //function to write the room to the canvas
    template <size_t size_x, size_t size_y>
    void write(char (&level)[size_x][size_y]);
    template <size_t size_x, size_t size_y>
    void makeDoor(char (&level)[size_x][size_y]);
    void buryTreasure();
};
//lock the room, setting which question is going to be acked randomly.
void Room::lockRoom()
{
    DWORD countT = GetTickCount();
    srand (time(NULL) + countT);
    question = rand() % (6 + 0);
    lock.whichQuestion = question;
    lock.getQuestion();
    locked = true;
}
template <size_t size_x, size_t size_y>
void Room::write(char (&level)[size_x][size_y])
{
    //this iterates through the room parameters and matches them with the canvas coordinates, drawing the walls and writing it to the canvas.
    for (int countY = yPos; countY < (yPos + ySize); countY++)
    {
        for (int countX = xPos; countX < (xPos + xSize); countX++)
        {
            //top and bottom walls
            if ((countY == yPos || countY == (yPos + ySize - 1)) && (countX != xPos && countX != (xPos + xSize - 1)))
            {
                level[countX][countY] = 205;
            }
            //side walls
            else if ((countX == xPos || countX == (xPos + xSize - 1)) && (countY != yPos && countY != (yPos + ySize - 1)))
            {
                level[countX][countY] = 186;
            }
            //corners
            else if (countX == xPos && countY == yPos)
            {
                level[countX][countY] = 201;
            }
            else if (countX == (xPos + xSize - 1) && countY == yPos)
            {
                level[countX][countY] = 187;
            }
            else if (countX == xPos && countY == (yPos + ySize - 1))
            {
                level[countX][countY] = 200;
            }
            else if (countX == (xPos + xSize - 1) && countY == (yPos + ySize - 1))
            {
                level[countX][countY] = 188;
            }
            //floorinside
            else
            {
                if (visible)
                {
                    level[countX][countY] = ' ';
                }
                else
                {
                    level[countX][countY] = '.';
                }

            }
        }
    }
    if (visible)
    {
        if(treasure)
        {
            level[treasureX][treasureY] = 'T';
        }
    }
    //level[treasureX][treasureY] = 'T';
    level[doorX][doorY] = '#';

}
//makes the doors for each building/room
template <size_t size_x, size_t size_y>
void Room::makeDoor(char (&level)[size_x][size_y])
{
    DWORD countT = GetTickCount();
    srand (time(NULL) + countT);
    //0 = top, 1 = right, 2 = bottom, 3 = left
    int side = rand() % (4 + 0);
    if (side == 0)
    {
        srand (time(NULL) + countT);
        doorX = rand() % (xSize - 2) + (xPos + 1);
        doorY = yPos;
    }
    if (side == 1)
    {
        doorX = (xPos + xSize - 1);
        srand (time(NULL) + countT);
        doorY = rand() % (ySize - 2) + (yPos + 1);
    }
    if (side == 2)
    {
        srand (time(NULL) + countT);
        doorX = rand() % (xSize - 2) + (xPos + 1);
        doorY = (yPos + ySize - 1);
    }
    if (side == 3)
    {
        srand (time(NULL) + countT);
        doorX = xPos;
        doorY = rand() % (ySize - 2) + (yPos + 1);
    }
}
void Room::buryTreasure()
{
    treasure = true;
    DWORD countT = GetTickCount();
    srand (time(NULL) + countT);
    treasureX = rand() % (xSize - 2) + (xPos + 1);
    treasureY = rand() % (ySize - 2) + (yPos + 1);
}

class Campfire
{
public:
    int xPos, yPos;
    template <size_t size_x, size_t size_y>
    void write(char (&level)[size_x][size_y]);
};
template <size_t size_x, size_t size_y>
void Campfire::write(char (&level)[size_x][size_y])
{
    level[xPos][yPos] = '*';
}


//the class for the base level.  The array from this class goes unchanged after the level is generated
//and is applied right after zeroing the canvas, followed by everything else.
class Level
{
public:
    //int width = 150;
    //int height = 40;
    char level[150][45];
    //linked list were too confusing for me, so i created 2 vectors to just track coordinates,
    //one for x and one for y and they represent a list of "illegal" spaces that rooms cannot occupy.
    //this is to ensure that nothing intersects or goes out of bounds.
    //every time a room is created, every coordinate it occupies and the surrounding spaces are added to the list.
    //the surrounding spaces are included to ensure no doors get blocked, and the tresure lost with it. The border is also on this list
    vector<int> xForbid;
    vector<int> yForbid;
    vector<Room> rooms;
    vector<Campfire> camp;
    void forbidBorder();
    void createRoom(int);
    template <size_t size_x, size_t size_y>
    void lightFire(char (&level)[size_x][size_y], int);

    //r is the room count c is the camfire count
    Level (int r, int c)
    {
        rooms.resize(r);
        camp.resize(c);
    }
};

void Level::forbidBorder()
{
    for (int countY = 0; countY < 40; countY++)
    {
        for (int countX = 40; countX < 150; countX++)
        {
            if ((countY <= 1 || countY >= 38) || ((countX <= 1 || countX >= 148)))
            {
                xForbid.push_back(countX);
                yForbid.push_back(countY);
                //cout << xForbid[countX] << " " << yForbid[countY] << "    ";
            }
        }
    }
}
//sets random parameters for the room size and position.  The position starts at the top left
void Level::createRoom(int currentRoom)
{
    bool overlap = false;
    do
    {
        overlap = false;
        DWORD countT = GetTickCount();
        srand (time(NULL) + countT);
        rooms[currentRoom].xPos = rand() % 140 + 2;
        rooms[currentRoom].yPos = rand() % 27 + 2;
        rooms[currentRoom].xSize = rand() % 20 + 4;
        rooms[currentRoom].ySize = rand() % 7 + 4;

        for (int countY = rooms[currentRoom].yPos; countY < (rooms[currentRoom].yPos + rooms[currentRoom].ySize); countY++)
        {
            for (int countX = rooms[currentRoom].xPos; countX < (rooms[currentRoom].xPos + rooms[currentRoom].xSize); countX++)
            {
                for (int countF = 0; countF < yForbid.size(); countF++)
                {
                    if (countX == xForbid[countF] && countY == yForbid[countF])
                    {
                        overlap = true;
                    }
                }
            }
        }
        if (overlap == false)
        {
            for (int countY = rooms[currentRoom].yPos - 1; countY < (rooms[currentRoom].yPos + rooms[currentRoom].ySize + 1); countY++)
            {
                for (int countX = rooms[currentRoom].xPos -1 ; countX < (rooms[currentRoom].xPos + rooms[currentRoom].xSize + 1); countX++)
                {
                    yForbid.push_back(countY);
                    xForbid.push_back(countX);
                }
            }
        }
        //this forces random wait times to make the numbers a little more randimish so the buiildings don't render in a straight line and appear more random
        //I'm kinda proud of this one though its so simple.
        //srand (time(NULL) + countT);
        while (countT > GetTickCount() - (rand() % 113 + 77))
        {
            //cout << "loading Level";
        }
    }while(overlap);
}
template <size_t size_x, size_t size_y>
void Level::lightFire(char (&level)[size_x][size_y], int currentCamp)
{
    DWORD countT = GetTickCount();
    srand (time(NULL) + countT);
    bool overlap = false;
    do
    {
        overlap = false;
        camp[currentCamp].xPos = rand() % 148 + 1;
        camp[currentCamp].yPos = rand() % 43 + 1;
        for (int countF = 0; countF < yForbid.size(); countF++)
        {
            if (camp[currentCamp].xPos == xForbid[countF] && camp[currentCamp].xPos == yForbid[countF])
            {
                overlap = true;
            }
        }
        //camp[currentCamp]
        if (!overlap)
        {
            //this long if statement is to check is the space the camp is occupying is open, and if any of the surrounding 4 tiles are doors
            //so that they don't block your way inside
            if (level[camp[currentCamp].xPos][camp[currentCamp].yPos] == ' ' &&
                ((level[camp[currentCamp].xPos + 1][camp[currentCamp].yPos] != '#')&&(level[camp[currentCamp].xPos - 1][camp[currentCamp].yPos] != '#')&&(level[camp[currentCamp].xPos][camp[currentCamp].yPos + 1] != '#')&&(level[camp[currentCamp].xPos][camp[currentCamp].yPos - 1] != '#')))
            {
                xForbid.push_back(camp[currentCamp].xPos);
                yForbid.push_back(camp[currentCamp].yPos);
            }
            else
            {
                overlap = true;
            }
        }
        //forces a random amount of milliseconds for wait time between each campfire to increase randomization.
        while (countT > GetTickCount() - (rand() % 113 + 77))
        {
            //cout << "loading Level";
        }
    }while(overlap);

}


//prototype for sizing window function
void SetWindow(int, int);







int main()
{
    //Set the window size to display the entire map
    //first int is number of characters wide the console screen is and second is the number of lines
    SetWindow(151,61);
    //creates a handle to read the console input for the arrow key presses and esc to end the program
    HANDLE consInput = GetStdHandle(STD_INPUT_HANDLE);
    //handle to read the output for editing the color
    HANDLE consColor = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD Events = 0;     //event count
    DWORD EventsCount = 0; //events read from console

    //create the player and canvas objects, set the player position
    Player player;
    Canvas canvas;
    int roomCount;
    int numCampFires;
    int locked;
    int playerLastX, playerLastY;
    //variables for drawing the loading screen graphic
    int hashCount = 39;
    int spaceCount = 54;
    int spaceCountT = 73;
    int hashCountT = 1;
    bool lockFailed = false;
    string loadingGraphic;
    string loadingGraphicT;
    Message msg;
    string message = "";
    msg.prime();

    //randomization'
    DWORD countT = GetTickCount();
    srand (time(NULL) + GetTickCount());
    //randomize the number of rooms
    numCampFires = rand() % 5 + 8;
    roomCount = rand() % 5 + 5;//distr1(eng);

    //choose a random room for the treasure
    Level level1(roomCount, numCampFires);
    int tRoom = rand() % roomCount + 0;


    //default player starting point
    player.x = 1;
    player.y = 1;

    //the next few lines are the pre-load
    //clear the canvas
    canvas.zeroCanvas();
    //adds the border coordinates to a forbidden coordinate list for the room generation to reference
    level1.forbidBorder();



    //clear the screen
    system ("CLS");

    //display game tutorial and ask the player their name
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
    << "                                             You are an explorer in the year 3342, scaveging ancient cities.\n"
    << "                                              You are to find out the building with the treasure 'T' in it.\n\n"
    << "                                    Use the arrow keys to explore.  Watch your stamina, for if it runs out, you'll die.\n"
    << "                                                  Rest at camps marked with '*' to restore your stamina.\n\n"
    << "                                                        Now scavenger, I must ask: what is your name? \n\n"
    << "                                                                          ";
    cin >> player.name;

    //draw the loading screen, and generate the level
    for (int rCount = 0; rCount < roomCount; rCount++)
    {
        while (hashCountT <= 39)
        {
            for (int sCount = 0; sCount < spaceCountT; sCount++)
            {
                loadingGraphicT += ' ';
            }
            for (int hCount = 0; hCount < hashCountT; hCount++)
            {
                loadingGraphicT += '#';
            }
            loadingGraphicT += '\n';
            spaceCountT--;
            hashCountT += 2;
        }
        cout << "\n\n\n\n\n";
        cout << loadingGraphicT;
        cout << "                                                     #####                               #####\n";
        cout << "                                                    #####                                 #####\n";
        cout << "                                                   #####                                   #####\n";
        cout << "                                                  ######          GENERATING CITY          ######\n";
        cout << "                                                 #######                                   #######\n";
        cout << "                                                ########                                   ########\n";
        cout << "                                                 #######                                   #######\n";
        cout << "                                                  ######            "<< setfill('0') << setw(2) << rCount << "/" << roomCount << " rooms            ######\n";
        cout << "                                                   #####                                   #####\n";
        cout << "                                                    #####                                 #####\n";
        cout << "                                                     #####                               #####\n";
        while (hashCount >= 1)
        {
            for (int sCount = 0; sCount < spaceCount; sCount++)
            {
                loadingGraphic += ' ';

            }
            for (int hCount = 0; hCount < hashCount; hCount++)
            {
                loadingGraphic += '#';
            }
            loadingGraphic += '\n';
            spaceCount++;
            hashCount -= 2;
        }
    cout << loadingGraphic;
    cout << "treasure room is room number: " << tRoom << endl;
    cout << "Number of campfires: " << numCampFires;
        //actually generate the rooms here
        level1.createRoom(rCount);
        level1.rooms[rCount].makeDoor(canvas.canvas);
        level1.rooms[rCount].roomNumber = rCount;
        locked = rand() % 10 + 0;
        //randomly decides if the room is locked, 30% chance
        if (locked < 5)
        {
            level1.rooms[rCount].lockRoom();
        }
        //level1.
        system ("CLS");//clear the output
    }
    //put the treasure in a random location in the treasure room and lock the room
    level1.rooms[tRoom].buryTreasure();
    level1.rooms[tRoom].lockRoom();
    //level1.rooms[tRoom].
    //write the rooms to the canvas
    for (int rCount = 0; rCount < roomCount; rCount++)
    {
        level1.rooms[rCount].write(canvas.canvas);
    }

    for (int countC = 0; countC < numCampFires; countC++)
    {
        //cout << countC << endl;
        level1.lightFire(canvas.canvas, countC);
        level1.camp[countC].write(canvas.canvas);
        //cout << "camp " << countC << " x: " << level1.camp[countC].xPos << endl;
    }

    //set player starting point.  2 is for the smiley face icon
    canvas.canvas[player.x][player.y] = 2;
    //draw the screen
    //cout << level1.camp.size() << endl;
    canvas.display();
    cout << "\n\n" << "STAMINA: " << player.stamina << "\n";

    bool running = true;

    //main loop
    while(running)
        {

        //gets the systems current "event" count
        GetNumberOfConsoleInputEvents(consInput, &Events);
        //when an event happens, run this if
        if(Events != 0)
            {
            //create event buffer the size of how many Events
            INPUT_RECORD eventBuffer[Events];

            //fills the event buffer with the events and saves count in EventsCount
            ReadConsoleInput(consInput, eventBuffer, Events, &EventsCount);

            //loop through the event buffer using the saved count
            for(DWORD i = 0; i < EventsCount; ++i)
                {
                //check if event[i] is a key event && if so is a press not a release
                if(eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown)
                    {
                    //check if the key press was an arrow key, space, or esc, and defaults for any other key
                    switch(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode)
                    {
                        case VK_LEFT:
                            //SetConsoleTextAttribute(consColor, 10);
                            msg.pushMsg(player.name + player.movement(canvas.canvas, -1, 0));
                            //cout << "left ";// << endl;//these outputs are just for testing
                            break;

                        case VK_RIGHT:
                            //SetConsoleTextAttribute(consColor, 11);
                            msg.pushMsg(player.name + player.movement(canvas.canvas, 1, 0));
                            break;

                        case VK_UP:
                            //SetConsoleTextAttribute(consColor, 12);
                            //player.moveUp(canvas.canvas);
                            //message = player.name + " moved north\n";
                            msg.pushMsg(player.name + player.movement(canvas.canvas, 0, -1));
                            //msg.pushMsg(message);
                            break;

                        case VK_DOWN:
                            //SetConsoleTextAttribute(consColor, 13);
                            //player.moveDown(canvas.canvas);
                            //message = player.name + " moved south\n";
                            msg.pushMsg(player.name + player.movement(canvas.canvas, 0, 1));
                            break;

                        case VK_SPACE:
                            //SetConsoleTextAttribute(consColor, 14);
                            break;

                        case VK_ESCAPE:
                            //SetConsoleTextAttribute(consColor, 7);
                            cout<< "escape" << endl;
                            running = false;
                            break;

                        default: //when other keys are pressed
                            //SetConsoleTextAttribute(consColor, 7);
                            cout<< "other key" << endl;
                            break;
                        }
                        //these next few lines are the update.
                        canvas.zeroCanvas();
                        //room visibility detection code.  This should go in the player or the room class eventually but its here for now
                        for (int rCount = 0; rCount < roomCount; rCount++)
                        {
                            for (int countY = level1.rooms[rCount].yPos; countY < (level1.rooms[rCount].yPos + level1.rooms[rCount].ySize); countY++)
                            {
                                for (int countX = level1.rooms[rCount].xPos; countX < (level1.rooms[rCount].xPos + level1.rooms[rCount].xSize); countX++)
                                {
                                    if ((player.x == countX) && (player.y == countY))
                                    {
                                        player.indoors = true;
                                        if (level1.rooms[rCount].locked)
                                        {
                                            if (!level1.rooms[rCount].lock.askQuestion())
                                            {
                                                player.stamina -= 25;
                                                player.x = playerLastX;
                                                player.y = playerLastY;
                                                lockFailed = true;
                                                player.indoors = false;
                                            }
                                            else
                                            {
                                                level1.rooms[rCount].locked = false;
                                                lockFailed = false;

                                            }
                                        }
                                    }
                                }
                            }
                            if (!lockFailed)
                            {
                                if (player.indoors == true)
                                {
                                    level1.rooms[rCount].visible = true;
                                }
                                else
                                {
                                    level1.rooms[rCount].visible = false;
                                }
                            }
                            player.indoors = false;
                        }
                        //write the rooms to the canvas
                        for (int rCount = 0; rCount < roomCount; rCount++)
                        {
                            level1.rooms[rCount].write(canvas.canvas);
                        }
                        //write the campfires to the canvas
                        for (int countC = 0; countC < numCampFires; countC++)
                        {
                            level1.camp[countC].write(canvas.canvas);
                        }

                        //Set player position
                        canvas.canvas[player.x][player.y] = 2;
                        //clear the screen for the next frame
                        system ("CLS");
                        //draw the level
                        canvas.display();
                        //stamina display
                        cout << "\n\n" << "STAMINA: " << player.stamina << "\n";
                        msg.msgDisplay();
                        //cout << "\n\n" << message;
                        if (player.gameWon == true)
                        {
                            system ("CLS");
                            cout << "Congratulations you have found the treasure!!!!!\n\n\n" << "Press enter to end the game ";
                            cin.ignore(1, '\n');
                            cin.get();
                            running = false;
                        }
                        else if (player.stamina <= 0)
                        {
                            system ("CLS");
                            cout << "You have run out of stamina and died a terrible death.  Your soul shall wither into nothingness and you legacy, forgotten.\n\n\n"
                            << "Press enter to end the game ";
                            cin.ignore(1, '\n');
                            cin.get();
                            running = false;
                        }
                        playerLastX = player.x;
                        playerLastY = player.y;
                    }
                } //end EventsRead loop
            }
        } //end main loop
    return 0;
}

void SetWindow(int Width, int Height)
    {
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    //the minus 1 forces the console window to be just under the buffer size, which makes it start maximized. Otherwise, it starts as a small window that you must maximize
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);      //get Handle
    SetConsoleScreenBufferSize(out, coord);            //set Buffer Size
    SetConsoleWindowInfo(out, TRUE, &Rect);            //set Window Size
    }





