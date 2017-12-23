███████╗███████╗ █████╗ ██████╗  ██████╗██╗  ██╗
██╔════╝██╔════╝██╔══██╗██╔══██╗██╔════╝██║  ██║
███████╗█████╗  ███████║██████╔╝██║     ███████║
╚════██║██╔══╝  ██╔══██║██╔══██╗██║     ██╔══██║
███████║███████╗██║  ██║██║  ██║╚██████╗██║  ██║
╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝
By Nino and Angelo

Bonus: We implemented the use of “stopwords.txt” in order
       to not store unwanted words

*Instructions on compiling and running search*

— Reading files -
  - In order to read files being input, files must
    be stored in TextDocuments file and have the
    extension .txt and be in the format cranfield00XX.txt

- Compiling -
  - files should be as according
	- hash.h
	- hash.cpp
	- main.cpp
	- stopwords.txt
	- TextDocuments
	     - cranfield0001.txt
	     - …

- Running -
  - project should ask for input after
    proper build
  - displayed should be:
   ------------------------------
   Enter search term: (enter your search terms here)

  - Searching tips
	- anything that is not a letter
          was not stored in hash therefore
	  cannot be searched for
	- terms such as “flow stream” will be
	  interpreted as “flow and stream”
	- any length search term can be used

