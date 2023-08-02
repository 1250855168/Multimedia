#include <cstdlib>
#include <ctime>
#include <chrono> // 添加计时器所需的头文件
#include <iostream>
using namespace std;
using namespace std::chrono;

const int ROWS = 8;
const int COLS = 8;
const int NUM_TYPES = 5;
const int PLAY_TIME = 180; // 游戏时间（秒）

// 判断是否存在可消除的方块
bool has_matches(int board[][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int count = 1;
      while (j + count < COLS && board[i][j + count] == board[i][j]) {
        count++;
      }
      if (count >= 3) {
        return true;
      }
      count = 1;
      while (i + count < ROWS && board[i + count][j] == board[i][j]) {
        count++;
      }
      if (count >= 3) {
        return true;
      }
    }
  }
  return false;
}

// 初始化游戏面板
void init_board(int board[][COLS]) {
  srand(time(0));
  while (true) {
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        board[i][j] = rand() % NUM_TYPES;
      }
    }
    if (!has_matches(board)) {
      break;
    }
  }
}

// 打印游戏面板
void print_board(int board[][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

// 交换方块
void swap_blocks(int board[][COLS], int row1, int col1, int row2, int col2) {
  int temp = board[row1][col1];
  board[row1][col1] = board[row2][col2];
  board[row2][col2] = temp;
}

// 消除方块并填充新的方块
int eliminate_blocks(int board[][COLS], int& score) {
  int num_matches = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int count = 1;
      while (j + count < COLS && board[i][j + count] == board[i][j]) {
        count++;
      }
      if (count >= 3) {
        for (int k = j; k < j + count; k++) {
          score += 10; // 每消除一个方块得10分
          board[i][k] = -1; // 标记为待删除
        }
        num_matches++;
      }
      count = 1;
      while (i + count < ROWS && board[i + count][j] == board[i][j]) {
        count++;
      }
      if (count >= 3) {
        for (int k = i; k < i + count; k++) {
          score += 10; // 每消除一个方块得10分
          board[k][j] = -1; // 标记为待删除
        }
        num_matches++;
      }
    }
  }

  // 填补空位
  for (int j = 0; j < COLS; j++) {
    int k = ROWS - 1;
    for (int i = ROWS - 1; i >= 0; i--) {
      if (board[i][j] != -1) {
        board[k][j] = board[i][j];
        k--;
      }
    }
    while (k >= 0) {
      board[k][j] = rand() % NUM_TYPES;
      k--;
    }
  }

  return num_matches;
}

int main() {
  int board[ROWS][COLS];
  init_board(board);
  print_board(board);

  // 计时器和得分变量
  time_point<system_clock> start_time = system_clock::now(); // 获取起始时间
  int score = 0;

  while (true) {
    // 检查游戏时间
    time_point<system_clock> now_time = system_clock::now();
    int elapsed_time= duration_cast<seconds>(now_time - start_time).count(); // 计算已经过去的时间（秒）
    if (elapsed_time >= PLAY_TIME) {
      cout << "Time's up!" << endl;
      break;
    }

    // 获取用户输入
    int row1, col1, row2, col2;
    cout << "Enter the row and column of the first block to swap: ";
    cin >> row1 >> col1;
    cout << "Enter the row and column of the second block to swap: ";
    cin >> row2 >> col2;

    // 检查用户输入是否合法
    if (row1 < 0 || row1 >= ROWS || col1 < 0 || col1 >= COLS ||
        row2 < 0 || row2 >= ROWS || col2 < 0 || col2 >= COLS) {
      cout << "Invalid input. Please try again." << endl;
      continue;
    }
    if ((abs(row1 - row2) == 1 && col1 == col2) ||
        (abs(col1 - col2) == 1 && row1 == row2)) {
      // 交换方块
      swap_blocks(board, row1, col1, row2, col2);

      // 消除方块并填充新的方块
      int num_matches = eliminate_blocks(board, score);
      if (num_matches > 0) {
        cout << "Matches found: " << num_matches << endl;
        cout << "Score: " << score << endl;
        print_board(board);
      } else {
        cout << "No matches found. Please try again." << endl;
        // 恢复交换前的状态
        swap_blocks(board, row1, col1, row2, col2);
      }
    } else {
      cout << "Invalid input. Please try again." << endl;
    }
  }

  return 0;
}