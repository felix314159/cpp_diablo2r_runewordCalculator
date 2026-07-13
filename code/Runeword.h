#ifndef RUNEWORD_H
#define RUNEWORD_H

#include <set>
#include <vector>

#include <wx/string.h>



using std::set, std::string, std::vector;


int calculateSockets(string &s);
set<string> calculateRunes(string &s);
bool isUpper(char &c);

class Runeword{
public:
    string name;            // e.g. "Spirit"
    string runeword;        // e.g. "TalThulOrtAmn"
    int sockets;            // e.g. 3 (amount of runes required)
    set<string> runes;      // e.g. {Tal, Thul, Ort, Amn} (for Spirit)
    set<string> items;      // e.g. {Shields, Swords} (for Spirit)
    string runeword_stats;  // string consisting of all stats gained by this word
    int level_req;          // level requirement to use the runeword

    Runeword(string s1, string s2, set<string> set1, string s3, int s4);        // constructor
    ~Runeword();                                                                // destructor

};

extern vector<Runeword> runewords;

void populate_runewords(vector<Runeword> &temp);
vector<Runeword> actual_calc(set<wxString> &user_runes, wxString user_item_wx, int user_sockets, wxString levelreq);

bool isSubset(set<string> &s1, set<wxString> &s2);
set<string> user_item_to_set(string user_item);

#endif
