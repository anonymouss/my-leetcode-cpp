/**
 * Given an absolute path for a file (Unix-style), simplify it. 
 *
 * For example,
 * path = "/home/", => "/home"
 * path = "/a/./b/../../c/", => "/c"
 * path = "/a/../../b/../c//.//", => "/c"
 * path = "/a//b////c/d//././/..", => "/a/b/c"
 *
 * In a UNIX-style file system, a period ('.') refers to the current directory, so it can be ignored
 * in a simplified path. Additionally, a double period ("..") moves up a directory, so it cancels out
 * whatever the last directory was. For more information,
 * look here: https://en.wikipedia.org/wiki/Path_(computing)#Unix_style
 *
 * Corner Cases:
 * Did you consider the case where path = "/../"?
 * In this case, you should return "/".
 * Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
 * In this case, you should ignore redundant slashes and return "/home/foo".
 */

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> folderVec;
        string folder{""};
        path += "/"; // ensure input end with '/'
        for (int i = 0; i < path.length(); ++i) {
            if (path[i] == '/') {   // separator
                if (!folder.empty()) {  // not the frist '/'
                    if (folder == "..") {   // cd to parent folder
                        if (!folderVec.empty()) // has parent folder
                            folderVec.pop_back();
                    } else if (folder != ".") { // not cd to current folder
                        folderVec.emplace_back(folder);
                    }
                    folder.clear();
                }
            } else {
                folder += path[i];
            }
        }
        string res{""};
        for (const auto &f : folderVec) {
            res += "/";
            res += f;
        }
        return res.empty() ? "/" : res;
    }
};

int main() {
    Solution s;
    int testId = 1;

    vector<string> paths{
        "/home/",                   // -> /home
        "/a/./b/../../c/",          // -> /c
        "/a/../../b/../c//.//",     // -> /c
        "/a//b////c/d//././/..",    // -> /a/b/c
        // corner case
        "/../",                     // -> /
        "/home//foo/"               // -> /home/foo
    };

    for (auto &path : paths) {
        auto p = s.simplifyPath(path);
        std::cout << "Case " << testId++ << ": " << p << std::endl;
    }
}