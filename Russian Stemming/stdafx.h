#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

typedef struct {
	std::string str;
	int n;
} stringNo;

typedef std::map<std::string, std::vector<stringNo>> textmap;