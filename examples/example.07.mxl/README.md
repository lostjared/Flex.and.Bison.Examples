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

Or use the the wrapper class like htis

mxl::MXL *parser = mxl::MXL::parseMXL("code.mxl");

don't forget to delete parser when done or use a smart pointer

std::unique_ptr<mxl::MXL> parser(mxl::MXL::parseMXL("source.mxl"));

if(parser) {

// use parser
  
 if(parser->keyValid("Size", "int")) {

        std::string val = parser->table("Size", "int");

        std::cout << "Found Size value is: " << val << "\n";

    }

}
