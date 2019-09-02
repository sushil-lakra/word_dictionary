#pragma once
#include <vector>
#include <string>
#include "word_db.h"

class trie_node {
    char char_;
    bool word_end_;
    std::vector<trie_node> nexts_;

public:
    trie_node(bool word_end = false) : char_{ 0 }, nexts_{}, word_end_{word_end} {}
    trie_node(char inp) : char_{inp}, nexts_ {}, word_end_{false}{}

    void add_word(const std::string& word, size_t idx = 0) {
        if (idx == word.length()) {
            for (auto& next : nexts_)
                if (next.word_end_)
                    return;

            word_db::instance().add_word(word);
            word_end_ = true;
            return;
        }

        if (char_ == word[idx]) {
            if (idx < word.length() - 1)
                for (auto& next : nexts_) {
                    if (next.char_ == word[idx + 1]) {
                        next.add_word(word, idx + 1);
                        return;
                    }
                }
        }
        char_ = word[idx];
        nexts_.push_back(trie_node());
        nexts_[nexts_.size() - 1].add_word(word, idx + 1);
    }

    bool find_word(const std::string& word, size_t idx = 0) {
        if (idx == word.length())
            return word_end_;

        if (char_ == word[idx]) {
            bool ret = false;
            for (auto next : nexts_) {
                ret = next.find_word(word, idx + 1);
                if (ret == true) return true;
            }
        }
        return false;
    }

    bool remove_word(const std::string& word, bool& remove_node, size_t idx = 0) {
        if (idx == word.length()) {
            if (word_end_)
                word_db::instance().remove_word(word);
            remove_node = word_end_;
            word_end_ = false;
            return remove_node;
        }

        if (char_ == word[idx]) {
            for (size_t i = 0; i < nexts_.size(); ++i) {
                if (nexts_[i].remove_word(word, remove_node, idx + 1)) {
                    if (remove_node) {
                        nexts_[i].swap(nexts_[nexts_.size() - 1]);
                        nexts_.pop_back();
                    }
                    if (nexts_.size() != 0)
                        remove_node = false;
                    return true;
                }
            }
        }
        return false;
    }

    void swap(trie_node& o) {
        this->char_ = o.char_;
        nexts_.swap(o.nexts_);
        word_end_ = o.word_end_;
    }

    char get_char() { return char_; }
};

class trie {
    std::vector<trie_node> word_starts_;
    trie() {
        auto itr = word_db::instance().word_2_pos_info().begin();
        while (itr != word_db::instance().word_2_pos_info().end()) {
            bool processed = false;
            for (auto& node : word_starts_)
                if (node.get_char() == itr->first[0]) {
                    node.add_word(itr->first);
                    processed = true;
                    break;
                }
            if (!processed) {
                word_starts_.push_back(trie_node());
                word_starts_[word_starts_.size() - 1].add_word(itr->first);
            }
            ++itr;
        }
    }

    static trie* instance_;

public:

    void add_word(const std::string& word) {
        auto itr = word.find(' ');
        if (itr != std::string::npos) return; //string contains spaces
        if (word.length() <= 0) return;
        for (auto& node : word_starts_)
            if (node.get_char() == word[0]) {
                node.add_word(word);
                return;
            }
        word_starts_.push_back(trie_node());
        word_starts_[word_starts_.size() - 1].add_word(word);
    }

    void remove_word(const std::string& word) {
        if (word.length() <= 0) return;
        for (auto& node : word_starts_)
            if (node.get_char() == word[0]) {
                bool remove_node = false;
                node.remove_word(word, remove_node);
                return;
            }
    }

    bool find_word(const std::string& word) {
        if (word.length() <= 0) return false;
        for (auto& node : word_starts_)
            if (node.get_char() == word[0]) {
                return node.find_word(word);
            }

        return false;
    }

    static trie& instance() {
        if (instance_ == nullptr){
            instance_ = new trie();
        }
        return *instance_;
    }
};

