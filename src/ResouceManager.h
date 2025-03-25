#pragma once
#include"ofMain.h"

template<typename T>
class ResouceManager
{
private:
	unordered_map<string, T>contents_;
	string defaultPath_;

public:
	ResouceManager();
	virtual ~ResouceManager();
	void loadContentsFromFile(string _filename,string _defaultPath = "");
	T* getComtents(string _key);
	void clearContants();
	void unloadContentsFromFile(string _filename);
};


template<typename T>
ResouceManager<T>::ResouceManager()
	:contents_()
	,defaultPath_("")
{

}

template<typename T>
ResouceManager<T>::~ResouceManager() {
	clearContants();
}

template<typename T>
inline  void ResouceManager<T>::loadContentsFromFile(string _filename,string _defaultPath)
{
	string path = "";
	defaultPath_ = _defaultPath;
	if (defaultPath_ != "") {
		path = defaultPath_ + "/";
	}

	ofBuffer resfile = ofBufferFromFile(_filename);
	auto lines = resfile.getLines();
	for (auto l : lines) {
		contents_.insert(make_pair(l, T(path + l)));
	}
}

template<typename T>
inline T* ResouceManager<T>::getComtents(string _key)
{
	return &contents_[_key];
}

template<typename T>
inline void ResouceManager<T>::clearContants()
{
	contents_.clear();
}

template<typename T>
inline void ResouceManager<T>::unloadContentsFromFile(string _filename)
{
	ofBuffer resfile = ofBufferFromFile(_filename);
	auto lines = resfile.getLines();
	for (auto l : lines) {
		contents_.erase(l);
	}
}
