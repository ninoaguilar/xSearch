# SearchEngine

**Clone and run for a quick way to see in action.**

## Reading files

In order to read the files to be search, the files must be stored in the `TextDocuments` folder and have the extension `.txt` and be in the format `cranfield00XX.txt`.


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

Project should ask for input after proper build.

Displayed should be:
```bash
███████╗███████╗ █████╗ ██████╗  ██████╗██╗  ██╗
██╔════╝██╔════╝██╔══██╗██╔══██╗██╔════╝██║  ██║
███████╗█████╗  ███████║██████╔╝██║     ███████║
╚════██║██╔══╝  ██╔══██║██╔══██╗██║     ██╔══██║
███████║███████╗██║  ██║██║  ██║╚██████╗██║  ██║
╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝
By: Nino Aguilar


------------------------------
Enter search term: [enter your search terms here]
```


## Searching tips

* Anything that is not a letter was not stored in hash, therefore, it cannot be searched for.
* Terms such as “flow stream” will be interpreted as “flow and stream”.
* Any length search term can be used.

## License

[GNU GENERAL PUBLIC LICENSE](LICENSE)