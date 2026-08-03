// ============================================================================
// main.cpp
// Main point for the OS
// This file starts up the custom shell interface
// ============================================================================

#include "CustomShell.h"

// ============================================================================
// MAIN FUNCTION
// Creates the shell and starts the session
// Parameters: none 
// Returns: 0 if successful
// ============================================================================
int main() {
    // Create and run the custom shell
    CustomShell shell;
    shell.run();
    
    return 0;
}