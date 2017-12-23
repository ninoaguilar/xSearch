# SearchEngine

**Clone and run for a quick way to see in action.**

## Reading files

In order to read files being input, files must be stored in TextDocuments file and have the extension .txt and be in the format cranfield00XX.txt


## To Use

From your command line:

```bash
# Clone this repository
git clone https://github.com/ninoaguilar/xSearch.git
# Go into the repository
cd xSearch
# Create a build directory
mkdir build
# Go into the build directory
cd build
# Run the program
cmake ../src
make
./xSearch
```


## Running

project should ask for input after proper build.

displayed should be:
```bash
------------------------------
Enter search term: [enter your search terms here]
```


## Searching tips

* Anything that is not a letter was not stored in hash, therefore, it cannot be searched for.
* Terms such as “flow stream” will be interpreted as “flow and stream”.
* Any length search term can be used.

## License

[GNU GENERAL PUBLIC LICENSE](LICENSE)