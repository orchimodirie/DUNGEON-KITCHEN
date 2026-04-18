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
    vector <string> options;
    int padding;

    int terminalWidth;
    int terminalHeight;

    //hidden tolesm fo special formatting
    const string SEPARATOR_TOKEN = "<SEPARATOR>";
    const string EMPTY_TOKEN = "<EMPTY>";

public:
    MenuBox(int padAmount = 5) {
        padding = padAmount;
        terminalWidth = 80;
        terminalHeight = 24;
    }

    void setResoultion (int width, int height) {
        terminalWidth = width;
        terminalHeight = height;
    }

    void setTitle(string T) {title = T; }
    void setSubtitle (string s) {subtitle = s;}

    // add content methods
    void addOptions (string opt) {options.push_back(opt);}
    void addSeparator () { options.push_back(SEPARATOR_TOKEN);}
    void addEmptyLine () { options.push_back(EMPTY_TOKEN);}

    void draw() {
        //1. calculate the box width (ignore both special tokens)
        int maxlen= 0;
        if (title.length() > maxlen) maxlen = title.length();
        if(subtitle.length() > maxlen ) maxlen = title.length();
        for(const string& opt : options) {
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
        int xOffset = (terminalHeight - boxWidth) / 2;
        if (yOffset < 0) yOffset = 0;
        if (xOffset < 0) xOffset = 0;

        // setup spacing tools
        string leftIndent(xOffset, ' ');
        string innerPad(padding, ' ');
        string emptyInnerLine = leftIndent + "|" + string(boxWidth - 2, ' ') + "|\n";
        string border = leftIndent + string(boxWidth, '=') + "\n";
        

    }

   





};










#endif