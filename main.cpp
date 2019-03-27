#include <bits/stdc++.h>
using namespace std;

string charset = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

uint64_t mrand(uint64_t change = 0) {
    static uint64_t seed = 7122;
    seed ^= change;
    return seed = (seed << 45) ^ (seed << 36) ^ (seed << 16) ^ (seed << 11) ^ (seed << 4) ^ (seed >> 7) ^ (seed >> 15) ^ (seed >> 19) ^ (seed >> 40);
}

uint64_t mhash(string s = "") {
    uint64_t rt = 0;
    for (char c : s) rt = rt * 7902131 + c;
    return rt;
}

string rand_string(string str = "") {
    string s;
    for (int i = 0; i < 5; ++i) {
        s += charset[mrand(mhash(str)) % charset.size()];
    }
    return s;
}

map<string, string> mp;

string get(string s){
    if (s == "") return "";
    if (s == " ") return " ";
    auto it = mp.find(s);
    if (it != mp.end()) return it->second;
    else return mp[s] = rand_string(s);
}

bool in(char c, string s) {
    for (char a : s) if (a == c) return 1;
    return 0;
}

string remove_continue_space(string s) {
    string t;
    for (char c : s) {
        if (c == ' ' && t.size() && t.back() == ' ') continue;
        t += c;
    }
    return t;
}

vector<string> outputs;

int main() {
    string s; while (getline(cin, s)) {
        if (s.empty()) { outputs.push_back(s); continue; }
        if (s[0] == '#') { outputs.push_back(s); continue; }
        if (s.substr(0, 2) == "//") { continue; }
        string output;
        for (int i = 0; i < int(s.size()); ++i) {
            if (s[i] == '\'') {
                int j = i + 1;
                for (; s[j - 1] == '\\' || s[j] != '\''; ++j);
                output += get(s.substr(i, j - i + 1)) + " ";
                i = j; continue;
            } else if (s[i] == '\"') {
                int j = i + 1;
                for (; s[j - 1] == '\\' || s[j] != '\"'; ++j);
                output += get(s.substr(i, j - i + 1)) + " ";
                i = j; continue;
            } else {
                if (s[i] == ' ') {
                    output += " "; continue;
                }
                if (i + 6 < int(s.size())) {
                    string key = s.substr(i, 7);
                    if (key == "...Args" || key == "...args" || key == "args...") {
                        output += get(key) + " ";
                        i += 6; continue;
                    }
                }
                if (i + 2 < int(s.size())) {
                    string op = s.substr(i, 3);
                    if (op == "<<=" || op == ">>=" || op == "<=>" || op == "->*") {
                        output += get(op) + " ";
                        i += 2; continue;
                    }
                }
                if (i + 1 < int(s.size())) {
                    string op = s.substr(i, 2);
                    if (op == "+=" || op == "-=" || op == "*=" || op == "/=" || op == "%=" ||
                        op == "^=" || op == "&=" || op == "|=" || op == "<<" || op == ">>" || 
                        op == "==" || op == "!=" || op == "<=" || op == ">=" || op == "&&" ||
                        op == "||" || op == "++" || op == "--" || op == "->") {
                        output += get(op) + " ";
                        ++i; continue;
                    }
                }
                if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%' ||
                    s[i] == '^' || s[i] == '&' || s[i] == '|' || s[i] == '~' || s[i] == '!' ||
                    s[i] == '=' || s[i] == '<' || s[i] == '>' || s[i] == ',' || s[i] == '.' ||
                    s[i] == '(' || s[i] == ')' || s[i] == '[' || s[i] == ']' || s[i] == '{' || 
                    s[i] == '}') {
                    output += get(string(1, s[i])) + " ";
                    continue;
                }
                int j = i + 1;
                for (; j < int(s.size()) && (isalpha(s[j]) || isdigit(s[j]) || s[j] == '_'); ++j);
                // if (s.substr(i, j - i) == "Args") j += 3;
                output += get(s.substr(i, j - i)) + " ";
                i = j - 1; continue;
            }
        }
        outputs.push_back(output);
        // outputs.push_back("// " + s);
    }
    for (auto &p : mp) {
        cout << "#define " << p.second << " " << p.first << endl;
    }
    for (int i = 0; i < int(outputs.size()); ++i) {
        cout << remove_continue_space(outputs[i]) << endl;
    }
}
