#include <iostream>
#include <vector>
#include <json/json.h>

#ifndef VATSIM_MANAGER_CLIENTSTATE_H
#define VATSIM_MANAGER_CLIENTSTATE_H


class clientstate {
public:
    int createState();
    std::vector<std::string> parseState();
private:
    std::vector<std::vector<std::string>> checkClients();

    //https://stackoverflow.com/questions/26773043/how-to-write-a-template-converts-vector-to-jsonvalue-jsoncpp
    template <typename Iterable>
    Json::Value vectorToJson(Iterable const& cont) {
        Json::Value v;
        for (auto&& element: cont) {
            v.append(element);
        }
        return v;
    }

};


#endif //VATSIM_MANAGER_CLIENTSTATE_H
