#include "Server.h"
#include <iostream>

#include <boost/thread.hpp>

#include "util/FileIO.h"

#include <functional>
bool is_number(const std::string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void DLCServer::start() {
    mServer.config.port = 20046;

    // All possible Requests
    mServer.resource["^/champ$"]["GET"] = [this](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request){
        Member champion = mHexDLC.getChampion();
        std::string weights = FileIO::doubleArrayToString(champion.getNetwork().getWeights());        
        *response << makeResponse("200 OK", weights);
    };

    mServer.resource["^/gencount$"]["GET"] = [this](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request){
        long int generationCount = mHexDLC.getGenerationCount();
        
        *response << makeResponse("200 OK", std::to_string(generationCount));
    };

    mServer.resource["^/gencount$"]["POST"] = [this](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request){
        std::string newGenCount = request->content.string();   
        if(is_number(newGenCount)){
            mHexDLC.setGenerationCount(std::stoi(newGenCount));
            *response << makeResponse("200 OK", newGenCount);
        }
        else{
            *response << makeResponse("400 Bad Request", "Can only set generation count to positive integer");
        }
    };


    mServer.resource["^/population$"]["GET"] = [this](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request){
        std::string population = mHexDLC.getPopulation().save();
        *response << makeResponse("200 OK", population);
    };

    mServer.resource["^/runtime$"]["GET"] = [this](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request){
        std::string runTime = std::to_string(mHexDLC.getRunningTime());
        *response << makeResponse("200 OK", runTime);
    };

	boost::thread([this]() {
        mServer.start();
    });

	mHexDLC.run();
}

std::string DLCServer::makeResponse(std::string status, std::string content){
    return "HTTP/1.1 " + status + "\r\nContent-Length: " + std::to_string(content.size()) + "\r\n\r\n" + content;
}
