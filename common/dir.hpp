#ifndef DIR_HPP
#define DIR_HPP

#include <stdio.h>  /* defines FILENAME_MAX */
#include<iostream>

#ifdef WINDOWS
	#include <direct.h>
	#define getCurrentDir _getcwd
#else
	#include <unistd.h>
	#define getCurrentDir getcwd
#endif

std::string getCurrentWorkingDir();

#endif // DIR_HPP
