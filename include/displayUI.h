#ifndef DISPLAYUI_H
#define DISPLAYUI_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class MenuBox {
private:
    string title;
    string subtitle;
    vector<string> options;
    int padding;

    int terminalWidth;
    int terminalHeight;

    //hidden tolesm fo special formatting
    const string SEPARATOR_TOKEN = "<SEPARATOR>";
    const string EMPTY_TOKEN = "<EMPTY>";

    // 
    int lastXOffset;
    int lastBoxHeight;
    int lastYOffset;
public:
    MenuBox(int padAmmount = 5);

    void setResolution(int width, int height) {
        terminalWidth = width;
        terminalHeight = height;
    }

    void setTitle(string t) { title = t; }
    void setSubtitle(string s) { subtitle = s; }

    // add content methods
    void addOption (string opt) {options.push_back(opt);}
    void addSeparator () { options.push_back(SEPARATOR_TOKEN);}
    void addEmptyLine () { options.push_back(EMPTY_TOKEN);}

    void draw(bool expectingInput = false);

    int getUserInput (string promptText = "Choice: ");
    void systemPause (string promptText = "Press [enter] to flee to menu");
};


#endif