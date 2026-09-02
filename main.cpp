#include <iostream>
#include <string>

// Ilnur Sultanov (C) 2026

// 02 Sept 2026: This is only a boilerplate code that I'm planning to rework later

using namespace std;

const string CLEAR_SCREEN = "\033[2J";
const string RESET        = "\033[0m";
const string MOVE_HOME    = "\033[H";
const string HIDE_CURSOR  = "\033[?25l";
const string SHOW_CURSOR  = "\033[?25h";

const string DOS_COLOR = "\033[93;44m";

const string DEFAULT_PROJECT_NAME = "Unnamed project";

string projectName;

struct Layer {
    int value;
    bool visibility;
};

struct Position2D {
    int x;
    int y;
};

class Panel {
    public:
        Panel(Position2D start, Position2D end, string color, int layerValue)
        : startPos(start), endPos(end), color(color), layer{ layerValue, true} {}

        void draw() {
            moveCursor(x0, y0);
            cout << "+";

            for (int x = x0 + 1; x < x1; x++)
                cout << "-";

            cout << "+";

            for (int y = y0 + 1; y < y1; y++)
            {
                moveCursor(x0, y);
                cout << "|";

                for (int x = x0 + 1; x < x1; x++)
                    cout << " ";

                cout << "|";
            }

            moveCursor(x0, y1);
            cout << "+";

            for (int x = x0 + 1; x < x1; x++)
                cout << "-";

            cout << "+";
        }

    private:
        Layer layer;
        Position2D startPos;
        Position2D endPos;
        string color;
};

struct ToolbarButton {
    Layer layer;
    string caption;


};

struct Toolbar {
};

void moveCursor(int x, int y)
{
    cout << "\033[" << y << ";" << x << "H";
}

void init()
{
    // settings dos colors
    cout << DOS_COLOR;
    cout << CLEAR_SCREEN;
    cout << MOVE_HOME;
    cout << HIDE_CURSOR;
}

void shutdown()
{
    cout << RESET;
    cout << SHOW_CURSOR;
    cout << CLEAR_SCREEN;
    cout << MOVE_HOME;
}

int getCaptionDistance(string inputText) {
    return inputText.length() + 2;
}

void drawToolbarButton(string buttonText) {

}

void drawSubToolbar() {
    // we need to use layers to draw subtoolbar in front of the regular toolbar imo
}

void drawToolbar() {
    // firstly we need to draw toolbar button and then put them in an array
    int currentBtn = 0;

}


void drawUi() {
    // Main DOS window
    makeWindow({5, 3}, {75, 22});

    // draw toolbar
    drawToolbar();

    moveCursor(30, 3);
    cout << "[ ";
    if (projectName.empty()) {
        cout << "*";
    }
    cout << projectName << " ]";

    // moveCursor(8, 4);
    // cout << "File";

    // moveCursor(15, 4);
    // cout << "Edit";

    // moveCursor(22, 4);
    // cout << "Options";

    // moveCursor(32, 4);
    // cout << "Help";
}

int main()
{
    init();

    while (true) {
        drawUi();

        moveCursor(8, 9);
        cout << "Welcome to the TermDRAW! Easy-to-use terminal drawing tool";
        moveCursor(8, 12);
        cout << "Made by Ilnur Sultanov (c) 2026";

        cout.flush();

        cin.get();
    }

    shutdown();

    return 0;
}
