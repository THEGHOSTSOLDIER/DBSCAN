# DBSCANRework
[![C++](https://img.shields.io/badge/language-C%2B%2B-%23f34b7d.svg?style=plastic)](https://en.wikipedia.org/wiki/C%2B%2B) 
[![Windows](https://img.shields.io/badge/platform-Windows-0078d7.svg?style=plastic)](https://en.wikipedia.org/wiki/Microsoft_Windows)
[![x64](https://img.shields.io/badge/arch-x64-red.svg?style=plastic)](https://en.wikipedia.org/wiki/X86-64) 

A data clustering algorithm written in C++ from scratch to understand DBSCAN.

## Getting started

### Prerequisites
Microsoft Visual Studio 2022 17.2.2 (or newer), Python (2 or 3) with [matplotlib](https://matplotlib.org/) installed, platform toolset v143 and Windows SDK 10.0.x.x are required in order to compile the project. If you don't have ones, you can download VS [here](https://visualstudio.microsoft.com/) (Windows SDK is installed during Visual Studio Setup).

### Set up the project

Expand `C/C++`, add `"C:\Users\%USERNAME%\AppData\Local\Programs\Python\Python<your_python_version>\include"` and `"<PROJECT_PATH>\matplotlib-cpp-master"` to `Include Directories`

Expand `Linker`, click on `Input`, add `"C:\Users\%USERNAME%\AppData\Local\Programs\Python\Python<your_python_version>\libs\python<your_python_version>.lib"` to `Additional Dependencies`

## FAQ

### What is DBSCAN?
Curious? a lot of knowledge is waiting for you [here](https://en.wikipedia.org/wiki/DBSCAN)

## License

> Copyright (c) 2022 THEGHOSTSOLDIER

This project is licensed under the [MIT License](https://opensource.org/licenses/mit-license.php) - see the [LICENSE](https://github.com/THEGHOSTSOLDIER/DBSCANRework/blob/main/LICENSE) file for details.