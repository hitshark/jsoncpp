#include <iostream>
#include <fstream>
#include <string>
#include "json/json.h"

int main()
{
    // old style
    Json::Value root;
    Json::Reader reader;
    Json::FastWriter fwriter;
    Json::StyledWriter swriter;

    std::ifstream ifs("example.json");
    //std::string ifs("{\"uploaded\" : \"up000000\"}");

    if(!reader.parse(ifs, root)){
        std::cout<<"can't open example.json file"<<std::endl;
        exit(-1);
    }
    else{
        std::cout<<root["encoding"].asString()<<std::endl;
        std::cout<<root["indent"]["length"].asInt()<<std::endl;
    }
    int a = root["indent"].get("length", 2).asInt();

    std::string str = fwriter.write(root);
    std::ofstream ofs("example_fast_writer.json");
    ofs<<str;
    ofs.close();

    str = swriter.write(root);
    ofs.open("example_styled_writer.json");
    ofs<<str;
    ofs.close();


    // new style
    /*
    std::ifstream ifs("example.json");
    Json::Value root;
    //std::ifstream ifs_tmp("example.json");
    if(ifs){
        std::string line, jsonStr;
        while(getline(ifs, line)){
            jsonStr.append(line);
        }
        std::unique_ptr<Json::CharReader> const reader(Json::CharReaderBuilder().newCharReader());
        std::string errs;

        //stream or string method
        //Json::CharReaderBuilder rdr;
        //if(Json::parseFromStream(rdr, ifs_tmp, &root, &errs)){
        if(reader->parse(jsonStr.c_str(), jsonStr.c_str()+jsonStr.size(), &root, &errs)){
            auto length = root["indent"].get("length", 0).asInt();
            auto encode = root["encoding"].asString();
            std::cout<<"length: "<<length<<std::endl<<"encoding: "<<encode<<std::endl;

            if(root.isMember("plug-ins")){
                auto plugs = root["plug-ins"];
                for(auto x : plugs){
                    std::cout<<x.asString()<<std::endl;
                }
            }
        }
        else{
            std::cout<<errs<<std::endl;
        }
    }

    // stream writer
    std::unique_ptr<Json::StreamWriter> writer(Json::StreamWriterBuilder().newStreamWriter());
    writer->write(root, &std::cout);
    */
    return 0;
}
