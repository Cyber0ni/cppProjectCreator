//@author Cyber0ni
#include <iostream>
#include <fstream>

typedef const char* str;
typedef unsigned int uint;

int strsSize(str);
str strCopy(char*, str);

template <typename ...Arg> int strsSize(str, Arg...);
template <typename ...Arg> str strCopy(char*, str, Arg...);
template <typename ...Arg> str strCat(Arg...); 

int main(int argc, str* argv) {
    if(argc == 1) {
        std::cout << "Project name argument is empty";
        return -1;
    }

    str dir       = strCat("mkdir ", argv[1]),
        src       = strCat("mkdir ", argv[1], "/src"),
        bin       = strCat("mkdir ", argv[1], "/bin"),
        lib       = strCat("mkdir ", argv[1], "/lib"),
        include   = strCat("mkdir ", argv[1], "/include");
        
    system(dir);
    delete [] dir;
    system(src);
    delete [] src;
    system(bin);
    delete [] bin;
    system(lib);
    delete [] lib;
    system(include);
    delete [] include;

    str make      = strCat(argv[1], "/Makefile"),
        creatMake = strCat("touch ", make);
    
    system(creatMake);
    delete [] creatMake;

    std::ofstream makeFile(make); 
    delete [] make; 

    makeFile << "CXX		 := g++\n"
             <<	"DEBUG_FLAGS     := -g -pedantic-errors -Wall -Wextra -Werror\n"
             << "RELEASE_FLAGS   := -s -O3 -w\n\n" 
             << "BIN             := bin\n"
             << "INCLUDE         := -Iinclude\n"
             << "LIB             := -Llib\n"
             << "LIBS            :=\n"
             << "SRC             := src\n"
             << "NAME            := " << argv[1] << "\n\n\n"
             << "all: debug\n\n"
             << "run: all\n"
             << "\t$(BIN)/$(NAME)\n\n"
             << "debug: $(SRC)/*.cpp\n"
             << "\t$(CXX) $(DEBUG_FLAGS) $(INCLUDE) $(LIB) $(LIBS) $^ -o $(BIN)/$(NAME)\n\n"
             << "release: $(SRC)/*.cpp\n"
             << "\t$(CXX) $(RELEASE_FLAGS) $(INCLUDE) $(LIB) $(LIBS) $^ -o $(BIN)/$(NAME)\n\n"
             << "clean:\n"
             << "\trm $(BIN)/$(NAME)";
    
    
    str mainCpp   = strCat(argv[1], "/src/main.cpp"),
        creatMain = strCat("touch ", mainCpp);
    
    system(creatMain);
    delete [] creatMain;

    std::ofstream mainFile(mainCpp);
    delete [] mainCpp;

    mainFile << "int main() {\n"
             << "\treturn 0;\n"
             << "}";

    return 0;
}


int strsSize(str s) {
    uint l = 0;
    while(s[l] != '\0') {
        ++l;
    }
    return l; 
}

template <typename ...Arg> int strsSize(str s, Arg... args) {
    uint l = 0;
    while(s[l] != '\0') {
        ++l;
    }
    return l + strsSize(args...); 
}

str strCopy(char* s, str sCopy) {   
    uint l = 0, i = 0;
    while(s[i] != '\0') {
        ++i;
    }
    while(sCopy[l] != '\0') {
        s[l + i] = sCopy[l];
        ++l;
    }
    s[l + i] = '\0';
    return s; 
}

template <typename ...Arg> str strCopy(char* s, str sCopy, Arg... copyArgs) {
    strCopy(s, sCopy);
    return strCopy(s, copyArgs...);
}

template <typename ...Arg> str strCat(Arg... strs) {
    char* result = new char[strsSize(strs...) + 1]{};
    strCopy(result, strs...);
    return str(result);
}
