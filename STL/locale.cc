#include <locale>
#include <codecvt>
#include <string>
#include <iostream>
#include <cwctype>
#include <iomanip>
#include <chrono>
#include <iterator>
#include <sstream>
#include <vector>
using namespace std;

void money_example()
{
    cout << showbase << put_money(12312332) << endl;
    cout.imbue(locale{"sv_SE.utf8"});
    cout << put_money(12312332) << endl;
    cout.imbue(locale{"en_US.utf8"});
    cout << put_money(12312332) << endl;
}
void time_example()
{
    using chrono::system_clock;
    auto tt = system_clock::to_time_t (system_clock::now());
    auto ptm = localtime(&tt);

    cout << "Now (local time): " << put_time(ptm,"%A %x %X") << '\n';
    cout.imbue(locale{"en_US.utf8"});
    cout << "Now (local time): " << put_time(ptm,"%A %x %X") << '\n';
    cout.imbue(locale{"sv_SE.utf8"});
    cout << "Now (local time): " << put_time(ptm,"%A %x %X") << '\n';
}

void delimiter();
void unicode();
int main()
{
    //money_example();
    //time_example();
    //delimiter();
    unicode();

}
// ctype<char> is based on a simple lookup table to classify characters,
// here we create our own based on the classic table (C locale) and extend it.
struct colon_is_space : std::ctype<char> {

    colon_is_space() : std::ctype<char>(make_table()) {}

    static mask const* make_table()
    {
        static vector<mask> rc{classic_table(), classic_table()+table_size};
        // int value of the character used as index
        rc[':'] = std::ctype_base::space;
        return rc.data();
    }
};

void delimiter()
{
    string data {"123:333:3213 2312:323"};
    istringstream iss {data};
    // create a copy of the current locale, add a Facet for classifications. The
    // extra facet (new) will be destroyed by ~locale.
    iss.imbue(locale{locale{""}, new colon_is_space});
    copy(istream_iterator<int>{iss}, istream_iterator<int>{}, ostream_iterator<int>{cout, " "});
}

void unicode()
{
    // a utf-8 string literal (string is still sequence of char)
    string s = u8"ääå…ⴇ‽ų‡";

    // used to convert between wchar_t (utf32) and char* (utf8)
    std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;

    // changes the value of a default-constructed locale object. Uses standard
    // "C" locale by default (usually simple ASCII).
    // The chosen locale must be supported on the current system.
    // Use locale{""} for the system locale used at runtime
    locale::global(locale{"sv_SE.utf8"});

    // print ints as hex with base (0x...)
    cout << hex << showbase;
    int code_points{};

    // convert to wstring (usually four bytes per character/code point)
    for (wchar_t c: utf8_conv.from_bytes(s))
    {
        ++code_points;
        // cout (and STDOUT) expects characters -> convert back to bytes
        // wint_t is an integer type with the same size as wchar_t
        cout << utf8_conv.to_bytes(c) << " (" << (wint_t)c << ")";
        if ( isalpha(c, locale{} ) )
        {
            auto cu = toupper(c, locale{});
            cout << "-> "
                << utf8_conv.to_bytes(cu)
                << " (" << (wint_t)cu << ")";
        }
        cout << endl;
    }
    cout << "Number of unicode code points: " << dec << code_points << endl;
    cout << "String length: " << s.length() << endl;
    // Print each char from the string. Will print each byte from the utf8-encoded
    // string (probably not printable)
    for ( char c: s)
    {
        cout << c << endl;
    }
}
