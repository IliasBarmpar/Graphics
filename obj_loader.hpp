#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

typedef struct point {
  float x;
  float y;
  float z;
  float w;
  bool has_w = false;
} point;

typedef struct face {
  int vtx_indices[3];
  int norm_indices[3];
  bool has_norm = false;
} face;

typedef struct model {
  vector<point> obj_vertices; // array of all v
  vector<point> obj_normals; // array of all vn
  vector<face> obj_faces; // array of all f
} model;

class obj_loader {
private:
    model md;
    std::ifstream _file;

    inline void split(const string &s, vector<std::string> &v, char delim) {
        std::istringstream ss(s);
        std::string tmp;
        while(std::getline(ss, tmp, delim)) {
            if (tmp != "") {
                v.push_back(tmp);
            }
        }
    }

public:
    obj_loader(const string);
    ~obj_loader()=default;
    void load(const string);
    void clear();
    model& get_model();
};
