#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "include/search.h"

using namespace std;
using namespace testing;

// Returns the same token without changing anything
TEST(CleanToken, sameString) {
  ASSERT_THAT(cleanToken("hello"), StrEq("hello"));
  ASSERT_THAT(cleanToken("hello123"), StrEq("hello123"));
  ASSERT_THAT(cleanToken("123hello"), StrEq("123hello"));
  ASSERT_THAT(cleanToken("123hello123"), StrEq("123hello123"));
}

// Returns an empty string when no letters are in the token
TEST(CleanToken, emptyString) {
  ASSERT_THAT(cleanToken("12345"), StrEq(""));
  ASSERT_THAT(cleanToken("....."), StrEq(""));
  ASSERT_THAT(cleanToken("     "), StrEq(""));
  ASSERT_THAT(cleanToken(".....     ....."), StrEq(""));
  ASSERT_THAT(cleanToken(""), StrEq(""));
  ASSERT_THAT(cleanToken("...   ...   ..."), StrEq(""));
}

// returns a lowercase string
TEST(CleanToken, checkLowerCase) {
  ASSERT_THAT(cleanToken("Hello"), StrEq("hello"));
  ASSERT_THAT(cleanToken("123Hello"), StrEq("123hello"));
  ASSERT_THAT(cleanToken("HELLO"), StrEq("hello"));
  ASSERT_THAT(cleanToken(".....HELLO....."), StrEq("hello"));
  ASSERT_THAT(cleanToken("hEllO"), StrEq("hello"));
}

// Clean the trailing punctuation
TEST(CleanToken, cleanBack) {
  ASSERT_THAT(cleanToken("hello..."), StrEq("hello"));
  ASSERT_THAT(cleanToken("hello123!!!"), StrEq("hello123"));
  ASSERT_THAT(cleanToken("123hello!.??."), StrEq("123hello"));
  ASSERT_THAT(cleanToken("123hello123   !!!..."), StrEq("123hello123   "));
}

// clean the preceding punctuation
TEST(CleanToken, cleanFront) {
  ASSERT_THAT(cleanToken("...hello"), StrEq("hello"));
  ASSERT_THAT(cleanToken("!!!hello123"), StrEq("hello123"));
  ASSERT_THAT(cleanToken("!/??.123hello"), StrEq("123hello"));
  ASSERT_THAT(cleanToken("...!!!   123hello123"), StrEq("   123hello123"));
}

// clean the preceding and trailing punctuation
TEST(CleanToken, cleanBoth) {
  ASSERT_THAT(cleanToken("...hello..."), StrEq("hello"));
  ASSERT_THAT(cleanToken("!!!hello123..."), StrEq("hello123"));
  ASSERT_THAT(cleanToken("!.!123hello.!."), StrEq("123hello"));
  ASSERT_THAT(cleanToken("!.!  123hello123   .!!."), StrEq("  123hello123   "));
}

// Clean out different types of punction
TEST(CleanToken, differentPunctuations) {
  ASSERT_THAT(cleanToken("!#$%&'()*+,-./:;<=>?@[]^_`{|}~.hello!#$%&'()*+,-./"
                         ":;<=>?@[]^_`{|}~."),
              StrEq("hello"));
  ASSERT_THAT(
      cleanToken("!#$%&'()*+,-./:;<=>?@[]^_`{|}~.123hello123.!#$%&'()*+,-./"
                 ":;<=>?@[]^_`{|}~..."),
      StrEq("123hello123"));
  ASSERT_THAT(cleanToken("!.!#$%&'()*+,-./:;<=>?@[]^_`{|}~.! 123hello "
                         ".!!#$%&'()*+,-./:;<=>?@[]^_`{|}~.."),
              StrEq(" 123hello "));
}

// Characters that are not punctuation
TEST(CleanToken, nonPuncuation) {
  ASSERT_THAT(cleanToken("“hello“..."), StrEq("“hello“"));
  ASSERT_THAT(cleanToken("\thello123\t..."), StrEq("\thello123\t"));
  ASSERT_THAT(cleanToken("!.!\n\t123hello\n\t.!."), StrEq("\n\t123hello\n\t"));
}

// Punctuation in the middle
TEST(CleanToken, middlePunctuation) {
  ASSERT_THAT(cleanToken(".. .hello. .."), StrEq(" .hello. "));
  ASSERT_THAT(cleanToken("!!!hello123!.!#$%&'()*+,-./:;<=>?@[]^_`{|}~.!r..."),
              StrEq("hello123!.!#$%&'()*+,-./:;<=>?@[]^_`{|}~.!r"));
  ASSERT_THAT(cleanToken("!.!123he.llo.!."), StrEq("123he.llo"));
  ASSERT_THAT(cleanToken("   !.!#$%&'()*+,-./:;<=>?@[]^_`{|}~.!s   "),
              StrEq("   !.!#$%&'()*+,-./:;<=>?@[]^_`{|}~.!s   "));
}

TEST(CleanToken, testAll) {
  ASSERT_THAT(cleanToken("HeLLo“..."), StrEq("hello“"));
  ASSERT_THAT(cleanToken("...“HeLLo"), StrEq("“hello"));
  ASSERT_THAT(cleanToken("...“HeLLo“..."), StrEq("“hello“"));
  ASSERT_THAT(cleanToken("...H.e.L.L.o..."), StrEq("h.e.l.l.o"));
  ASSERT_THAT(cleanToken(".!.!.“H!e.L?L.o“.?."), StrEq("“h!e.l?l.o“"));
}

// edge cases test
TEST(CleanToken, edgeCases) {
  ASSERT_THAT(cleanToken("x"), StrEq("x"));
  ASSERT_THAT(cleanToken("..........a"), StrEq("a"));
  ASSERT_THAT(cleanToken("a.........."), StrEq("a"));
  ASSERT_THAT(cleanToken("..........a.........."), StrEq("a"));
  ASSERT_THAT(cleanToken("“..........a.........."), StrEq("“..........a"));
  ASSERT_THAT(cleanToken("..........a..........“"), StrEq("a..........“"));
  ASSERT_THAT(cleanToken("“..........a..........“"),
              StrEq("“..........a..........“"));
}

TEST(GatherTokens, singleSpaces) {
  string text = "hello my name is shazaib";
  set<string> expected = {"hello", "my", "name", "is", "shazaib"};

  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(GatherTokens, multipleSpaces) {
  string text = "hello   my name   is    shazaib";
  set<string> expected = {"hello", "my", "name", "is", "shazaib"};

  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(GatherTokens, leadingSpaces) {
  string text = "   hello my name is shazaib";
  set<string> expected = {"hello", "my", "name", "is", "shazaib"};

  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(GatherTokens, trailingSpaces) {
  string text = "hello my name is shazaib     ";
  set<string> expected = {"hello", "my", "name", "is", "shazaib"};

  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(GatherTokens, mixedSpaces) {
  string text = "     hello my    name is    shazaib     ";
  set<string> expected = {"hello", "my", "name", "is", "shazaib"};

  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(GatherTokens, checkCleanTokens) {
  string text = "... ?.?!  ..helLo   .. ..my nAme?.   is Sha.Zaib.. .";
  set<string> expected = {"hello", "my", "name", "is", "sha.zaib"};

  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(BuildIndex, tinyTxt) {
  string filename = "data/tiny.txt";
  map<string, set<string>> expectedIndex = {
      {"eggs", {"www.shoppinglist.com"}},
      {"milk", {"www.shoppinglist.com"}},
      {"fish", {"www.shoppinglist.com", "www.dr.seuss.net"}},
      {"bread", {"www.shoppinglist.com"}},
      {"cheese", {"www.shoppinglist.com"}},
      {"red", {"www.rainbow.org", "www.dr.seuss.net"}},
      {"gre-en", {"www.rainbow.org"}},
      {"orange", {"www.rainbow.org"}},
      {"yellow", {"www.rainbow.org"}},
      {"blue", {"www.rainbow.org", "www.dr.seuss.net"}},
      {"indigo", {"www.rainbow.org"}},
      {"violet", {"www.rainbow.org"}},
      {"one", {"www.dr.seuss.net"}},
      {"two", {"www.dr.seuss.net"}},
      {"i'm", {"www.bigbadwolf.com"}},
      {"not", {"www.bigbadwolf.com"}},
      {"trying", {"www.bigbadwolf.com"}},
      {"to", {"www.bigbadwolf.com"}},
      {"eat", {"www.bigbadwolf.com"}},
      {"you", {"www.bigbadwolf.com"}},
  };
  map<string, set<string>> studentIndex;
  int studentNumProcesed = buildIndex(filename, studentIndex);

  string indexTestFeedback =
      "buildIndex(\"" + filename + "\", ...) index incorrect\n";
  EXPECT_THAT(studentIndex, ContainerEq(expectedIndex)) << indexTestFeedback;

  string retTestFeedback =
      "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
  EXPECT_THAT(studentNumProcesed, Eq(4)) << retTestFeedback;
}

TEST(BuildIndex, nofile) {
  string filename = "data/filename.txt";
  map<string, set<string>> expectedIndex = {};
  map<string, set<string>> studentIndex;
  int studentNumProcesed = buildIndex(filename, studentIndex);

  string indexTestFeedback =
      "buildIndex(\"" + filename + "\", ...) index incorrect\n";
  EXPECT_THAT(studentIndex, ContainerEq(expectedIndex)) << indexTestFeedback;

  string retTestFeedback =
      "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
  EXPECT_THAT(studentNumProcesed, Eq(0)) << retTestFeedback;
}

TEST(BuildIndex, webpageCounterTest) {
  string filename = "data/uiccs-news.txt";
  map<string, set<string>> studentIndex;
  int studentNumProcesed = buildIndex(filename, studentIndex);

  string retTestFeedback =
      "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
  EXPECT_THAT(studentNumProcesed, Eq(85)) << retTestFeedback;
}

map<string, set<string>> INDEX = {
    {"hello", {"example.com", "uic.edu"}},
    {"there", {"example.com"}},
    {"according", {"uic.edu"}},
    {"to", {"uic.edu"}},
    {"all", {"example.com", "uic.edu", "random.org"}},
    {"known", {"uic.edu"}},
    {"laws", {"random.org"}},
    {"of", {"random.org"}},
    {"aviation", {"random.org"}},
    {"a", {"uic.edu", "random.org"}},
};

TEST(FindQueryMatches, wrongFirstTerm) {
  set<string> expected;

  expected = {"example.com"};
  EXPECT_THAT(findQueryMatches(INDEX, "here there"), ContainerEq(expected));

  expected = {"example.com", "uic.edu"};
  EXPECT_THAT(findQueryMatches(INDEX, "here hello"), ContainerEq(expected));
  EXPECT_THAT(findQueryMatches(INDEX, "here Hello!"), ContainerEq(expected));

  expected = {};
  EXPECT_THAT(findQueryMatches(INDEX, "here"), ContainerEq(expected));

  expected = {"example.com", "uic.edu", "random.org"};
  EXPECT_THAT(findQueryMatches(INDEX, "here hello laws aviation"),
              ContainerEq(expected));
  EXPECT_THAT(findQueryMatches(INDEX, "here Hello, Laws, AVIATION!"),
              ContainerEq(expected));

  expected = {"uic.edu"};
  EXPECT_THAT(findQueryMatches(INDEX, "here hello +all +to"),
              ContainerEq(expected));

  expected = {"example.com"};
  EXPECT_THAT(findQueryMatches(INDEX, "here all -of -a"),
              ContainerEq(expected));

  expected = {};
  EXPECT_THAT(findQueryMatches(INDEX, "here all -all +all"),
              ContainerEq(expected));

  expected = {"example.com", "uic.edu", "random.org"};
  EXPECT_THAT(findQueryMatches(INDEX, "here all -all +all all"),
              ContainerEq(expected));
}

TEST(FindQueryMatches, wrongMiddleTerm) {
  set<string> expected;

  expected = {"example.com"};
  EXPECT_THAT(findQueryMatches(INDEX, " there here"), ContainerEq(expected));

  expected = {"example.com", "uic.edu"};
  EXPECT_THAT(findQueryMatches(INDEX, " hello here"), ContainerEq(expected));
  EXPECT_THAT(findQueryMatches(INDEX, " Hello! here"), ContainerEq(expected));

  expected = {};
  EXPECT_THAT(findQueryMatches(INDEX, "here +here"), ContainerEq(expected));

  expected = {"example.com", "uic.edu", "random.org"};
  EXPECT_THAT(findQueryMatches(INDEX, " hello laws here aviation"),
              ContainerEq(expected));
  EXPECT_THAT(findQueryMatches(INDEX, " Hello, Laws, AVIATION! here"),
              ContainerEq(expected));

  expected = {"uic.edu"};
  EXPECT_THAT(findQueryMatches(INDEX, " hello +all here +to"),
              ContainerEq(expected));
  expected = {"uic.edu"};
  // EXPECT_THAT(findQueryMatches(INDEX, " hello +all +here +to"),
  //             ContainerEq(expected));

  expected = {"example.com"};
  EXPECT_THAT(findQueryMatches(INDEX, " all -of here -a"),
              ContainerEq(expected));
  expected = {"example.com"};
  EXPECT_THAT(findQueryMatches(INDEX, " all -of -here -a"),
              ContainerEq(expected));

  expected = {};
  EXPECT_THAT(findQueryMatches(INDEX, "all -to there +name"),
              ContainerEq(expected));

  expected = {};
  EXPECT_THAT(findQueryMatches(INDEX, " all -all here +all"),
              ContainerEq(expected));
  expected = {};
  EXPECT_THAT(findQueryMatches(INDEX, " all -all +here +all"),
              ContainerEq(expected));
  expected = {};
  EXPECT_THAT(findQueryMatches(INDEX, " all -all -here +all"),
              ContainerEq(expected));

  expected = {"example.com", "uic.edu", "random.org"};
  EXPECT_THAT(findQueryMatches(INDEX, " all -all here +all all"),
              ContainerEq(expected));
  expected = {"example.com", "uic.edu", "random.org"};
  EXPECT_THAT(findQueryMatches(INDEX, " all -all +here +all all"),
              ContainerEq(expected));
  expected = {"example.com", "uic.edu", "random.org"};
  EXPECT_THAT(findQueryMatches(INDEX, " all -all -here +all all"),
              ContainerEq(expected));
}