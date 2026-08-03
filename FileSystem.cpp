// ============================================================================
// FileSystem.cpp
// Implementation file for File System class
// Contains the actual code for file operations
// ============================================================================

#include "FileSystem.h"
#include <iostream>
#include <ctime>

using namespace std;

// Constructor for File structure
// Parameters: name - filename
//            data - initial content
File::File(string name, string data) {
    fileName = name;
    content = data;
    fileSize = data.length();
    
    // Get current time for creation timestamp
    time_t now = time(0);
    char* dt = ctime(&now);
    creationTime = string(dt);
}

// Constructor: Initialize the file system and open log file
// Parameters: none
// Returns: nothing 
FileSystem::FileSystem() {
    logFile.open("filesystem_log.txt", ios::app);
    logFile << "\n=== File System Session Started ===" << endl;
    
    // Get current time
    time_t now = time(0);
    char* dt = ctime(&now);
    logFile << "Start Time: " << dt << endl;
    
    cout << "[FILESYSTEM] Initialized virtual file system" << endl;
}

// Destructor: Close log file when file system is destroyed
FileSystem::~FileSystem() {
    logFile << "=== File System Session Ended ===" << endl;
    logFile.close();
}

// Create a new file
// Parameters: fileName - name for the new file
//            content - initial content to put in the file
// Returns: true if created successfully and false if file already exists
bool FileSystem::createFile(string fileName, string content) {
    cout << "\n[FILESYSTEM] Creating file: " << fileName << endl;
    
    // Check if file already exists
    if (files.find(fileName) != files.end()) {
        cout << "  -> ERROR: File already exists!" << endl;
        logFile << "Failed to create " << fileName << " - already exists" << endl;
        return false;
    }
    
    // Create new file
    File newFile(fileName, content);
    files[fileName] = newFile;
    
    cout << "  -> File created successfully" << endl;
    cout << "  -> Size: " << newFile.fileSize << " bytes" << endl;
    
    // Log this operation
    logFile << "Created file: " << fileName 
            << " (Size: " << newFile.fileSize << " bytes)" << endl;
    
    return true;
}

// Read and display a files contents
// Parameters: fileName - name of file to read
// Returns: nothing
void FileSystem::readFile(string fileName) {
    cout << "\n[FILESYSTEM] Reading file: " << fileName << endl;
    
    // Check if file exists
    if (files.find(fileName) == files.end()) {
        cout << "  -> ERROR: File not found!" << endl;
        logFile << "Failed to read " << fileName << " - not found" << endl;
        return;
    }
    
    // Get the file and display its contents
    File theFile = files[fileName];
    cout << "\n--- File Contents ---" << endl;
    cout << "Name: " << theFile.fileName << endl;
    cout << "Size: " << theFile.fileSize << " bytes" << endl;
    cout << "Created: " << theFile.creationTime;
    cout << "\nContent:\n" << theFile.content << endl;
    cout << "--- End of File ---\n" << endl;
    
    logFile << "Read file: " << fileName << endl;
}

// Write new content to an existing file 
// Parameters: fileName - which file to write to
//            newContent - new content to put in the file
// Returns: true if successful, false if file doesn't exist
bool FileSystem::writeFile(string fileName, string newContent) {
    cout << "\n[FILESYSTEM] Writing to file: " << fileName << endl;
    
    // Check if file exists
    if (files.find(fileName) == files.end()) {
        cout << "  -> ERROR: File not found!" << endl;
        logFile << "Failed to write " << fileName << " - not found" << endl;
        return false;
    }
    
    // Update the file's content
    files[fileName].content = newContent;
    files[fileName].fileSize = newContent.length();
    
    cout << "  -> File updated successfully" << endl;
    cout << "  -> New size: " << files[fileName].fileSize << " bytes" << endl;
    
    logFile << "Modified file: " << fileName 
            << " (New size: " << files[fileName].fileSize << " bytes)" << endl;
    
    return true;
}

// Delete a file from the file system
// Parameters: fileName - name of file to delete
// Returns: true if deleted, false if file doesn't exist
bool FileSystem::deleteFile(string fileName) {
    cout << "\n[FILESYSTEM] Deleting file: " << fileName << endl;
    
    // Check if file exists
    if (files.find(fileName) == files.end()) {
        cout << "  -> ERROR: File not found!" << endl;
        logFile << "Failed to delete " << fileName << " - not found" << endl;
        return false;
    }
    
    // Remove the file
    files.erase(fileName);
    
    cout << "  -> File deleted successfully" << endl;
    logFile << "Deleted file: " << fileName << endl;
    
    return true;
}

// List all files in the file system
// Parameters: none
// Returns: nothing
void FileSystem::listFiles() {
    cout << "\n--- File System Contents ---" << endl;
    
    if (files.empty()) {
        cout << "No files in file system" << endl;
        return;
    }
    
    cout << "Total files: " << files.size() << endl << endl;
    
    // Loop through all files and display their info
    for (map<string, File>::iterator it = files.begin(); 
         it != files.end(); it = std::next(it, 1)) {
        
        File currentFile = it->second;
        cout << "File: " << currentFile.fileName << endl;
        cout << "  Size: " << currentFile.fileSize << " bytes" << endl;
        cout << "  Created: " << currentFile.creationTime;
        cout << endl;
    }
}