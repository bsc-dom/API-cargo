#include "dataclayplugin.h"

PyObject *pFile = NULL;
wchar_t* wPathToScript;
char* dict[1000];
int pos_dict = 0;
int free_dict[1001];

void dataclay_plugin(const char* alias, const char* lib_path){
    Py_Initialize();

    PyObject *sysPath = PySys_GetObject("path");
    

    const char* pathToScript = lib_path;
    size_t len = mbstowcs(NULL, pathToScript, 0) + 1;
    wPathToScript = (wchar_t*)malloc(len * sizeof(wchar_t));
    mbstowcs(wPathToScript, pathToScript, len);

    PyObject *pathItem = PyUnicode_FromWideChar(wPathToScript, -1);
    PyList_Append(sysPath, pathItem);

    PyObject *pModule = PyImport_ImportModule("client");
    if (pModule != NULL) {
        //Start the client
        PyObject *pFileFunc = PyObject_GetAttrString(pModule, "start_client");
        if (pFileFunc != NULL){
            PyObject *client = PyObject_CallObject(pFileFunc, NULL);
        }
        //Creates the persistent object "pFile" with alias "alias"
        pFile = PyObject_CallMethodObjArgs(pModule, PyUnicode_FromString("make_persistent"), PyUnicode_FromString(alias), NULL);
    }else{
        printf("ImportModule == NULL\n");
        PyErr_Print();
    }
}

int dataclay_open(char* path, int flags, unsigned int mode){
    int fd;
    if(free_dict[0]==0){
        dict[pos_dict] = path;
        fd = pos_dict;
        pos_dict = pos_dict + 1;
    }else{
        dict[free_dict[free_dict[0]]] = path;
        fd = free_dict[free_dict[0]];
        free_dict[0] = free_dict[0] - 1;
    }
    return fd;
}

void dataclay_close(int fd){
    dict[fd] = "";
    free_dict[0] = free_dict[0] + 1;
    free_dict[free_dict[0]] = fd;
}

int dataclay_pread(int fd, char* buf, int count, int offset){
    const char* path = dict[fd];
    if (pFile != NULL && path != ""){
        PyObject *pResult = PyObject_CallMethodObjArgs(pFile, PyUnicode_FromString("read"), PyUnicode_FromString(path), PyLong_FromLong(count), PyLong_FromLong(offset), NULL);
        if(pResult == Py_None) return -1;
        memcpy(buf, PyBytes_AsString(pResult), PyBytes_GET_SIZE(pResult));
        return PyBytes_GET_SIZE(pResult);
    }else{
        if(pFile == NULL){
            printf("ImportFile-read == NULL\n");
            PyErr_Print();
        }else{
            printf("File not opened\n");
        }
    }
    return -1;
}
int dataclay_pwrite(int fd, const char* buf, int count, int offset){
    const char* path = dict[fd];
    if (pFile != NULL && path != ""){
        PyObject *pResult = PyObject_CallMethodObjArgs(pFile, PyUnicode_FromString("write"),PyUnicode_FromString(path), PyBytes_FromStringAndSize(buf,count), PyLong_FromLong(count), PyLong_FromLong(offset), NULL);
        return PyLong_AsLong(pResult);
    }else{
        if(pFile == NULL){
            printf("ImportFile-write == NULL\n");
            PyErr_Print();
        }else{
            printf("File not opened\n");
        }
    }
    return -1;
}

void dataclay_plugin_close(){
    free(wPathToScript);
    Py_Finalize();
}

