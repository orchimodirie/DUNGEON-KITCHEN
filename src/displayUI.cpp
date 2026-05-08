#include "displayUI.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

MenuBox::MenuBox(int padAmmount ) {
    padding = padAmmount;
    terminalWidth = 80;
    terminalHeight = 24;
}

void MenuBox::draw(bool expectingInput) {
      int maxlen= 0;

      // calculate which has the maxlen, subtitle or title
        if (title.length() > maxlen) maxlen = title.length();
        if (subtitle.length() > maxlen ) maxlen = subtitle.length();
        for (const string& opt : options) {
            if(opt != SEPARATOR_TOKEN && opt != EMPTY_TOKEN && opt.length() > maxlen) {
                maxlen = opt.length();
            }
        }
        int boxWidth = maxlen + (padding * 2 ) + 2;

        // calculate centering offsets
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

int MenuBox::getUserInput (string promptText) {
    int input;
    string leftIndent(lastXOffset, ' ');
        
    cout << leftIndent << promptText << flush;

    #ifdef __EMSCRIPTEN__
    emscripten_sleep(16); 
    #endif

    // THE FIX: Use getline for clean reads
    string rawInput;
    getline(cin, rawInput);
    
    // THE FIX: Revive cin if the user clicked "Cancel" (EOF)
    if (cin.fail() || cin.eof()) {
        cin.clear();
        input = -1; // Default to invalid input so game doesn't crash
    } else {
        try {
            input = stoi(rawInput);
        } catch (...) {
            input = -1;
        }
    }
    
    cout << input << endl; // Echo
        
    int remainingLines = terminalHeight - lastBoxHeight - lastYOffset - 1;
    for (int i = 0; i < remainingLines; i++) cout << endl;
        
    return input;
}

void MenuBox::systemPause(string promptText) {
    string leftIndent(lastXOffset, ' ');

    cout << leftIndent << promptText << flush;
    
    #ifdef __EMSCRIPTEN__
    emscripten_sleep(16); 
    #endif

    // THE FIX: Use getline and clear for the pause as well
    string dummy;
    getline(cin, dummy);
    
    if (cin.fail() || cin.eof()) {
        cin.clear();
    }
    
    int remainingLines = terminalHeight - lastBoxHeight - lastYOffset - 1;
    for (int i = 0; i < remainingLines; i++) cout << endl;
}