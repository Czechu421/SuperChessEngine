# SuperChessEngine

### Features
* Uses UCI commands to communicate.
  * Tested with [LichessBot](https://github.com/lichess-bot-devs/lichess-bot).
* Supports multithreading.
* Uses negamax algorithm at depth specified in uci command.
* Evaluates position based on material and position of each piece.

### Prerequisites
- Visual Studio 2019 or later
- C++ version 17

### Usage
Tested and built in Visual Studio. C++ version is 17. Follow these steps to clone and build the repository:

1. Clone the repository:
    ```sh
    git clone https://github.com/Czechu421/SuperChessEngine.git
    ```
2. Open the project in Visual Studio.
3. Select the release version.
4. Build the project. The executable file should be in `yourRepoDirectory/x64/release/SuperChessEngine.exe`.

### Testing Environment
* **CPU**: Intel i5-12400
* **Memory**: 32 GB DDR5-6400
* **OS**: Windows 11 24H2

### Additional Notes
Based on [chess-library](https://github.com/Disservin/chess-library)

### License
This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.
