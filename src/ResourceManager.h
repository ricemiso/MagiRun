#pragma once
#include "ofMain.h"

template<typename T>
class ResourceManager {
private:
	unordered_map<string, T> contents_;
	string defaultPath_;	// デフォルトのフォルダパス

public:
	ResourceManager();
	virtual ~ResourceManager();
	void loadContentsFromFile(string _fileName, string _defaultPath = "");
	T* getContents(string _key);
	void clearContents();
	void unloadContentsFromFile(string _fileName);
};

template<typename T>
inline ResourceManager<T>::ResourceManager()
	: contents_()
	, defaultPath_("")
{}

template<typename T>
inline ResourceManager<T>::~ResourceManager()
{
	clearContents();
}

template<typename T>
void ResourceManager<T>::loadContentsFromFile(string _fileName, string _defaultPath)
{
	string path = "";
	defaultPath_ = _defaultPath;
	if (defaultPath_ != "") {
		path = defaultPath_ + "/";
	}

	ofBuffer resfile = ofBufferFromFile(_fileName);

	auto lines = resfile.getLines();
	for (auto l : lines) {
		contents_.insert(make_pair(l, T(path + l)));
	}
}

template<typename T>
inline T* ResourceManager<T>::getContents(string _key)
{
	return &contents_[_key];
}

template<typename T>
inline void ResourceManager<T>::clearContents()
{
	contents_.clear();
}

template<typename T>
inline void ResourceManager<T>::unloadContentsFromFile(string _fileName)
{
	ofBuffer resfile = ofBufferFromFile(_fileName);

	auto lines = resfile.getLines();
	for (auto l : lines) {
		contents_.erase(l);
	}
}
