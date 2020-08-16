??=include <bits/stdc++.h>

using namespace std;

void replace_all(string& str, const string& from, const string& to) ??<
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) ??<
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    ??>
??>

int main() ??<
    int L;
    cin >> L;
    cin.ignore(1, '??/n');
    string buf;
    while (L --> 0) ??<
        getline(cin, buf);
        replace_all(buf, "??" "=", "??=");
        replace_all(buf, "??" "(", "??(");
        replace_all(buf, "??" "/", "??/??/");
        replace_all(buf, "??" ")", "??)");
        replace_all(buf, "??" "'", "??'");
        replace_all(buf, "??" "<", "??<");
        replace_all(buf, "??" "!", "??!");
        replace_all(buf, "??" ">", "??>");
        replace_all(buf, "??" "-", "??-");
        cout << buf << '??/n';
    ??>
    cout.flush();
    return 0;
??>