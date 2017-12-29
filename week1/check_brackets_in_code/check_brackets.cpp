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
    std::stack <Bracket> extra_closing_bracket_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        if (next == '(' || next == '[' || next == '{') {
            const Bracket a_new_bracket(next,position+1);
            opening_brackets_stack.push(a_new_bracket);

        }
        if (next == ')' || next == ']' || next == '}') {
            if(!opening_brackets_stack.empty() && opening_brackets_stack.top().Matchc(next)){
                opening_brackets_stack.pop();
            }
            else{
                std::cout << position + 1;
                const Bracket closing_bracket(next,position+1);
                extra_closing_bracket_stack.push(closing_bracket);
                break;
            }   
        }
    }
    if(!opening_brackets_stack.empty() && extra_closing_bracket_stack.empty()){
        std::cout << opening_brackets_stack.top().position;
    }
    else if(extra_closing_bracket_stack.empty()){
        std::cout << "Success";
    }

    return 0;
}
