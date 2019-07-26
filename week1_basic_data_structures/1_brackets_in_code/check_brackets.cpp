#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            Bracket opening(next,position);
            opening_brackets_stack.push(opening);
        }
        else if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            Bracket closing(next,position);
            if(opening_brackets_stack.empty()){
              std::cout << closing.position + 1 << std::endl;
              return 0;
            }
            Bracket laststack = opening_brackets_stack.top();
            opening_brackets_stack.pop();
            bool match = laststack.Matchc(closing.type);
            if (!match){
              std::cout <<  closing.position + 1 << std::endl;
              return 0;
            }
        }
    }

    if(!opening_brackets_stack.empty()){
      while(opening_brackets_stack.size() > 1)
        opening_brackets_stack.pop();

      std::cout << opening_brackets_stack.top().position + 1 << std::endl;
      return 0;
    }

    // Printing answer, write your code here
    std::cout << "Success" << std::endl;
    return 0;
}
