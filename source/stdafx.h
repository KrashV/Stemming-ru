/**
* \file
* \brief Header with structures, that used in algorithm
*/
#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

/**
* \brief Structure of stemms
*
* \param wstr Name of stemm
* \param n Count of stemms with this name
*/
typedef struct {
	std::wstring wstr;
	int n;
} wstringNo;

/**
* \brief Map, there the key is a stemm and the value its an array of words with this stemm
*/
typedef std::map<std::wstring, std::vector<wstringNo>> textmap;