#ifndef dataclayplugin_h__
#define dataclayplugin_h__

#include <Python.h>
#include <wchar.h>
#include <stdio.h>
#include <fcntl.h>

extern PyObject *pFile;
extern wchar_t* wPathToScript;
extern char* dict[1000];
extern int pos_dict;
extern int free_dict[1001];

//Description: Start the connection with dataclay, with the client, with file system
//Requirements:
//  -alias  : Name given to dataclay. 
//              If (this name already existed in dataclay) -> It will restore the file system.
//              Else -> A new file system will be created
//Response: --
void dataclay_plugin(const char* alias, const char* lib_path);


//Description: Adds the path to the dataclay-plugin opened files file system
//Requirements:
//  -path   : Path to the file  
//  -flags  : Flags (will not be used)
//  -mode   : Mode (will not be used)
//Response: Integer representing the file descriptor
int dataclay_open(char* path, int flags, unsigned int mode);


//Description: Closes the dataclay-plugin file with file descriptor == fd
//Requirements:
//  -fd     : Integer representing the file descriptor you need to close
//Response: --
void dataclay_close(int fd);


//Description: Reads content from a file and store it in the buffer
//Requirements:
/*  -fd     : Path to the file you will read from
    -buf    : Position at the buffer you will start writting from 
    -count  : Number of characters you will read from the file
    -offset : Position from the file you will start reading from
*/
//Response: --
int dataclay_pread(int fd, char* buf, int count, int offset);


//Description: Writes content from the buffer to a file
//Requirements: 
/*  -fd     : Path to the file you will write to
    -buf    : Position at the buffer you will start reading from 
    -count  : Number of characters you will write to the file
    -offset : Position from the file you will start writing from
*/
//Response: --
int dataclay_pwrite(int fd, const char* buf, int count, int offset);


//Description: Closes the file system and the connection with dataclay
//Requirements: --
//Response: --
void dataclay_plugin_close();

#endif  // dataclayplugin_h__
