#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

struct bingo_entry {
  int value;
  bool checked;
};

struct bingo {
  vector<int> entry;
  vector<vector<vector<bingo_entry>>> tables;
};

vector<vector<bingo_entry>> empty_table(5, vector<bingo_entry>(5, {value: 0, checked: false}));

void populate_bingo_file(ifstream *file, struct bingo *bingo) {
  string input;
  regex space_reg("\\s+");
  regex comma_reg(",");

  if(!file->is_open()) {
    cout << "Couldn't open file\n";
    return;
  }

  getline(*file, input);
  regex_token_iterator<string::iterator> iter(input.begin(), input.end(), comma_reg, -1);
  regex_token_iterator<string::iterator> end;

  for(int i=0; iter != end; ++i) {
    string entry_string = *iter++;

    bingo->entry.push_back(atoi(entry_string.c_str()));
  }
  
  for(int i=0; *file; ++i) {
    bingo->tables.push_back(empty_table);

    // remove empty line from table
    getline(*file, input);
    for(int j = 0; j < 5; ++j) {
      getline(*file, input);
      regex_token_iterator<string::iterator> iter(input.begin(), input.end(), space_reg, -1);
      regex_token_iterator<string::iterator> end;

      int k = 0;
      while(iter != end) {
        string test = *iter++;
        if(test.empty()) {

          continue;
        }
        bingo->tables[i][j][k] = {value: atoi(test.c_str()), checked: false};
        k++;
      }
    }
  }
  bingo->tables.pop_back();

}

// TODO: find winner value
int check_winner(struct bingo *bingo, int value_to_find) {
  // check input with entry values
  for(int i=0; i < bingo->tables.size(); ++i) {
    for(int j=0; j < bingo->tables[i].size(); ++j) {
      for(int k=0; k < bingo->tables[i][j].size(); ++k) {
        if(bingo->tables[i][j][k].value == value_to_find) {
          bingo->tables[i][j][k].checked = true;
        }
      }
    }
  }

  int i,j,k;
  for(i=0; i < bingo->tables.size(); ++i) {
    for(j=0; j < bingo->tables[i].size(); ++j) {
      bool found_row = true;
      bool found_col = true;

      for(k=0; k < bingo->tables[i][j].size(); ++k) {
        if(!bingo->tables[i][k][j].checked) {
          found_row = false;
        }

        if(!bingo->tables[i][j][k].checked) {
          found_col = false;
        }
      }
      if(found_row) {
        cout << "FOUND COL: " << " table: " << i << " index: " << j << endl << endl;
        int sum_of_unchecked = 0;
        for(int l=0; l < bingo->tables[i].size(); ++l) {
          for(int m=0; m < bingo->tables[i][l].size(); ++m) {
            if(bingo->tables[i][l][m].checked == false) {
              sum_of_unchecked += bingo->tables[i][l][m].value;
            }
          }
        }
        return sum_of_unchecked;
      }

      if(found_col) {
        cout << "FOUND ROW: " << " table: " << i << " index: " << j << endl << endl;
        int sum_of_unchecked = 0;
        for(int l=0; l < bingo->tables[i].size(); ++l) {
          for(int m=0; m < bingo->tables[i][l].size(); ++m) {
            if(bingo->tables[i][l][m].checked == false) {
              sum_of_unchecked += bingo->tables[i][l][m].value;
            }
          }
        }
        return sum_of_unchecked;
      }
    }
  }
  return -1;
}

void print_bingo(struct bingo *bingo) {
  for(int i=0; i < bingo->entry.size(); ++i) {
    cout << bingo->entry[i] << ',';
  }
  cout << endl << endl;


  for(int i=0; i < bingo->tables.size(); ++i) {
    for(int j=0; j < bingo->tables[i].size(); ++j) {
      for(int k=0; k < bingo->tables[i][j].size(); ++k) {
        cout << '[' << bingo->tables[i][j][k].value << " " << bingo->tables[i][j][k].checked << "]";
      }
      cout << endl;
    }
    cout << endl;
  }
}

int main(int argc, char *argv[]) {
  ifstream inputFile (argv[1]);
  struct bingo bingogame;

  populate_bingo_file(&inputFile, &bingogame);

  for(int i=0; i < bingogame.entry.size(); ++i) {
    int value_to_find = bingogame.entry[i];
    int winner = check_winner(&bingogame, value_to_find);
    if(winner > 0) {
      cout << "\n WINNER score is: " << winner * value_to_find << endl;
      break;
    }
  }

  print_bingo(&bingogame);

  return EXIT_SUCCESS;
}