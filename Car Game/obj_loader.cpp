#include "obj_loader.hpp"

obj_loader::obj_loader(const string path) {
    load(path);
}

void obj_loader::load(const string path) {

    _file.open(path);
    if (_file.fail()){
		exit(1);
    }

    string line;
    std::vector<string> v;
    while(std::getline(_file,line)){
        split(line,v,' ');
        if (v.size() == 0 || v[0] == "#") {
            v.clear();
            continue;
        }

        if (v[0] == "v") {
            point p;
            if (sscanf(line.c_str(), "%*s %f %f %f\n", &p.x, &p.y, &p.z) == 3) {
                md.obj_vertices.push_back(p);
            }
            // else if (sscanf(line.c_str(), "%*s %f %f %f %f\n", &p.x, &p.y, &p.z, &p.w) == 4) {
            //     p.has_w = true;
            //     md.obj_vertices.push_back(p);
            // }
        }
        else if (v[0] == "f") {
            face f;
            if (sscanf(line.c_str(), "%*s %d %d %d\n", &f.vtx_indices[0], &f.vtx_indices[1], &f.vtx_indices[2]) == 3) {
                md.obj_faces.push_back(f);
            }
            else if (sscanf(line.c_str(), "%*s %d//%d %d//%d %d//%d\n", &f.vtx_indices[0], &f.norm_indices[0], &f.vtx_indices[1], &f.norm_indices[1], &f.vtx_indices[2], &f.norm_indices[2]) == 6) {
                f.has_norm = true;
                md.obj_faces.push_back(f);
            }
        }
        else if (v[0] == "vn") {
            point p;
            if (sscanf(line.c_str(), "%*s %f %f %f\n", &p.x, &p.y ,&p.z) == 3) {
                md.obj_normals.push_back(p);
            }
        }
        else{
            v.clear();
            continue;
        }
        v.clear();
    }
    _file.close();
}

void obj_loader::clear() {
    md.obj_faces.clear();
    md.obj_normals.clear();
    md.obj_vertices.clear();
}

model& obj_loader::get_model(){ return md; } //tha klhthei o copy constr toy vector opote ok
