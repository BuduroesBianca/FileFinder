#include "Finder.h"
#include<iostream>
#include<string>
#include<exception>

using namespace std;


void processingInput(string& input, wstring& path, char& type, wstring& name, int& wildcard, int& verifyCommand) {


    //find the path
    string test = input.substr(0, 4); // a correct "find" command should have 4 characters
    if (test != "find") { //verify if the command "find" is correct
        return;
    }
    else {
        verifyCommand = 1; //command "find" is correct
    }

    test = input.substr(5, input.size() - 5); //skip the already processed part
    input = test;

    int i = 1;
    if (test[0] == '"') {
        while (test[i] != '"' && i < test.size()) {
            path += test[i];
            i++;
        }
        i++;
    }
    else if (test[0] == '.')
        path = L"C:\\"; // default path

    i++;

    //if we still have input 
    if (i < test.size()) {
        test = test.substr(i, test.size() - i);
        input = test;
    }
    else {
        return;
    }

    //find the type of file
    string verif = test.substr(0, 5); // a correct "-type" command should have 5 characters

    if (verif != "-type") {
        return;
    }

    test = test.substr(6, test.size() - 6); //skip the already processed part
    input = test;

    i = 1;
    if (test[0] == 'f')
        type = 'f';
    else if (test[0] == 'd')
        type = 'd';
    else {
        return;
    }
    i++;

    //if we still have input
    if (i < test.size()) {
        test = test.substr(i, test.size() - i);
        input = test;
    }
    else {
        return;
    }

    //find the name of the file
    verif = test.substr(0, 5); // a correct "-name" command should have 5 characters

    if (verif != "-name") {

        return;
    }

    test = test.substr(6, test.size() - 6); //skip the already processed part
    input = test;


    if (test.size() < 2) {
        return;
    }

    i = 1;
    if (test[0] == '"') {
        while (test[i] != '"' && i < test.size()) {
            name += test[i];
            if (test[i] == '*')
                wildcard = 1;
            i++;
        }
        i++;
    }
    else {
        return;
    }

}

int main() {

    string input;
    Finder finder = Finder();
    cout << "This simulation begins." << endl;
    char response = 'Y';
    int ok;
    do {

        int wildcard = 0;
        int verifyCommand = 0;
        wstring path = L"";
        char type = NULL;
        wstring name = L"";

        ok = 0;
        int v = 1;

        while (ok == 0)
        {
            try
            {
                getline(cin >> ws, input);
                processingInput(input, path, type, name, wildcard, verifyCommand);

                if (verifyCommand != 1 || path == L"" || (input.size() > (path.size() + 2) && type != 'f' && type != 'd'))
                {
                    throw v;
                }
                else
                    ok = 1;
            }
            catch (int)
            {
                cout << "This is not a valid command";
            }
        }

        finder.clear(); //we clear the maps so we can start again on a new find command
        finder.getData(path);

        //if it s a type file
        if (type == 'f') {
            if (name != L"") {
                if (wildcard == 0)
                    finder.findFile(name);
                else if (wildcard == 1) {
                    finder.SearchFilesByWildcard(name);
                }
            }
            else
                finder.showFiles();
        }
        //if it s a type directory
        else if (type == 'd') {
            if (name != L"")
                finder.findDirectory(name);
            else
                finder.showDirectories();
        }
        else {
            finder.showDirectories();
            finder.showFiles();
        }


        cout << "Do you want to try again? -> ";
        ok = 0;
        while (ok == 0)
        {
            try
            {
                cin >> response;
                if (response != 'Y' && response != 'N' && response != 'y' && response != 'n')
                {
                    throw response;
                }
                else
                    ok = 1;
            }
            catch (char)
            {
                cout << "This is not a valid option" << endl;
            }
        }

    } while (response == 'Y' || response == 'y');

    return 0;
}


