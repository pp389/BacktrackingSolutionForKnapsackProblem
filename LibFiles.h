#pragma once

#include <fstream>

/**
* This function adds extension to file name if it's not present.
* @param fileName - name of file to check
* @return fileName with added extension if it was necessary
*/
std::string addExtensionIfNotPresent(std::string fileName);

/**
* This function opens specified file to read.
* @param file - reference to fstream object for our file
* @param fileName - name of file to open
*/
void openFile(std::fstream& file, std::string fileName);



