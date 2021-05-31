#include "Finder.h"
#include<iostream>


using namespace std;

void Finder::showFiles() {
    for (auto& it : files) {
        for (auto it2 = it.second.begin(); it2 != it.second.end(); ++it2)
            std::wcout << *it2 << std::endl;
    }
}

void Finder::showDirectories() {
    for (auto& it : directories) {
        for (auto it2 = it.second.begin(); it2 != it.second.end(); ++it2)
            std::wcout << *it2 << std::endl;
    }
}

void Finder::clear() {
    files.clear();
    directories.clear();
}

void Finder::getData(std::wstring& directory) {

    std::wstring aux = directory + L"\\*";
    WIN32_FIND_DATAW file;

    wrapper.hfile = FindFirstFileW(aux.c_str(), &file);

    if (wrapper.hfile != INVALID_HANDLE_VALUE)
    {
        std::vector<std::wstring> helper; // array of directories for recursive call

        do
        {
            if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if ((!lstrcmpW(file.cFileName, L".")) || (!lstrcmpW(file.cFileName, L"..")))
                    continue;
            }

            aux = directory + L"\\" + std::wstring(file.cFileName);

            if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                directories[std::wstring(file.cFileName)].push_back(aux); //we store in map the directory name and the path
                helper.push_back(aux);
            }
            else
                files[std::wstring(file.cFileName)].push_back(aux); ////we store in map the file name and the path

        } while (FindNextFileW(wrapper.hfile, &file));

        for (auto& it : helper)
            getData(it);
    }
}

void Finder::SearchFilesByWildcard(std::wstring& path)
{
    WIN32_FIND_DATA file;

    wrapper.hfile = FindFirstFile(path.c_str(), &file);
    if (wrapper.hfile == INVALID_HANDLE_VALUE)
    {
        cout << "Invalid input" << endl;
        return;
    }

    if (file.cFileName[0] != '.')
    {
        std::wcout << file.cFileName << std::endl;
    }

    while (FindNextFile(wrapper.hfile, &file))
    {
        if (file.cFileName[0] == '.')
        {
            continue;
        }

        std::wcout << file.cFileName << std::endl;
    }

    return;
}


void Finder::findFile(std::wstring& file) {

    std::map<std::wstring, std::vector<std::wstring>>::iterator it;
    it = files.find(file); // try to search for the file
    if (it != files.end()) { //if the file name exist in map
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            std::wcout << *it2 << std::endl; // print all the paths of the searched file
    }
    else
        std::wcout << "This file does not exist in this directory" << std::endl;
}

void Finder::findDirectory(std::wstring& folder) {

    std::map<std::wstring, std::vector<std::wstring>>::iterator it;
    it = directories.find(folder); // try to search for the directory
    if (it != directories.end()) { //if the name of the directory exist in the map
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            std::wcout << *it2 << std::endl;//print all the paths of the searched directory
    }
    else
        std::wcout << "This folder does not exist in this directory" << std::endl;
}

