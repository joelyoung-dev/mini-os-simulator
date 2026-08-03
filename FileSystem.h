// ============================================================================
// FileSystem.h
// Header file for File System class
// Implements a simple virtual file system
// ============================================================================

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <map>
#include <fstream>

using namespace std;

// ============================================================================
// FILE STRUCTURE
// Represents a file in our virtual file system
// Contains the file name, content, size, and creation timestamp
// ============================================================================
struct File {
    string fileName;        // Name of the file
    string content;         // What's stored in the file
    int fileSize;          // Size in bytes
    string creationTime;   // When the file was created
    
    // Default constructor
    File() {
        fileName = "";
        content = "";
        fileSize = 0;
        creationTime = "";
    }
    
    // Constructor to create a new file
    // Parameters: name - filename
    //          data - initial content
    File(string name, string data);
};

// ============================================================================
// FILE SYSTEM CLASS
// Implements a simple virtual file system
// Supports creating, reading, writing, and deleting files
// All files are stored in memory 
// ============================================================================
class FileSystem {
private:
    map<string, File> files;     // Storage for all files
    ofstream logFile;            // Log file for tracking operations
    
public:
    // Constructor: Initialize the file system and open log file
    // Parameters: none
    FileSystem();
    
    // Destructor: Close log file when file system is destroyed
    ~FileSystem();
    
    // Create a new file
    // Parameters: fileName - name for the new file
    //            content - initial content to put in the file
    // Returns: true if created successfully, false if file already exists
    bool createFile(string fileName, string content);
    
    // Read and display a file's contents
    // Parameters: fileName - name of file to read
    // Returns: nothing
    void readFile(string fileName);
    
    // Write new content to an existing file 
    // Parameters: fileName - which file to write to
    //            newContent - new content to put in the file
    // Returns: true if successful, false if file doesn't exist
    bool writeFile(string fileName, string newContent);
    
    // Delete a file from the file system
    // Parameters: fileName - name of file to delete
    // Returns: true if deleted, false if file doesn't exist
    bool deleteFile(string fileName);
    
    // List all files in the file system
    // Parameters: none
    // Returns: nothing
    void listFiles();
};

#endif // FILESYSTEM_H