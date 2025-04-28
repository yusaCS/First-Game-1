# Dungeon Crawler Game (C++)

## 🌍 Project Overview
Welcome adventurer! This is a classic **Dungeon Crawler** text-based game written in C++. You control an explorer who must find treasures, avoid monsters, and navigate through multiple levels of dungeons to escape safely.

The project features:
- Dynamic map loading from text files
- Player movement mechanics (up, down, left, right, stay)
- Resizing dungeon maps with magical amulets
- Intelligent monster behavior (chasing you based on line of sight)
- Treasure collection and victory conditions
- Dynamic memory management (manual `new` and `delete`)
- Test cases for core functionalities

---

## 🔧 How to Compile and Run
### Requirements:
- C++ compiler (e.g., `g++`, `clang++`, or Visual Studio)
- C++11 standard or newer

### Compile:
If you are using `g++`, run this command in your project directory:
```bash
# Compile the main game
g++ dungeoncrawler.cpp logic.cpp helper.cpp -o dungeon_crawler

# (Optional) Compile the test file
g++ dctests.cpp logic.cpp -o dungeon_tests
```

### Run:
```bash
# Run the game
./dungeon_crawler

# (Optional) Run the tests
./dungeon_tests
```

---

## 🌐 Gameplay Instructions
- Your objective is to **collect at least one treasure** and **escape the dungeon**.
- Each level is loaded from a `.txt` file.
- Movement keys:
  - `w` = Move Up
  - `a` = Move Left
  - `s` = Move Down
  - `d` = Move Right
  - `e` = Stay Still
  - `q` = Quit Game

- Special Tiles:
  - `o` : Player (you!)
  - `$` : Treasure
  - `@` : Amulet (resizes dungeon)
  - `M` : Monster (avoid them!)
  - `+` : Pillar (unpassable obstacle)
  - `?` : Door to the next level
  - `!` : Exit door (requires treasure to leave)

- Watch out! Monsters move towards you if they see you in a straight line!

---

## 📚 Project Structure
| File | Description |
|:----|:------------|
| `logic.h` | Game logic declarations and constants |
| `logic.cpp` | Core gameplay logic (player movement, monster behavior, map management) |
| `helper.h` | Helper function declarations |
| `helper.cpp` | Display functions for map and instructions |
| `dungeoncrawler.cpp` | Main game loop |
| `dctests.cpp` | Unit tests for core logic functions |
| `example1.txt` (add) | Sample dungeon level file |

---

## 🌐 Example Dungeon File Format
You need `.txt` files to define each dungeon level.
Example format (`example1.txt`):
```
5 3
3 0
M + -
- + -
- + !
- - -
@ - $
```
Explanation:
- First line: `5 3` -> 5 rows, 3 columns
- Second line: `3 0` -> Player starts at (row 3, column 0)
- Following lines: Dungeon layout with special characters

Each new level should have its own text file (e.g., `dungeon1.txt`, `dungeon2.txt`, etc.)

---

## 🔍 Future Improvements (Optional Ideas)
- Add different types of monsters with unique behaviors.
- Introduce player health and combat mechanics.
- Save/load dungeon progress to files.
- Create a graphical interface with SDL or SFML.
- Add multiple difficulty levels.

---

## ✍️ Credits
This project was developed by [Your Name Here].

Feel free to fork, contribute, and improve the game!

---

## 📊 License
This project is licensed under the [MIT License](LICENSE) — free to use and modify.

---

# 🎉 Happy Crawling, Adventurer! 🗿

