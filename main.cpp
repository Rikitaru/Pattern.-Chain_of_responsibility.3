#include <iostream>
#include <string>
#include <fstream>

const std::string SPECS[] = {"year","color","engine capacity","akpp//mkpp","engine power","fuel tank","fuel consumption","dimensions","heated steering wheel","abs","eds","navigation system","board computer","heated seats","roof rack","number of airbags"};

class handler
{
public:
    handler* next;
    std::string filename;   
    handler(std::string filename):filename(filename),next(nullptr){};
    void find_automobile(std::string model)
    {
        std::ifstream file(this->filename);
        bool found=false;
        std::string buf;
        while(std::getline(file,buf) && found==false)
        {
            if(model.compare(buf)==0)
            {
                found=true;
                std::cout << this->filename << ": found!" << std::endl;
                for(auto&& specification : SPECS)
                {
                    std::getline(file,buf);
                    std::cout << specification << " : " << buf << std::endl;
                }
            }
        }
        if(!found)
        {
            if(next!=nullptr){
                std::cout << this->filename << ": tryind to find deeper" << std::endl;
                next->find_automobile(model);
            }
            else
                std::cout << this->filename << ": not found :С" << std::endl;
        }
    }
    void set_next(handler* next_handler){this->next=next_handler;};

};


int main(int argc, char const *argv[])
{
    handler* salon = new handler("salon");
    salon->set_next(new handler("dealer"));
    salon->next->set_next(new handler("manufacture"));
    std::string model;
    std::cout << "Enter model to find:";
    std::cin >> model;
    salon->find_automobile(model);
    return 0;
}