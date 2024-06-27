#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
#define MAX_LINE_LENGTH 1024 
 
void grep(const char *pattern, FILE *file); 
 
int main(int argc, char *argv[]) {     
const char *pattern; 
    FILE *file; 
 
    // Ensure proper usage     if (argc < 2) {       
fprintf(stderr, "Usage: %s pattern [file...]\n", argv[0]);      
exit(EXIT_FAILURE); 
    } 
 
    // Get pattern from command line argument     pattern = argv[1]; 
 
    // If files are specified, open each file and grep     if (argc >= 3) {         
for (int i = 2; i < argc; i++) {             file = fopen(argv[i], "r");           
if (file == NULL) {                 
perror(argv[i]);               
continue;             }          
grep(pattern, file);           
fclose(file); 
        } 
    } else { // Grep from standard input         
grep(pattern, stdin); 
    } 
 
    return 0; 
} 
 
void grep(const char *pattern, FILE *file) {    
char line[MAX_LINE_LENGTH]; 
 
    // Read lines from file or stdin     
while (fgets(line, sizeof(line), file) != NULL) { 
        // Search for pattern in line        
if (strstr(line, pattern) != NULL) {           
// Print the line containing the pattern          
printf("%s", line); 
        } 
    } 
} 
