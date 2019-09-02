#include "pch.h"

#include "../db/trie.h"
using namespace std;

TEST(trie, 1_create_file)
{
    ofstream ofs("persistence");
    ofs.clear();
    ofs.close();
    //EXPECT_TRUE(false);
}

TEST(trie, 2_all) {

    trie& root = trie::instance();
    root.add_word("hello");
    root.add_word("hell");
    root.add_word("helloo");
    root.add_word("helluvetica");
    root.add_word("fellow");
    root.add_word("fell");
    root.add_word("fellowship");
    root.add_word("fellow-ship");
    EXPECT_TRUE(root.find_word("hello"));
    EXPECT_TRUE(root.find_word("hell"));
    EXPECT_TRUE(root.find_word("helloo"));
    EXPECT_TRUE(root.find_word("helluvetica"));
    EXPECT_TRUE(root.find_word("fellow"));
    EXPECT_TRUE(root.find_word("fell"));
    EXPECT_TRUE(root.find_word("fellowship"));
    EXPECT_TRUE(root.find_word("fellow-ship"));

    root.remove_word("hell");
    root.remove_word("fellowship");
    EXPECT_FALSE(root.find_word("hell"));
    EXPECT_FALSE(root.find_word("fellowship"));
    EXPECT_TRUE(root.find_word("hello"));
    EXPECT_TRUE(root.find_word("helloo"));
    EXPECT_TRUE(root.find_word("helluvetica"));
    EXPECT_TRUE(root.find_word("fellow"));
    EXPECT_TRUE(root.find_word("fell"));
    EXPECT_TRUE(root.find_word("fellow-ship"));
}

TEST(trie, 3_load) {
    trie& root = trie::instance();
    EXPECT_FALSE(root.find_word("hell"));
    EXPECT_FALSE(root.find_word("fellowship"));
    EXPECT_TRUE(root.find_word("hello"));
    EXPECT_TRUE(root.find_word("helloo"));
    EXPECT_TRUE(root.find_word("helluvetica"));
    EXPECT_TRUE(root.find_word("fellow"));
    EXPECT_TRUE(root.find_word("fell"));
    EXPECT_TRUE(root.find_word("fellow-ship"));
}


TEST(trie, 4_para_upload)
{
    string para = "It wasnt like a World Cup semifinal or something. It was just a tri-series. A series where \
                    Australia had already beaten us before this game. But this was Sachins night. This was our \
                    night and for all those in the stands and those staying up at night, ignoring everything else \
                    to watch pure class. He won the World Cup, innumerable Man of the Match and Series awards, \
                    scored the first-ever ODI double ton, made the highest number of centuries, the highest \
                    number of runs, most caps for the country... he did it all. Every landmark justified why \
                    we call him God. But this one, this innings was different. This one was like no other. \
                    Tendulkar will be remembered for many things, but Sharjah will always be special. We \
                    witnessed God in his prime that night. ";

    //clearing content
    ofstream ofs("persistence");
    ofs.clear();
    ofs.close();

    size_t start = 0;
    size_t end = 0;

    trie& root = trie::instance();

    //parsing para and preparing trie data structure
    while (start < para.length()) {
        end = start;
        while ((para[end] >= 'a' && para[end] <= 'z') ||
            (para[end] >= 'A' && para[end] <= 'Z') && end != para.length()) ++end;

        string word = para.substr(start, end - start);
        //cout << word << ";" << endl;
        root.add_word(word);
        start = end + 1;
        while (!((para[start] >= 'a' && para[start] <= 'z') ||
            (para[start] >= 'A' && para[start] <= 'Z')) && start != para.length()) ++start;
    }

    vector<string> some_words = {"Australia", "semifinal", "highest", "we", "Sharjah", "up", "at", "Match"};

    for (auto word : some_words)
        EXPECT_TRUE(root.find_word(word));

    //EXPECT_TRUE(false);
}

TEST(trie, 5_load_post_para_upload)
{
    trie& root = trie::instance();
    vector<string> some_words = {"Australia", "semifinal", "highest", "we", "Sharjah", "up", "at", "Match"};

    for (auto word : some_words)
        EXPECT_TRUE(root.find_word(word));
}
