
#include "pch.h"

#include "..//db/word_db.h"
using namespace std;

TEST(word_db, 1_create_file)
{
    ofstream ofs("persistence");
    ofs.clear();
    ofs.close();
    EXPECT_TRUE(false);
}

TEST(word_db, 2_add_word)
{
    word_db::instance().add_word("hello");
    word_db::instance().add_word("hell");
    word_db::instance().add_word("helluvetica");
    EXPECT_TRUE(word_db::instance().has_word("hello"));
    EXPECT_TRUE(word_db::instance().has_word("hell"));
    EXPECT_TRUE(word_db::instance().has_word("helluvetica"));
    //EXPECT_TRUE(false);
}

TEST(word_db, 3_load_post_add)
{
    //word_db::instance().print();
    EXPECT_TRUE(word_db::instance().has_word("hello"));
    EXPECT_TRUE(word_db::instance().has_word("hell"));
    EXPECT_TRUE(word_db::instance().has_word("helluvetica"));
    //EXPECT_TRUE(false);
}

TEST(word_db, 4_remove_word)
{
    word_db::instance().remove_word("hell");
    //word_db::instance().print();
    EXPECT_TRUE(word_db::instance().has_word("hello"));
    EXPECT_FALSE(word_db::instance().has_word("hell"));
    EXPECT_TRUE(word_db::instance().has_word("helluvetica"));
    //EXPECT_TRUE(false);
}

TEST(word_db, 5_load_post_remove)
{
    //word_db::instance().print();
    EXPECT_TRUE(word_db::instance().has_word("hello"));
    EXPECT_FALSE(word_db::instance().has_word("hell"));
    EXPECT_TRUE(word_db::instance().has_word("helluvetica"));
    //EXPECT_TRUE(false);
}

TEST(word_db, 6_reuse_post_remove)
{
    word_db::instance().add_word("prob");
    //word_db::instance().print();
    EXPECT_TRUE(word_db::instance().has_word("hello"));
    EXPECT_FALSE(word_db::instance().has_word("hell"));
    EXPECT_TRUE(word_db::instance().has_word("prob"));
    EXPECT_TRUE(word_db::instance().has_word("helluvetica"));
    //EXPECT_TRUE(false);
}

TEST(word_db, 7_load_post_reuse_post_remove)
{
    //word_db::instance().print();
    EXPECT_TRUE(word_db::instance().has_word("hello"));
    EXPECT_FALSE(word_db::instance().has_word("hell"));
    EXPECT_TRUE(word_db::instance().has_word("prob"));
    EXPECT_TRUE(word_db::instance().has_word("helluvetica"));
    //EXPECT_TRUE(false);
}
