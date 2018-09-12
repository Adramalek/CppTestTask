#ifdef UNIT_TESTING

#include "uftest.h"
#include "kernel\utils.h"

using namespace Uniteller::Framework::UnitTesting;

#include "StringUtils.h"

namespace Uniteller 
{
  namespace Framework
  {
    namespace Kernel
    {
      namespace System
      {
        using namespace StringUtils;

        TEST_CLASS_WITH_LEAKS_CHECK(StringUtilsTest)
        {
          ENABLE_CRT_CHECK(StringUtilsTest);
          /// <summary>
          /// Тестируется метод разбиения строки на голову и хвост по первому вхождению символов 
          /// </summary>
          TEST_METHOD(TestUnpackFirstSequence)
          {
            std::string resHead, resTail;
            UnpackFirst("a\\b\\c","\\", resHead, resTail,  true);
            Assert::AreEqual(resHead, std::string("a"));
            Assert::AreEqual(resTail, std::string("b\\c"));
            UnpackFirst("\\a\\b","\\", resHead, resTail,  true);
            Assert::AreEqual(resHead, std::string(""));
            Assert::AreEqual(resTail, std::string("a\\b"));
            UnpackFirst("a\\","\\", resHead, resTail,  true);
            Assert::AreEqual(resHead, std::string("a"));
            Assert::AreEqual(resTail, std::string(""));
            UnpackFirst("a\\\\","\\", resHead, resTail,  true);
            Assert::AreEqual(resHead, std::string("a"));
            Assert::AreEqual(resTail, std::string("\\"));
            UnpackFirst("","\\", resHead, resTail,  true);
            Assert::IsTrue(resHead.empty() && resTail.empty());
            UnpackFirst("","", resHead, resTail,  true);
            Assert::IsTrue(resHead.empty() && resTail.empty());
          }

          /// <summary>
          /// Тестируется метод разбиения строки на голову и хвост по первому вхождению любого символа 
          /// </summary>
          TEST_METHOD(TestUnpackFirstAnyOf)
          {
            std::string resHead, resTail;
            UnpackFirst("a\tb\\c","\\\t", resHead, resTail, false);
            Assert::AreEqual(resHead, std::string("a"));
            Assert::AreEqual(resTail, std::string("b\\c"));
            UnpackFirst("\ta\\b","\\\t", resHead, resTail, false);
            Assert::AreEqual(resHead, std::string(""));
            Assert::AreEqual(resTail, std::string("a\\b"));
            UnpackFirst("a\\\t","\t", resHead, resTail, false);
            Assert::AreEqual(resHead, std::string("a\\"));
            Assert::AreEqual(resTail, std::string(""));
            UnpackFirst("a\\\t","\\\t", resHead, resTail, false);
            Assert::AreEqual(resHead, std::string("a"));
            Assert::AreEqual(resTail, std::string("\t"));
            UnpackFirst("\\\\\\\\","\\", resHead, resTail, false);
            Assert::AreEqual(resHead, std::string(""));
            Assert::AreEqual(resTail, std::string("\\\\\\"));
          }

          /// <summary>
          /// Тестируется метод разбиения строки на голову и хвост по последнему вхождению любого символа
          /// </summary>
          TEST_METHOD(TestUnpackLastAnyOf)
          {
            std::string resHead, resTail;
            UnpackLast("a\\b\tc","\\\t", resHead, resTail, false);
            Assert::AreEqual(resHead, std::string("a\\b"));
            Assert::AreEqual(resTail, std::string("c"));
            UnpackLast("\\a\tb","\\\t", resHead, resTail, false);
            Assert::AreEqual(resHead, std::string("\\a"));
            Assert::AreEqual(resTail, std::string("b"));
            UnpackLast("\ta\\","\\\t", resHead, resTail, false);
            Assert::AreEqual(resHead, std::string("\ta"));
            Assert::AreEqual(resTail, std::string(""));
            UnpackLast("a\\\t","\\\t", resHead, resTail, false);
            Assert::AreEqual(resHead, std::string("a\\"));
            Assert::AreEqual(resTail, std::string(""));
            UnpackLast("","\\", resHead, resTail, false);
            Assert::IsTrue(resHead.empty() && resTail.empty());
            UnpackLast("","", resHead, resTail, false);
            Assert::IsTrue(resHead.empty() && resTail.empty());
          }

          /// <summary>
          /// Тестируется метод разбиения строки на голову и хвост по последнему вхождению символов
          /// </summary>
          TEST_METHOD(TestUnpackLastSequence)
          {
            std::string resHead, resTail;
            UnpackLast("a\\b\\c","\\", resHead, resTail,  true);
            Assert::AreEqual(resHead, std::string("a\\b"));
            Assert::AreEqual(resTail, std::string("c"));
            UnpackLast("a\\b\\c","a", resHead, resTail,  true);
            Assert::AreEqual(resHead, std::string(""));
            Assert::AreEqual(resTail, std::string("\\b\\c"));
            UnpackLast("a\\b","b", resHead, resTail,  true);
            Assert::AreEqual(resHead, std::string("a\\"));
            Assert::AreEqual(resTail, std::string(""));
            UnpackLast("a\\\\","\\", resHead, resTail,  true);
            Assert::AreEqual(resHead, std::string("a\\"));
            Assert::AreEqual(resTail, std::string(""));
          }

          TEST_METHOD(TestSplitUniversalAnyOf1)
          {
            //std::vector<std::string> Split(const std::string &s, std::string & delim, int Mode, bool AllowEmpty)
            std::list<std::string> res;
            res=Split(std::string("abcd"),std::string("a"),false,false);
            Assert::AreEqual(res.size(), (size_t)1);
            res.clear();
            res=Split(std::string("abcd"),std::string("a"),false,true);
            Assert::AreEqual(res.size(), (size_t)2);
            res.clear();
            res=Split(std::string("aabcd"),std::string("a"),false,true);
            Assert::AreEqual(res.size(), (size_t)3);
            res.clear();
            res=Split(std::string("bab"),std::string("a"),false,true);
            Assert::AreEqual(res.size(), (size_t)2);
            res.clear();
            res=Split(std::string("baab"),std::string("a"),false,true);
            Assert::AreEqual(res.size(), (size_t)3);
            res.clear();
            res=Split(std::string("bca"),std::string("a"),false,true);
            Assert::AreEqual(res.size(), (size_t)2);
            res.clear();
            res=Split(std::string("bcaa"),std::string("a"),false,true);
            Assert::AreEqual(res.size(), (size_t)3);
            res.clear();
            res=Split(std::string("abaca"),std::string("a"),false,false);
            Assert::AreEqual(res.size(), (size_t)2);
            res.clear();
            res=Split(std::string("abcd"),std::string("a"),false,false);
            Assert::AreEqual(res.size(), (size_t)1);
            res.clear();
            res=Split(std::string("bcda"),std::string("a"),false,false);
            Assert::AreEqual(res.size(), (size_t)1);
            res.clear();
          }

          TEST_METHOD(TestSplitUniversalAnyOf2)
          {
            //std::vector<std::string> Split(const std::string &s, std::string & delim, int Mode, bool AllowEmpty)
            std::list<std::string> res;
            res=Split(std::string("abcd"),std::string("ab"),false,false);
            Assert::AreEqual(res.size(), (size_t)1);
            res.clear();
            res=Split(std::string("abcd"),std::string("ab"),false,true);
            Assert::AreEqual(res.size(), (size_t)3);
            res.clear();
            res=Split(std::string("cabc"),std::string("ab"),false,true);
            Assert::AreEqual(res.size(), (size_t)3);
            res.clear();
          }

          TEST_METHOD(TestSplitUniversalSequence)
          {
            //std::vector<std::string> Split(const std::string &s, std::string & delim, int Mode, bool AllowEmpty)
            std::list<std::string> res;
            res=Split(std::string("abcd"),std::string("ab"),true,false);
            Assert::AreEqual(res.size(), (size_t)1);
            res.clear();
            res=Split(std::string("ababcd"),std::string("ab"),true,false);
            Assert::AreEqual(res.size(), (size_t)1);
            res.clear();
            res=Split(std::string("ababcd"),std::string("ab"),true,true);
            Assert::AreEqual(res.size(), (size_t)3);
            res.clear();
            res=Split(std::string("cababc"),std::string("ab"),true,true);
            Assert::AreEqual(res.size(), (size_t)3);
            res.clear();
            res=Split(std::string("cababc"),std::string("ab"),true,false);
            Assert::AreEqual(res.size(), (size_t)2);
            res.clear();
          }


          TEST_METHOD(TestParser)
          {
            std::list<std::string> lst;
            int match=-1;
            const char * s="\\4d-\\2d-\\2d-\\4w";
            const char * s1="1234-01-98-abcd";
            lst=MatchFormat(s, s1, match);
            Assert::AreEqual(lst.size(),(size_t)4);
            Assert::AreEqual(match, (int)Protocol::G1::Matching::Success);

            s="abc\\2d\\1w\\\\";
            s1="abc00a\\";
            lst=MatchFormat(s, s1, match);
            Assert::AreEqual(lst.size(),(size_t)2);
            Assert::AreEqual(match, (int)Protocol::G1::Matching::Success);

            s="abc\\2d\\4w";
            s1="abc00abвг";
            lst=MatchFormat(s, s1, match);
            Assert::AreEqual(lst.size(),(size_t)2);
            Assert::AreEqual(match, (int)Protocol::G1::Matching::Success);

            s="abc\\2d\\1w\\\\";
            s1="def00a\\";
            lst=MatchFormat(s, s1, match);
            Assert::AreEqual(lst.size(),(size_t)0);
            Assert::AreEqual(match, (int)Protocol::G1::Matching::Fail);

            s="abc\\d";
            s1="abc0";
            lst=MatchFormat(s, s1, match);
            Assert::AreEqual(lst.size(),(size_t)0);
            Assert::AreEqual(match, (int)Protocol::G1::Matching::WrongFormat);

            s="\\3w\\3d";
            s1="abc1234";
            lst=MatchFormat(s, s1, match);
            Assert::AreEqual(lst.size(),(size_t)2);
            Assert::AreEqual(match, (int)Protocol::G1::Matching::Fail);

            s="\\3w\\3d\\\\";
            s1="abc123";
            lst=MatchFormat(s, s1, match);
            Assert::AreEqual(lst.size(),(size_t)2);
            Assert::AreEqual(match, (int)Protocol::G1::Matching::Fail);

            s="\\3w\\3d\\1d";
            s1="abc123";
            lst=MatchFormat(s, s1, match);
            Assert::AreEqual(lst.size(),(size_t)2);
            Assert::AreEqual(match, (int)Protocol::G1::Matching::Fail);
          }
        };
      } //пространство имен System
    } // пространство имен Kernel
  } // пространство имен Framework 
} // пространство имен Uniteller

#endif // UNIT_TESTING
