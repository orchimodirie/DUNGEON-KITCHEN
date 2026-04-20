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
    MenuBox(int padAmount = 5) {
        padding = padAmount;
        terminalWidth = 80;
        terminalHeight = 24;
    }

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

    void draw(bool expectingInput = false) {
        //1. calculate the box width (ignore both special tokens)
        int maxlen= 0;
        if (title.length() > maxlen) maxlen = title.length();
        if (subtitle.length() > maxlen ) maxlen = subtitle.length();
        for (const string& opt : options) {
            if(opt != SEPARATOR_TOKEN && opt != EMPTY_TOKEN && opt.length() > maxlen) {
                maxlen = opt.length();
            }
        }
        int boxWidth = maxlen + (padding * 2 ) + 2;

        //2. calculate centering offsets
        int boxHeight = 4;
        if (!title.empty()) boxHeight += 2;
        if (!subtitle.empty()) boxHeight += 2;
        boxHeight += options.size();

        // calculating centering effects
        int yOffset = (terminalHeight - boxHeight) / 2;
        int xOffset = (terminalWidth - boxWidth) / 2;
        if (yOffset < 0) yOffset = 0;
        if (xOffset < 0) xOffset = 0;

        // setup spacing tools
        lastXOffset = xOffset;
        lastBoxHeight = boxHeight;
        lastYOffset = yOffset;

        string leftIndent(xOffset, ' ');
        string innerPad(padding, ' ');
        string emptyInnerLine = leftIndent + "|" + string(boxWidth - 2, ' ') + "|\n";
        string border = leftIndent + string(boxWidth, '=') + "\n";

        // start drawing
        for (int i = 0; i < yOffset; i++) cout << endl;

        cout << border;
        cout << emptyInnerLine;

        if (!title.empty()) {
            string rightPad((boxWidth - 2) - title.length() - padding, ' ');
            cout << leftIndent << "|" << innerPad << title << rightPad << "|" << endl;
            cout << emptyInnerLine;
        }

        if (!subtitle.empty()) {
            string rightPad((boxWidth - 2) - subtitle.length() - padding, ' ');
            cout << leftIndent << "|" << innerPad << subtitle << rightPad << "|" << endl;
            cout << emptyInnerLine;
        }

        // Draw Options, Separator, and Empty Lines
        for (const string& opt : options) {
            if (opt == SEPARATOR_TOKEN) {
                // Draw an horizontal line 
                cout<< leftIndent << "|" << string(boxWidth - 2, '=') << "|" <<endl;
            } else if (opt == EMPTY_TOKEN) {
                    // draw an empty line wth bordere
                    cout << leftIndent << "|" << string(boxWidth - 2, ' ') << "|" << endl;
            } else {
                // draw normal text
                string rightPad((boxWidth - 2) - opt.length() - padding, ' ');
                cout << leftIndent << "|" << innerPad << opt << rightPad << "|" << endl;
            }
        }

        cout << emptyInnerLine;
        cout << border;

        if(!expectingInput) {
        for (int i = 0; i < (terminalHeight - boxHeight - yOffset); i++) cout << endl;
        }
    }

    //
    int getUserInput (string promptText = "Choice: ") {
        int input;

        string leftIndent(lastXOffset, ' ');
        
        //
        cout << leftIndent << promptText;

        //
        cin >> input;
        //
        //
        int remainingLines = terminalHeight - lastBoxHeight - lastYOffset - 1;
        for (int i = 0; i < remainingLines; i++) cout << endl;
        
        return input;
    }

    void systemPause (string promptText = "Press [enter] to flee to menu") {

        string leftIndent(lastXOffset, ' ');

        cout << leftIndent << promptText;
        cin.get();
    
        int remainingLines = terminalHeight - lastBoxHeight - lastYOffset - 1;
        for (int i = 0; i < remainingLines; i++) cout << endl;
        
    }
};


#endif