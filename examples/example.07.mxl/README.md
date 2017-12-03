// example 07

Implementation of a parser for INI like text files.
type

$ make

to build the project

or

$ make flex

to rebuild the files with flex/bison

Simple tagging language use it like this:

Cateogry =>

"Key" = "value"

Width = "200"

Height = "400"

User =>

firstname = "Jared"

lastname = "Bruni"

Keys/Values can be accessed by adding project files (except main) and 
parsing the text with readSource("filename.mxl");
Then use


std::string value=getValue("Category", "Width");

value would hold "200"

