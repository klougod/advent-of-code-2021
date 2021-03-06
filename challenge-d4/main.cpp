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

void printRed(int str) {
  printf("\33[38;2;255;0;0m %2d \33[m", str);
};

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

vector<int> known_i;

int check_winner_part1(struct bingo *bingo, int value_to_find) {
  for(int i=0; i < bingo->tables.size(); ++i) {
    for(int j=0; j < bingo->tables[i].size(); ++j) {
      for(int k=0; k < bingo->tables[i][j].size(); ++k) {
        if(bingo->tables[i][j][k].value == value_to_find) {
          bingo->tables[i][j][k].checked = true;
        }
      }
    }
  }

  int sum_of_unchecked = 0;

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
        if (find(known_i.begin(), known_i.end(), i) == known_i.end()) {
          known_i.push_back(i);
          sum_of_unchecked = 0;
          for(int l=0; l < bingo->tables[i].size(); ++l) {
            for(int m=0; m < bingo->tables[i][l].size(); ++m) {
              if(bingo->tables[i][l][m].checked == false) {
                sum_of_unchecked += bingo->tables[i][l][m].value;
              }
            }
          }
          if(i == 44) {
            cout << "VALUE TO FIND: " <<  value_to_find << " soma: " << sum_of_unchecked << endl;
          }
        }
      }

      if(found_col) {
        if (find(known_i.begin(), known_i.end(), i) == known_i.end()) {
          known_i.push_back(i);
          sum_of_unchecked = 0;
          for(int l=0; l < bingo->tables[i].size(); ++l) {
            for(int m=0; m < bingo->tables[i][l].size(); ++m) {
              if(bingo->tables[i][l][m].checked == false) {
                sum_of_unchecked += bingo->tables[i][l][m].value;
              }
            }
          }
          if(i == 44) {
            cout << "VALUE TO FIND: " <<  value_to_find << " soma: " << sum_of_unchecked << endl;
          }
        }
      }
    }
  }

  return sum_of_unchecked;
}

void print_bingo(struct bingo *bingo) {
  for(int i=0; i < bingo->entry.size(); ++i) {
    cout << bingo->entry[i] << ',';
  }
  cout << endl << endl;


  for(int i=0; i < bingo->tables.size(); ++i) {
    for(int j=0; j < bingo->tables[i].size(); ++j) {
      for(int k=0; k < bingo->tables[i][j].size(); ++k) {
        if(bingo->tables[i][j][k].checked) {
          printRed(bingo->tables[i][j][k].value);
        } else {
          printf(" %2d ", bingo->tables[i][j][k].value);
        }
      }
      cout << endl;
    }
    cout << endl;
  }
}

int main(int argc, char *argv[]) {
  if(!argv[1]) {
    printf("Please provide a valid filepath\n");
    exit(1);
  }

  ifstream inputFile (argv[1]);
  struct bingo bingogame;

  populate_bingo_file(&inputFile, &bingogame);

  for(int i=0; i < bingogame.entry.size(); ++i) {
    int value_to_find = bingogame.entry[i];
    int winner = check_winner_part1(&bingogame, value_to_find);
    if(winner > 0) {
      cout << "\n WINNER PART1 score is: " << winner * value_to_find << endl;
      break;
    }
  }

  print_bingo(&bingogame);

  known_i.clear();

  for(int i=0; i < bingogame.entry.size(); ++i) {
    int value_to_find = bingogame.entry[i];
    int winner = check_winner_part1(&bingogame, value_to_find);
  }

  int last = known_i.back();

  print_bingo(&bingogame);

  return EXIT_SUCCESS;
}
