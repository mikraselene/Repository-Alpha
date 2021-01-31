#include <iostream>
#include <fstream>
using namespace std;

string rp(string k, string s, string p)
{
    while (s.find("  ") != s.npos)
    {
        s = s.replace(s.find("  "), 2, "");
    }
    while (s.find(k) != s.npos)
    {
        s = s.replace(s.find(k), k.size(), p);
    }
    return s;
}

int main()
{
    string s;
    string input_file = "new_dblp.xml";
    std::ifstream in(input_file);
    ofstream out("ndblp.xml");
    long long cnt = 0;
    while (getline(in, s))
    {
        cnt++;
        if (cnt % 100000 == 0)
        {
            cout << cnt / 100000 << endl;
        }
        s = rp("notetype", s, "note type");
        /*
        s = rp("&reg;", s, "®");
        s = rp("&micro;", s, "µ");
        s = rp("&times;", s, "×");
        s = rp("&Agrave;", s, "À");
        s = rp("&Aacute;", s, "Á");
        s = rp("&Acirc;", s, "Â");
        s = rp("&Atilde;", s, "Ã");
        s = rp("&Auml;", s, "Ä");
        s = rp("&Aring;", s, "Å");
        s = rp("&AElig;", s, "Æ");
        s = rp("&Ccedil;", s, "Ç");
        s = rp("&Egrave;", s, "È");
        s = rp("&Eacute;", s, "É");
        s = rp("&Ecirc;", s, "Ê");
        s = rp("&Euml;", s, "Ë");
        s = rp("&Igrave;", s, "Ì");
        s = rp("&Iacute;", s, "Í");
        s = rp("&Icirc;", s, "Î");
        s = rp("&Iuml;", s, "Ï");
        s = rp("&ETH;", s, "Ð");
        s = rp("&Ntilde;", s, "Ñ");
        s = rp("&Ograve;", s, "Ò");
        s = rp("&Oacute;", s, "Ó");
        s = rp("&Ocirc;", s, "Ô");
        s = rp("&Otilde;", s, "Õ");
        s = rp("&Ouml;", s, "Ö");
        s = rp("&Oslash;", s, "Ø");
        s = rp("&Ugrave;", s, "Ù");
        s = rp("&Uacute;", s, "Ú");
        s = rp("&Ucirc;", s, "Û");
        s = rp("&Uuml;", s, "Ü");
        s = rp("&Yacute;", s, "Ý");
        s = rp("&THORN;", s, "Þ");
        s = rp("&szlig;", s, "ß");
        s = rp("&agrave;", s, "à");
        s = rp("&aacute;", s, "á");
        s = rp("&acirc;", s, "â");
        s = rp("&atilde;", s, "ã");
        s = rp("&auml;", s, "ä");
        s = rp("&aring;", s, "å");
        s = rp("&aelig;", s, "æ");
        s = rp("&ccedil;", s, "ç");
        s = rp("&egrave;", s, "è");
        s = rp("&eacute;", s, "é");
        s = rp("&ecirc;", s, "ê");
        s = rp("&euml;", s, "ë");
        s = rp("&igrave;", s, "ì");
        s = rp("&iacute;", s, "í");
        s = rp("&icirc;", s, "î");
        s = rp("&iuml;", s, "ï");
        s = rp("&eth;", s, "ð");
        s = rp("&ntilde;", s, "ñ");
        s = rp("&ograve;", s, "ò");
        s = rp("&oacute;", s, "ó");
        s = rp("&ocirc;", s, "ô");
        s = rp("&otilde;", s, "õ");
        s = rp("&ouml;", s, "ö");
        s = rp("&oslash;", s, "ø");
        s = rp("&ugrave;", s, "ù");
        s = rp("&uacute;", s, "ú");
        s = rp("&ucirc;", s, "û");
        s = rp("&uuml;", s, "ü");
        s = rp("&yacute;", s, "ý");
        s = rp("&thorn;", s, "þ");
        s = rp("&yuml;", s, "ÿ");
        */
        out << s;
    }
}