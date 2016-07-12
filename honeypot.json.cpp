//
//  regex.cpp
//
//
//  Created by Andrew Mei on 3/5/16
//  Copyright (c) 2016 Andrew Mei. All rights reserved.
// This program allows you to parse a list of ip-address. It opens an file using fstream, and stores all the information in a
// string. It then iterates through the string through 1 of 2 functions depending on the user input. If you enter an IPv4 address
// which is normally designated through the format XXX.XXX.XXX.XXX which has the max string value of 15. The function called uses
// the regex library which is part of C++11 STL. A regex pattern is manually and painfully defined looking for similarities in the
//strings. If it finds a pattern, it would output the pattern onto the screen. This program manually goes through the entire json
// file which is inefficient, bigO(n), but stable. Program was tested on Linux and Windows through the g++, clang++,
// and visual studio ide.

#include <iostream>
#include <string>
#include <regex>
#include <fstream>
//#include <sys/stat.h>

//template<typename T>
void regex(std::string const& ip_address, std::string const& new_line)
{
    std::regex pattern(ip_address);
    pattern = ("\\\\\""+ ip_address + "\\\\" + "\",\\s*\\\\\"[a-zA-Z]+\\\\\":\\s*\\\\\"[0-9]{0,3}.[0-9]{0,3}.[0-9]{0,3}.[0-9]{0,3}\\\\\",\\s*\\\\\"[a-zA-Z]{0,20}\\\\\":\\s*\\\\\"[a-zA-Z]{0,7}\\\\\"[}]\",\\s*\"[a-z]{0,7}\"\\s*:\\s*\"[a-zA-Z]{0,4}.[a-zA-Z]{0,6}\"\\s*[}]" );
    auto begin = std::sregex_iterator(new_line.begin(), new_line.end(), pattern);
    auto end = std::sregex_iterator();      // iterator automatically points to end of string. auto is the preferred type
    
    while (begin != end){                //function is called when an IP address is inputed as a value. This regex pattern
        //std::cout << new_line;        // looks for the IP address in the file and outputs the rest of the string onto the console
        try                             // postcondition : returns IP address, connection type and channel
        {
            
            std::smatch match = *begin;
            std::smatch match2 = *begin;
            if (std::regex_search(new_line, match, pattern))
                std::cout << "IP address found " << match.str() << std::endl;
            else
                std::cerr << " error " << std::endl;
            
        }catch ( std::regex_error &e ){
            std::cout << ip_address << "not found " << std::endl;
        }
    }
    std::cout << "hi" << std::endl;
} //   \", \"connectionType\": \"initial\"}", "channel" : "amun.events" }
void regex_oid(std::string const& ip_address, std::string const& new_line)
{
    std::regex pattern(ip_address);
    pattern = (ip_address + "\"\\s*[}],\\s*\"[a-z]{0,5}\"\\s*:\\s*\"[a-zA-Z0-9]{0,8}[-][a-zA-Z0-9]{0,4}[-][a-zA-Z0-9]{0,4}[-][a-zA-Z0-9]{0,4}[-][a-zA-Z0-9]{0,12}\",\\s*\"[a-zA-Z]{0,9}\"\\s*:\\s*[{]\\s*\"[$][a-z]{0,4}\"\\s*:\\s*\"[0-9]{0,4}[-][0-9]{0,2}[-][a-zA-Z0-9]{0,5}:[0-9]{0,2}:[0-9]{1,2}.[0-9]{0,3}[+][0-9]{0,4}\"\\s*[}],\\s*\"[a-zA-Z]{0,10}\"\\s*:\\s*[a-zA-Z]{0,4},\\s*\"[a-zA-Z]{0,7}\"\\s*:\\s*\"[{]\\\\\"[a-zA-Z]{0,12}\\\\\":\\s[0-9]{0,5},\\s\\\\\"[a-zA-Z]{0,10}\\\\\":\\s[0-9]{0,3},\\s\\\\\"[a-zA-Z]{0,8}\\\\\":\\s*\\\\\"[0-9]{0,3}.[0-9]{0,3}.[0-9]{0,3}.[0-9]{0,3}\\\\\",\\s*\\\\\"[a-zA-Z]{0,13}\\\\\":\\s\\\\\"[0-9]{0,3}.[0-9]{0,3}.[0-9]{0,3}.[0-9]{0,3}\\\\\",\\s\\\\\"[a-zA-Z]{0,20}\\\\\":\\s*\\\\\"[a-zA-Z]{0,7}\\\\\"[}]\",\\s*\"[a-z]{0,7}\"\\s*:\\s*\"[a-zA-Z]{0,4}.[a-zA-Z]{0,6}\"\\s*[}]");

    auto begin = std::sregex_iterator(new_line.begin(), new_line.end(), pattern);
    auto end = std::sregex_iterator();
    while ( begin != end){                                                //this function takes an OID which is at the beginning
        try{                                                            //of the json object. It then returns all the information
            std::smatch match = *begin;                                 //corresponding to that specific json object.
            if ( std::regex_search(new_line, match, pattern))           //postcondition: returns all information regarding OID.
                std::cout << "$oid :  " << match.str() << std::endl;
            else
                std::cerr << ip_address << " not found " << std::endl;
            
        
        }catch ( std::regex_error &e){
        std::cout << ip_address << "not found " << std::endl;
    }
    }std::cout << " HI " << std::endl;
}

int main(int argc, char **argv)
{
    std::string ip_address;
    std::string line;     // holds value from file
    std::string new_line;
    std::string file_name;
    std::cout << "Enter an IP address to find, or an OID " << std::endl;
    std::cin >> ip_address;
    std::cout << "Enter a file name " << std::endl;  // file has to be in current dir with cpp file; Windows use dir, linux use pwd
    std::cin >> file_name;                          // if no file, this program returns 0.
    
    std::fstream file;
    //exist_file(file);
    file.open(file_name);  //honeypot.json
    file >> line;
    while ( std::getline(file, line)){                  //contents on file is being kept in a string.
        new_line += line;
        new_line.push_back('\n');
    }
    //std::cout << new_line;
    if ( ip_address.size() < 16)      // maximum size of an IPv4 address is XXX.XXX.XXX.XXX == 15
        regex(ip_address, new_line);
    else
        regex_oid(ip_address, new_line);
    return 0;
}


