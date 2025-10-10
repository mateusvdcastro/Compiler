/* syntactic errors */

int main() {
    int a = 5 // Missing semicolon
    
    void func( { // Missing parameter name and closing parenthesis
        return;
    }

    if (a > 0 !=){ // Invalid operation
        a = a + 1;
    }

    return 0;
}