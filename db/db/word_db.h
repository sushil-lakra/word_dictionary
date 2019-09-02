#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>

class word_db {
    struct pos_info {
        std::streampos position_;
        size_t size_;
        pos_info(std::streampos pos, size_t size) :
            position_{ pos }, size_{ size }{}
        pos_info() : position_{ -1 }, size_{ (size_t)-1 }{}
    };

    std::string dir_;
    std::fstream fs_;
    std::streampos last_pos_;
    static word_db* instance_;
    std::multimap<size_t, std::streampos> free_size_2_offset_;
    std::unordered_map<std::string, pos_info> word_2_pos_info_;

    word_db()   : dir_{ "./db" }
                , fs_{}
                , last_pos_{ 0 }
                , free_size_2_offset_{}
                , word_2_pos_info_{} {
        std::string file_name = "persistence";
        fs_.open(file_name, std::ios::in | std::ios::out);
        if (!fs_.is_open()) {
            std::cout << "couldn't open file" << std::endl;
            return;
        }

        fs_.seekp(0, std::ios_base::end);
        last_pos_ = fs_.tellp();
        fs_.seekp(0);
        std::string line;
        std::streampos pos = 0;
        char is_free;
        if (last_pos_ != 0) {
            while (fs_.get(is_free)) {
                std::getline(fs_, line);
                if (is_free == 'n') {
                    word_2_pos_info_[line] = pos_info(pos, line.size());
                }
                else {
                    free_size_2_offset_.insert(std::make_pair(line.size(), pos));
                }
                pos = fs_.tellp();
                if (pos == last_pos_) break;
            }
        }
    }

    ~word_db() {
        fs_.close();
    }
public:

    std::unordered_map<std::string, pos_info>& word_2_pos_info(){
        return word_2_pos_info_;
    }
    void uninit() {
        delete instance_;
    }

    void print() {
        auto itr = word_2_pos_info_.begin();
        while (itr != word_2_pos_info_.end()) {
            std::cout << itr->first << std::endl;
            ++itr;
        }
    }

    bool has_word(const std::string& w) {
        auto itr = word_2_pos_info_.find(w);
        return itr != word_2_pos_info_.end();
    }

    void add_word(const std::string& w) {
        if (word_2_pos_info_.find(w) != word_2_pos_info_.end())
            return;
        auto itr = free_size_2_offset_.find(w.size());
        if (itr != free_size_2_offset_.end()) {
            fs_.seekp(itr->second);
            free_size_2_offset_.erase(itr);
        } else {
            fs_.seekp(0, std::ios_base::end);
        }
        auto pos = fs_.tellp();
        fs_ << 'n';
        fs_ << w;
        fs_ << "\n";
        word_2_pos_info_[w] = pos_info(pos, w.size());
    }

    void remove_word(const std::string& w) {
        auto itr = word_2_pos_info_.find(w);
        if (itr == word_2_pos_info_.end()) {
            std::cout << "word doesn't exist" << std::endl;
            return;
        }
        fs_.seekp(itr->second.position_);
        fs_ << 'y';
        free_size_2_offset_.insert(std::make_pair(w.size(), itr->second.position_));
        word_2_pos_info_.erase(w);
    }

    static word_db& instance() {
        if (instance_ == nullptr)
            instance_ = new word_db();
        return *instance_;
    }
};
