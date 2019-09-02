#word_dictionary

trie -
	deals with words, maintains trie nodes for all the words.
	methods :
		add_word
		remove_word
		find_word
	improvements :
		currently words starting with new characters are stored in vector,
		and it can be replaced with a btree to get better performance.
		used vector because of better cache locality
word_db -
	db which handles persisting the words, this is done using file input/output to simulate database
	can be modified to access a database.
tests -
	trie tests show, usage of trie class, also para upload and search and removal of words.