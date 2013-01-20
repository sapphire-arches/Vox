#include "Shader.hpp"
#include "Util.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace vox::ren::gl;

//Util functions.
void PrintObjectInfoLog(int Object) {
    int buffLen;
    char* buff;
    GLhandleARB obj = (GLhandleARB) Object;

    glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB, &buffLen);
    if (buffLen > 0) {
        int charsWritten;
        buff = new char [buffLen + 1];
        glGetInfoLogARB(obj, buffLen, &charsWritten, buff);
        cout << "Info Log for object: " << Object << endl;
        cout << std::string(buff) << endl;
        delete[] buff;
    }
}

string ReadFullFile (const char* fname) {
    ifstream in(fname, ios::in | ios::binary);

    if (in) {
        string contents;
        in.seekg(0, ios::end);
        contents.resize(in.tellg());
        in.seekg(0, ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    std::cout << fname << " " << in.is_open() << std::endl;
    throw(in.fail());
}

//class Shader
Shader::Shader(string Source, int ShaderType) {
    this->_shaderID = glCreateShaderObjectARB(ShaderType);
    const char *src[1];
    src[0] = Source.c_str();
    int len = Source.length();
    
    glShaderSourceARB(this->_shaderID, 1, src, &len);
    PrintGLError("glShaderSourceARB");
    glCompileShaderARB(this->_shaderID);
    PrintGLError("glCompileShaderARB");
    cout << "Shader created with object ID " << this->_shaderID << ". Info log is " << endl;
    PrintObjectInfoLog(this->_shaderID);
    PrintGLError("Shader Compile");
}

Shader::~Shader() {
    //TODO: Some kind of memory managment of shaders
}

//class VertexShader
VertexShader::VertexShader(string Source) : Shader(Source, GL_VERTEX_SHADER_ARB) {
    //Nothing to do here.
}

VertexShader::~VertexShader() {
    //TODO: Some kind of memory management here.
}

//class FragmentShader
FragmentShader::FragmentShader(string Source) : Shader (Source, GL_FRAGMENT_SHADER_ARB) {
    //Nothing to do here.
}

FragmentShader::~FragmentShader() {
    //TODO: Some kind of memory management here.
}

//class ShaderProgram
ShaderProgram::ShaderProgram(const char* FName, const char* VName) {
    string *vsource = new string(ReadFullFile(VName));
    cout << "vsource is: " << endl << *vsource << endl;

    string *fsource = new string(ReadFullFile(FName));
    cout << "fsource is: " << endl << *fsource << endl;

    _programID = glCreateProgramObjectARB();

    VertexShader vshdr   (*vsource);
    FragmentShader fshdr (*fsource);
    
    glAttachObjectARB(_programID, vshdr._shaderID);
    glAttachObjectARB(_programID, fshdr._shaderID);
    PrintGLError("Attach Shadders");
    
    _link = true;
    delete vsource;
    delete fsource;
    cout << "Finished building program object " << _programID << endl;
}

ShaderProgram::~ShaderProgram() {
    //TODO: Some kind of memory managment on shaders.
}

void ShaderProgram::AttachVertexShader(VertexShader& VertShader) {
    glAttachObjectARB(VertShader._shaderID, _programID);
    _link = true;
}

void ShaderProgram::AttachFragmentShader(FragmentShader& FragShader) {
    glAttachObjectARB(FragShader._shaderID, _programID);
    _link = true;
}

void ShaderProgram::Use() {
    EnsureLink();
    glUseProgramObjectARB(_programID);
    PrintGLError("Shader Use");
}

int ShaderProgram::GetUniformLoc(string& Name) {
    UniformMap::iterator i = _uniforms.find(Name);
    if (i != _uniforms.end()) {
        return i->second;
    } else {
        EnsureLink();
        int loc = glGetUniformLocationARB(_programID, Name.c_str());
        PrintGLError("Location Get");
        _uniforms[Name] = loc;
        return loc;
    }
}

void ShaderProgram::PrintInfoLog() {
   PrintObjectInfoLog(_programID);
} 

void ShaderProgram::EnsureLink() {
    if (_link) {
        glLinkProgramARB(_programID);
        PrintObjectInfoLog(_programID);
        _link = false;
        PrintGLError("Shader Link.");
    }
}

ShaderProgram& ShaderProgram::operator= (const ShaderProgram& rhs) {
    if (this == &rhs) {
        return *this;
    }

    //TODO: we may need to delete shader objects here, but pehaps not.
    _programID = rhs._programID;
    _link = rhs._link;
    _uniforms = rhs._uniforms;

    return *this;
}
