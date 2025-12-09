/* syntactic errors */
void func(void) { // Missing parameter name and closing parenthesis
   return;
}

int main(void) {
    int a = 5; // Missing semicolon
    
    if (a > 0 ){ // Invalid operation
        a = a + 1;
    }
    
}