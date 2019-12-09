#include <iostream>
#include <functional>
#include <map>
#include <iterator>
#include <any>
#include <string>
#include <vector>
#include "CPPO.h"

using namespace std;

// CPPO implementation

vector<string> nusstudios::core::mapping::strsplit(string s, string delimiter) {
    vector<string> result = {};
    size_t pos = 0;
    string token;

    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);

        if (token.length() != 0) {
            result.push_back(token);
        }

        s.erase(0, pos + delimiter.length());
    }

    if (s.length() != 0) {
        result.push_back(s);
    }

    return result;
}

void nusstudios::core::mapping::iterate(string path, map<string, any> &mref, function<void(string, any)> callback, string path_sep) {
    for (auto itr = mref.begin(); itr != mref.end(); itr++) {
        string key = itr->first;
        any value = itr->second;
        string _path = path + path_sep + key;

        if (value.type() == typeid(map<string, any>)) {
            auto _value = any_cast<map<string, any>>(value);
            nusstudios::core::mapping::iterate(_path, _value, callback, path_sep);
        }
        else {
            callback(_path, value);
        }
    }

    if (mref.empty()) {
        callback(path, mref);
    }
}

string nusstudios::core::mapping::getleaf(string path, string path_sep) {
    size_t pos;

    if ((pos = path.rfind(path_sep)) == string::npos) {
        return path;
    }
    else {
        return path.substr(pos + 1);
    }
}

string nusstudios::core::mapping::getdiff(string fullp, string pp) {
    return fullp.substr(pp.length());
}

string nusstudios::core::mapping::getmum(string path, string path_sep) {
    size_t pos;

    if ((pos = path.rfind(path_sep)) == string::npos) {
        return "";
    }
    else {
        return path.substr(0, pos);
    }
}

bool nusstudios::core::mapping::hasindirection(string path, string path_sep) {
    return string::npos != path.find(path_sep);
}

vector<string> nusstudios::core::mapping::splitpath(string path, string path_sep) {
    return nusstudios::core::mapping::strsplit(path, path_sep);
}

template<class t>
void nusstudios::core::mapping::printv(vector<t> &lst) {
    for (int i = 0; i < lst.size(); i++) {
        cout << (i == 0 ? "[ " : "");
        cout << lst[i];
        cout << (i != (lst.size() - 1) ? ", " : "");
        cout << (i == (lst.size() - 1) ? " ]" : "");
    }
}

any nusstudios::core::mapping::query(map<string, any>* mptr, string path, string &foundPath, string path_sep) {
    vector vctr = nusstudios::core::mapping::strsplit(path, path_sep);
    map<string, any> *submap = mptr;
    any* child;

    for (int i = 0; i < vctr.size(); i++) {
        if (submap->find(vctr[i]) != submap->end()) {
            if (foundPath.length() != 0) {
                foundPath += path_sep;
            }

            foundPath += vctr[i];
            child = &submap->at(vctr[i]);

            if ((*child).type() == typeid(map<string, any>)) {
                submap = any_cast<map<string, any>>(child);

                if (i == vctr.size() - 1)
                    return child;
            }
            else {
                return child;
            }
        }
        else {
            if (i == 0) {
                break;
            }
            else {
                return child;
            }
        }
    }

    return submap;
}

bool nusstudios::core::mapping::del(map<string, any>* mptr, string path, string path_sep) {
    string mom = nusstudios::core::mapping::getmum(path, path_sep);
    string pth;
    any node = nusstudios::core::mapping::query(mptr, mom, pth, path_sep);

    if (mom == pth) {
        string leaf = nusstudios::core::mapping::getleaf(path, path_sep);
        map<string, any>* ptr;

        if (nusstudios::core::mapping::hasindirection(path, path_sep)) {
            any* _ptr = any_cast<any*>(node);
            ptr = any_cast<map<string, any>>(_ptr);
        }
        else {
            ptr = any_cast<map<string, any>*>(node);
        }

        (*ptr).erase(leaf);
        return true;
    }
    else {
        return false;
    }
}

bool nusstudios::core::mapping::update(map<string, any>* mptr, string path, any value, string path_sep) {
    string pth;
    any a = nusstudios::core::mapping::query(mptr, path, pth, path_sep);

    if (pth == path) {
        if (pth == "") {
            if (value.type() == typeid(map<string, any>)) {
                map<string, any>* mp = any_cast<map<string, any>*>(a);
                *mp = any_cast<map<string, any>>(value);
                return true;
            }
            else {
                return false;
            }
        }
        else {
            any* ptr = any_cast<any*>(a);
            *ptr = value;
            return true;
        }
    }
    else {
        map<string, any> *mp;

        if (a.type() == typeid(any*)) {
            any* ptr = any_cast<any*>(a);

            if ((*ptr).type() != typeid(map<string, any>)) {
                return false;
            }
            else {
                mp = any_cast<map<string, any>>(ptr);
            }
        }
        else {
            mp = any_cast<map<string, any>*>(a);
        }

        vector<string> nonextpath = nusstudios::core::mapping::strsplit(getdiff(path, pth), path_sep);

        for (int i = 0; i < nonextpath.size() - 1; i++) {
            string nxtpth = nonextpath[i];
            mp->insert({nxtpth, map<string, any>()});
            mp = any_cast<map<string, any>>(&mp->at(nxtpth));
        }

        mp->insert({nonextpath[nonextpath.size() - 1], value});
        return true;
    }
}

nusstudios::core::mapping::CPPO::CPPO(map<string, any> inm, string path_separator) {
    _map = inm;
    path_sep = path_separator;
    printfunc = [this] (string path, any element) -> void {
        cout << endl << path << path_sep;

        if (element.type() == typeid(string)) {
            cout << any_cast<string>(element);
        }
        else if (element.type() == typeid(int)) {
            cout << any_cast<int>(element);
        }
        else if (element.type() == typeid(const char*)) {
            cout << any_cast<const char*>(element);
        } else if (element.type() == typeid(map<string, any>)) {
            // nothing
        }
    };
};

nusstudios::core::mapping::CPPO::~CPPO() {};

string nusstudios::core::mapping::CPPO::getleaf(string path) {
    return nusstudios::core::mapping::getleaf(path, path_sep);
}

string nusstudios::core::mapping::CPPO::getdiff(string fullp, string pp) {
    return nusstudios::core::mapping::getdiff(fullp, pp);
}

string nusstudios::core::mapping::CPPO::getmum(string path) {
    return nusstudios::core::mapping::getmum(path, path_sep);
}

bool nusstudios::core::mapping::CPPO::hasindirection(string path) {
    return nusstudios::core::mapping::hasindirection(path, path_sep);
}

vector<string> nusstudios::core::mapping::CPPO::splitpath(string path) {
    return nusstudios::core::mapping::splitpath(path, path_sep);
}

bool nusstudios::core::mapping::CPPO::update(string path, any value) {
    return nusstudios::core::mapping::update(&_map, path, value, path_sep);
}

bool nusstudios::core::mapping::CPPO::del(string path) {
    return nusstudios::core::mapping::del(&_map, path, path_sep);
}

any nusstudios::core::mapping::CPPO::queryptr(string path, string& found_path, bool cast_child_from_any_to_map_if_possible) {
    any a = nusstudios::core::mapping::query(&_map, path, found_path, path_sep);

    if (a.type() == typeid(map<string, any>*)) {
        nusstudios::core::mapping::CPPOPtr r(any_cast<map<string, any>*>(a), path_sep);
        return r;
    }
    else {
        any* optr = any_cast<any*>(a);

        if ((*optr).type() == typeid(map<string, any>)) {
            if (cast_child_from_any_to_map_if_possible) {
                nusstudios::core::mapping::CPPOPtr r(any_cast<map<string, any>>(optr), path_sep);
                return r;
            }
            else {
                return optr;
            }
        }
        else {
            return optr;
        }
    }
}

any nusstudios::core::mapping::CPPO::querycpy(string path, string &foundPath) {
    any a = nusstudios::core::mapping::query(&_map, path, foundPath, path_sep);

    if (a.type() == typeid(map<string, any>*)) {
        nusstudios::core::mapping::CPPO r(*any_cast<map<string, any>*>(a), path_sep);
        return r;
    }
    else {
        any* optr = any_cast<any*>(a);

        if ((*optr).type() == typeid(map<string, any>)) {
            nusstudios::core::mapping::CPPO r(any_cast<map<string, any>>(*optr), path_sep);
            return r;
        }
        else {
            return *optr;
        }
    }
}

void nusstudios::core::mapping::CPPO::printm(function<void(string, any)> callback) {
    nusstudios::core::mapping::iterate("root", _map, callback, path_sep);
}

void nusstudios::core::mapping::CPPO::printm() {
    nusstudios::core::mapping::iterate("root", _map, printfunc, path_sep);
}

// CPPOPtr implementation

nusstudios::core::mapping::CPPOPtr::CPPOPtr(map<string, any>* mptr, string path_separator) {
_map = mptr;
path_sep = path_separator;
printfunc = [this] (string path, any element) -> void {
    cout << endl << path << path_sep;

    if (element.type() == typeid(string)) {
        cout << any_cast<string>(element);
    }
    else if (element.type() == typeid(int)) {
        cout << any_cast<int>(element);
    }
    else if (element.type() == typeid(const char*)) {
        cout << any_cast<const char*>(element);
    } else if (element.type() == typeid(map<string, any>)) {
        // nothing
    }
};
}

nusstudios::core::mapping::CPPOPtr::~CPPOPtr() {};

string nusstudios::core::mapping::CPPOPtr::getleaf(string path) {
    return nusstudios::core::mapping::getleaf(path, path_sep);
}

string nusstudios::core::mapping::CPPOPtr::getdiff(string fullp, string pp) {
    return nusstudios::core::mapping::getdiff(fullp, pp);
}

string nusstudios::core::mapping::CPPOPtr::getmum(string path) {
    return nusstudios::core::mapping::getmum(path, path_sep);
}

bool nusstudios::core::mapping::CPPOPtr::hasindirection(string path) {
    return nusstudios::core::mapping::hasindirection(path, path_sep);
}

vector<string> nusstudios::core::mapping::CPPOPtr::splitpath(string path) {
    return nusstudios::core::mapping::splitpath(path, path_sep);
}

bool nusstudios::core::mapping::CPPOPtr::update(string path, any value) {
    return nusstudios::core::mapping::update(_map, path, value, path_sep);
}

bool nusstudios::core::mapping::CPPOPtr::del(string path) {
    return nusstudios::core::mapping::del(_map, path, path_sep);
}

any nusstudios::core::mapping::CPPOPtr::queryptr(string path, string& foundPath, bool cast_child_from_any_to_map_if_possible) {
    any a = nusstudios::core::mapping::query(_map, path, foundPath, path_sep);

    if (a.type() == typeid(map<string, any>*)) {
        nusstudios::core::mapping::CPPOPtr r(any_cast<map<string, any>*>(a), path_sep);
        return r;
    }
    else {
        any* optr = any_cast<any*>(a);

        if ((*optr).type() == typeid(map<string, any>)) {
            if (cast_child_from_any_to_map_if_possible) {
                nusstudios::core::mapping::CPPOPtr r(any_cast<map<string, any>>(optr), path_sep);
                return r;
            }
            else {
                return optr;
            }
        }
        else {
            return optr;
        }
    }
}

any nusstudios::core::mapping::CPPOPtr::querycpy(string path, string &foundPath) {
    any a = nusstudios::core::mapping::query(_map, path, foundPath, path_sep);

    if (a.type() == typeid(map<string, any>*)) {
        Mapping:CPPO r(*any_cast<map<string, any>*>(a), path_sep);
        return r;
    }
    else {
        any* optr = any_cast<any*>(a);

        if ((*optr).type() == typeid(map<string, any>)) {
            nusstudios::core::mapping::CPPO r(any_cast<map<string, any>>(*optr), path_sep);
            return r;
        }
        else {
            return *optr;
        }
    }
}

void nusstudios::core::mapping::CPPOPtr::printm(function<void(string, any)> callback) {
    nusstudios::core::mapping::iterate("root", *_map, callback, path_sep);
}

void nusstudios::core::mapping::CPPOPtr::printm() {
    nusstudios::core::mapping::iterate("root", *_map, printfunc, path_sep);
}

// using namespace nusstudios::core::mapping;

int main() {
    /* CPPO obj({}, ">");
    obj.update("key1", 5);
    obj.update("key2>asdfgh>qwerty>foo>bar", "const char*");
    obj.update("string literal", string("str"));
    obj.printm();
    cout << endl << endl;
    obj.del("key1");
    obj.del("key2>asdfgh>foo");
    obj.printm();
    cout << endl << endl;
    string outp;
    any a = obj.queryptr("key2>asdfgh", outp, true);
    nusstudios::core::mapping::CPPOPtr aptr = any_cast<nusstudios::core::mapping::CPPOPtr>(a);
    aptr.update("yxc", 6);
    obj.printm();
    any _a = obj.queryptr("key2>asdfgh", outp, false);
    any* _aptr = any_cast<any*>(_a);
    *_aptr = "map replaced with const char";
    cout << endl << endl;
    obj.printm();
    any a2 = obj.querycpy("key2", outp);
    nusstudios::core::mapping::CPPO _a2 = any_cast<nusstudios::core::mapping::CPPO>(a2);
    _a2.update("nxt", 5);
    cout << endl << endl;
    obj.printm(); */
}