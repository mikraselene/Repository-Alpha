#include <iostream>
#include <list>

#include "tree.hpp"

void Languages() {
  /*
  tree<std::string> lang;
  auto head = lang.set_head("LANGUAGES");
  auto indo_european = lang.append_child(head, "INDO-EUROPEAN LANGUAGES");
  {
      auto germanic = lang.append_child(indo_european, "Germanic Languages");
      {
          auto english = lang.append_child(germanic, "English");
          {
              auto british_english = lang.append_child(english, "British
  English"); auto american_english = lang.append_child(english, "American
  English");
          }
          auto german = lang.append_child(germanic, "German");
          auto dutch = lang.append_child(germanic, "Dutch");
          auto swedish = lang.append_child(germanic, "Swedish");
      }
      auto romance = lang.append_child(indo_european, "Romance Languages");
      {
          auto french = lang.append_child(romance, "French");
          auto spanish = lang.append_child(romance, "Spanish");
          auto catalan = lang.append_child(romance, "Catalan");
          auto portuguese = lang.append_child(romance, "Portuguese");
          auto italian = lang.append_child(romance, "Italian");
          auto romanian = lang.append_child(romance, "Romanian");
      }
      auto indo_iranian = lang.append_child(indo_european, "Indo-Iranian
  Languages");
      {
          auto hindi = lang.append_child(indo_iranian, "Hindi");
          auto sanskrit = lang.append_child(indo_iranian, "Sanskrit");
          auto persian = lang.append_child(indo_iranian, "Persian");
      }
      auto hellenic = lang.append_child(indo_european, "Hellenic Languages");
      {
          auto greek = lang.append_child(hellenic, "Greek");
      }
  }
  auto sino_tibetan = lang.append_child(head, "SINO-TIBETAN LANGUAGES");
  {
      auto sinitic = lang.append_child(sino_tibetan, "Sinitic Languages");
      {
          auto mandarin = lang.append_child(sinitic, "Mandarin");
          {
              auto putonghua = lang.append_child(mandarin, "Putonghua");
          }
          auto cantonese = lang.append_child(sinitic, "Cantonese");
          auto hakka = lang.append_child(sinitic, "Hakka");
      }
      auto tibeto_burman = lang.append_child(sino_tibetan, "Tibeto-Burman
  Languages");
      {
          auto tibetan = lang.append_child(tibeto_burman, "Tibetan");
          auto gyalrong = lang.append_child(tibeto_burman, "Gyalrong");
      }
  }
  auto afroasiatic = lang.append_child(head, "AFROASIATIC LANGUAGES");
  {
      auto semitic = lang.append_child(afroasiatic, "Semitic Languages");
      {
          auto arabic = lang.append_child(semitic, "Arabic");
          auto aramaic = lang.append_child(semitic, "Aramaic");
          auto hebrew = lang.append_child(semitic, "Hebrew");
      }
      auto berber = lang.append_child(afroasiatic, "Berber Languages");
      {
          auto kabyle = lang.append_child(berber, "Kabyle");
      }
  }
  lang.print(lang.begin(), lang.end());
  */

#define PAR(xx) auto it = xx;
#define ADD(xx) lang.append_child(it, xx)

  tree<std::string> lang;
  auto head = lang.set_head("LANGUAGES");
  auto a = head;
  auto b = head;
  {
    PAR(head);
    auto indo_european = ADD("INDO-EUROPEAN LANGUAGES");
    {
      PAR(indo_european);
      auto germanic = ADD("Germanic Languages");
      {
        PAR(germanic);
        auto english = ADD("English");
        {
          PAR(english);
          ADD("British English");
          ADD("American English");
        }
        ADD("German");
        ADD("Dutch");
        ADD("Swedish");
      }
      auto italic = ADD("Italic Languages");
      {
        PAR(italic);
        auto latino_faliscan = ADD("Latino-Faliscan Languages");
        {
          PAR(latino_faliscan);
          auto latin = ADD("Latin");
          {
            PAR(latin);
            ADD("Classical Latin");
            ADD("Vulgar Latin");
            ADD("Ecclesiastical Latin");
          }
          ADD("Faliscan");
        }
        auto romance = ADD("Romance Languages");
        {
          PAR(romance);
          ADD("French");
          ADD("Spanish");
          ADD("Catalan");
          ADD("Portuguese");
          ADD("Italian");
          ADD("Romanian");
        }
      }
      auto indo_iranian = ADD("Indo-Iranian Languages");
      {
        PAR(indo_iranian);
        ADD("Hindi");
        ADD("Sanskrit");
        ADD("Persian");
      }
      auto hellenic = ADD("Hellenic Languages");
      {
        PAR(hellenic);
        auto greek = ADD("Greek");
        {
          PAR(greek);
          ADD("Ancient Greek");
          ADD("Modern Greek");
        }
      }
    }
    auto sino_tibetan = ADD("SINO-TIBETAN LANGUAGES");
    {
      PAR(sino_tibetan);
      auto sinitic = ADD("Sinitic Languages");
      {
        PAR(sinitic);
        auto mandarin = ADD("Mandarin");
        {
          PAR(mandarin);
          a = ADD("Standard Chinese");
          b = ADD("Lower Yangtze Mandarin");
        }
        b = ADD("Cantonese");
        ADD("Hakka");
      }
      auto tibeto_burman = ADD("Tibeto-Burman Languages");
      {
        PAR(tibeto_burman);
        ADD("Tibetan");
        ADD("Gyalrong");
      }
    }
    auto afroasiatic = ADD("AFROASIATIC LANGUAGES");
    {
      PAR(afroasiatic);
      auto semitic = ADD("Semitic Languages");
      {
        PAR(semitic);
        ADD("Arabic");
        ADD("Aramaic");
        ADD("Hebrew");
      }
      auto berber = ADD("Berber Languages");
      {
        PAR(berber);
        ADD("Kabyle");
      }
    }
  }

  lang.print();
  cout << "LCA(" << *a << ", " << *b
       << ") = " << *lang.lowest_common_ancestor(a, b) << endl;

#undef ADD
#undef PAR
}

void Sample2() {}

int main() {
  Languages();
  tree<double> j;
  auto h = j.set_head(1);
  auto h1 = j.append_child(h, 1.1);
  auto h11 = j.append_child(h1, 1.11);
  auto h2 = j.append_child(h, 1.2);
  auto h3 = j.append_child(h, 1.3);
  auto h31 = j.append_child(h3, 1.31);
  auto h32 = j.append_child(h3, 1.32);
  // j.print(j.begin(), j.end());
}
