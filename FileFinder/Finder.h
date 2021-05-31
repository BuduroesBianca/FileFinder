#pragma once
#include<Windows.h>
#include <iostream>
#include <string>
#include <vector>  
#include <map>


class Finder {

	std::map<std::wstring, std::vector<std::wstring>> files;
	std::map<std::wstring, std::vector<std::wstring>> directories;
	std::vector<std::wstring> filesWildCard;

	struct HandleWrapper {
		HANDLE hfile = INVALID_HANDLE_VALUE;
		~HandleWrapper() {
			if (hfile != INVALID_HANDLE_VALUE)
				FindClose(hfile);
		}
	} wrapper;

public:

	void showFiles(); //print files
	void showDirectories(); //print folders
	void clear();
	void getData(std::wstring& directory); //build the files map and directories map
	void SearchFilesByWildcard(std::wstring& wildcardPath); //list files found by wildcard search
	void findFile(std::wstring& directory); //search for a file
	void findDirectory(std::wstring& directory); //search for folder
};
