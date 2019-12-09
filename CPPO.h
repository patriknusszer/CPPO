//
// Created by Nusszer Patrik on 2019. 08. 13..
//

#ifndef CPPO_CPPO_H
#define CPPO_CPPO_H

#include <iostream>
#include <functional>
#include <map>
#include <iterator>
#include <any>
#include <string>
#include <vector>

using namespace std;

namespace nusstudios::core::mapping {
    vector<string> strsplit(string s, string delimiter);
    void iterate(string path, map<string, any> &mref, function<void(string, any)> callback, string path_sep);
    string getleaf(string path, string path_sep);
    string getdiff(string fullp, string pp);
    string getmum(string path, string path_sep);
    bool hasindirection(string path, string path_sep);
    vector<string> splitpath(string path, string path_sep);
    template<class t>
    void printv(vector<t> &lst);
    any query(map<string, any>* mptr, string path, string &foundPath, string path_sep);
    bool del(map<string, any>* mptr, string path, string path_sep);
    bool update(map<string, any>* mptr, string path, any value, string path_sep);

    class CPPO {
    public:
        map<string, any> _map = {};
        string path_sep;
        function<void(string, any)> printfunc;
        CPPO(map<string, any> inm, string path_separator);
        ~CPPO();
        string getleaf(string path);
        string getdiff(string fullp, string pp);
        string getmum(string path);
        bool hasindirection(string path);
        vector<string> splitpath(string path);
        bool update(string path, any value);
        bool del(string path);
        any queryptr(string path, string& found_path, bool cast_child_from_any_to_map_if_possible);
        any querycpy(string path, string &foundPath);
        void printm(function<void(string, any)> callback);
        void printm();
    };

    class CPPOPtr {
    public:
        map<string, any>* _map;
        string path_sep;
        function<void(string, any)> printfunc;
        CPPOPtr(map<string, any>* mptr, string path_separator);
        ~CPPOPtr();
        string getleaf(string path);
        string getdiff(string fullp, string pp);
        string getmum(string path);
        bool hasindirection(string path);
        vector<string> splitpath(string path);
        bool update(string path, any value);
        bool del(string path);
        any queryptr(string path, string& foundPath, bool cast_child_from_any_to_map_if_possible);
        any querycpy(string path, string &foundPath);
        void printm(function<void(string, any)> callback);
        void printm();
    };
}

#endif //CPPO_CPPO_H
