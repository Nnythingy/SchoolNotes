// This code uses new C++17 structured binding
// use this compiler setting "g++ -O2 -std=gnu++17 {cpp17file}"

#include <bits/stdc++.h>
using namespace std;

const int M = 13; // M = table size is a prime number, rather small, for illustration purpose only, generally make load factor alpha = N/M < 7 (just a small number) where N is the maximum number of keys that you will likely need for your application

class hash_table { // this is an attempt to emulate unordered_map<string, int> mapper;
// the 'easiest' and most robust Hash Table is actually the one with Separate Chaining collision resolution technique
private:
  // interesting (new) technique, we can create an array (or vector) of another STLs, here we have an array of std::list (of pair of (string, int))
  list<pair<string, int>> underlying_table[M]; // you can change list to vector :O

  // from https://visualgo.net/en/hashtable?slide=4-7
  int hash_function(string v) { // assumption 1: v uses ['A'..'Z'] only (be careful if this assumption is not true); assumption 2: v is a short string
    int sum = 0;
    for (auto &c : v) { // for each character c in v
      sum = ((sum*26)%M + (c-'A'+1))%M; // M is table size
    }
    return sum;
  }

public:
  hash_table() {
    for (int i = 0; i < M; ++i)
      underlying_table[i].clear(); // clear the linked list
  }

  void insert(string key, int value) { // to emulate mapper[key] = value
    bool contains_key = false;
    for (auto &[k, v] : underlying_table[hash_function(key)])
      if (k == key) { // if there is an existing key
        contains_key = true;
        v = value; // update the satellite data, notice that we use pass by reference '&' above
      }
 
    if (!contains_key) // no previous key before
      underlying_table[hash_function(key)].emplace_back(key, value); // just append at the back
  }

  int search(string key) { // to emulate mapper[key]
    for (auto &[k, v] : underlying_table[hash_function(key)]) // O(k), k is the length of this list, but with careful setup, k can be O(1)
      if (k == key) // if there is an existing key
        return v; // return this satellite data
 
    // if there is no previous key before (return v above is never executed)
    return -1; // we return a special symbol to say such key does not exist
  }

  void remove(string key) { // to emulate mapper.erase(key)
    auto &row = underlying_table[hash_function(key)]; // get the reference of the row, notice that we use pass by reference '&' (VERY IMPORTANT)

    for (auto it = row.begin(); it != row.end(); ++it)
      if (it->first == key) { // if there is an existing key
        row.erase(it); // erase this (key, value) pair from this vector
        break; // do not do anything else
      }

    // we do nothing if key is not actually found
  }

  bool is_empty() {
    int total = 0;
    for (int i = 0; i < M; ++i)
      total += (int)underlying_table[i].size();
    return (total == 0);
  }
};

int main() {
  cout << "Our own Hash Table with Separate Chaining collision resolution technique\n";
  hash_table ht;
  cout << ht.is_empty() << "\n"; // should be 1/true

  ht.insert("STEVEN", 77);
  cout << ht.is_empty() << "\n"; // should be 0/false

  ht.insert("STEVEN", 38); // will update instead of creating a new one
  ht.insert("GRACE", 37);
  ht.insert("JANE", 9);
  ht.insert("JOSHUA", 6);
  ht.insert("JEMIMAH", 3);
  cout << ht.search("STEVEN") << "\n"; // should be 38 (not 77, it has been overwritten)
  cout << ht.search("GRACE") << "\n"; // should be 37
  cout << ht.search("STRANGER") << "\n"; // should be -1 (does not exist)

  ht.remove("STEVEN");
  cout << ht.search("STEVEN") << "\n"; // should be -1 now (has just been deleted)
  cout << ht.search("GRACE") << "\n"; // should remain 37
  cout << ht.search("JANE") << "\n"; // should be 9

  ht.remove("JANE");
  cout << ht.search("JANE") << "\n"; // should be -1 now (has just been deleted)

  cout << "C++ STL version\n";
  unordered_map<string, int> mapper;
  cout << mapper.empty() << "\n"; // should be 1/true

  mapper["STEVEN"] = 77;
  cout << mapper.empty() << "\n"; // should be 0/false

  mapper["STEVEN"] = 38; // will update instead of creating a new one
  mapper["GRACE"] = 37;
  mapper["JANE"] = 9;
  mapper["JOSHUA"] = 6;
  mapper["JEMIMAH"] = 3;
  cout << mapper["STEVEN"] << "\n"; // should be 38 (not 77, it has been overwritten)
  cout << mapper["GRACE"] << "\n"; // should be 37
  cout << (mapper.find("STRANGER") == mapper.end() ? -1 : 1) << "\n"; // should be -1 ("STRANGER" does not exist)

  mapper.erase("STEVEN");
  cout << (mapper.find("STEVEN") == mapper.end() ? -1 : 1) << "\n"; // should be -1 (has just been deleted)
  cout << mapper["GRACE"] << "\n"; // should remain 37
  cout << mapper["JANE"] << "\n"; // should be 7

  mapper.erase("JANE");
  cout << (mapper.find("JANE") == mapper.end() ? -1 : 1) << "\n"; // should be -1 now (has just been deleted)

  return 0;
}
