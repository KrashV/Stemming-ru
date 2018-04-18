#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

typedef struct {
	std::wstring wstr;
	int n;
} wstringNo;

typedef std::map<std::wstring, std::vector<wstringNo>> textmap;