#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void find(fs::path path, std::string& file_name){
    for(auto& item : fs::directory_iterator(path)){
        if(item.is_directory()){
            find(fs::absolute(item.path()), file_name);
        }
        if(item.is_regular_file()){
            if(item.path().filename() == file_name){
                std::cout << "Found it: " << fs::absolute(item.path()) << std::endl;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    fs::path p = argv[1];
    std::string file_name = argv[2];

    find(p, file_name);

    return 0;
}
